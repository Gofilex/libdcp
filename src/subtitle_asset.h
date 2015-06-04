/*
    Copyright (C) 2012-2015 Carl Hetherington <cth@carlh.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef LIBDCP_SUBTITLE_ASSET_H
#define LIBDCP_SUBTITLE_ASSET_H

#include "asset.h"
#include "dcp_time.h"
#include "subtitle_string.h"
#include <libcxml/cxml.h>

namespace xmlpp {
	class Element;
}

namespace dcp
{

class SubtitleString;	
class FontNode;
class TextNode;
class SubtitleNode;
class LoadFontNode;

/** @class SubtitleAsset
 *  @brief A parent for classes representing a file containing subtitles.
 */
class SubtitleAsset : public Asset
{
public:
	SubtitleAsset ();
	SubtitleAsset (boost::filesystem::path file);

	bool equals (
		boost::shared_ptr<const Asset>,
		EqualityOptions,
		NoteHandler note
		) const;

	std::list<SubtitleString> subtitles_during (Time from, Time to) const;
	std::list<SubtitleString> const & subtitles () const {
		return _subtitles;
	}

	void add (SubtitleString);

	virtual void write (boost::filesystem::path) const = 0;
	virtual Glib::ustring xml_as_string () const = 0;

	Time latest_subtitle_out () const;

	virtual std::list<boost::shared_ptr<LoadFontNode> > load_font_nodes () const = 0;

protected:
	void parse_common (boost::shared_ptr<cxml::Document> xml, std::list<boost::shared_ptr<FontNode> > font_nodes);
	
	virtual std::string pkl_type (Standard) const = 0;

	std::string asdcp_kind () const {
		return "Subtitle";
	}

	void subtitles_as_xml (xmlpp::Element* root, int time_code_rate, std::string xmlns) const;
	
	std::list<SubtitleString> _subtitles;

private:
	struct ParseState {
		std::list<boost::shared_ptr<FontNode> > font_nodes;
		std::list<boost::shared_ptr<TextNode> > text_nodes;
		std::list<boost::shared_ptr<SubtitleNode> > subtitle_nodes;
	};

	void maybe_add_subtitle (std::string text, ParseState const & parse_state);
	
	void examine_font_nodes (
		boost::shared_ptr<const cxml::Node> xml,
		std::list<boost::shared_ptr<FontNode> > const & font_nodes,
		ParseState& parse_state
		);
	
	void examine_text_nodes (
		boost::shared_ptr<const cxml::Node> xml,
		std::list<boost::shared_ptr<TextNode> > const & text_nodes,
		ParseState& parse_state
		);
};

}

#endif
