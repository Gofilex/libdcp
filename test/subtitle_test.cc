/*
    Copyright (C) 2012-2014 Carl Hetherington <cth@carlh.net>

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

#include "interop_subtitle_content.h"
#include "subtitle_string.h"
#include <boost/test/unit_test.hpp>

using std::list;
using std::string;
using boost::shared_ptr;

/* Load some subtitle content from XML and check that it is read correctly */
BOOST_AUTO_TEST_CASE (subtitles1)
{
	dcp::InteropSubtitleContent subs ("test/data/subs1.xml");

	BOOST_CHECK_EQUAL (subs.language(), "French");

	list<dcp::SubtitleString> s = subs.subtitles_during (dcp::Time (0, 0, 6, 1, 250), dcp::Time (0, 0, 6, 2, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 1);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFontId"),
				   false,
				   dcp::Colour (255, 255, 255),
				   39,
				   dcp::Time (0, 0, 5, 198, 250),
				   dcp::Time (0, 0, 7, 115, 250),
				   15,
				   dcp::BOTTOM,
				   "My jacket was Idi Amin's",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 1, 250),
				   dcp::Time (0, 0, 0, 1, 250)
				   ));
							 
	s = subs.subtitles_during (dcp::Time (0, 0, 7, 190, 250), dcp::Time (0, 0, 7, 191, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFontId"),
				   true,
				   dcp::Colour (255, 255, 255),
				   39,
				   dcp::Time (0, 0, 7, 177, 250),
				   dcp::Time (0, 0, 11, 31, 250),
				   21,
				   dcp::BOTTOM,
				   "My corset was H.M. The Queen's",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 1, 250),
				   dcp::Time (0, 0, 0, 1, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFontId"),
				   false,
				   dcp::Colour (255, 255, 255),
				   39,
				   dcp::Time (0, 0, 7, 177, 250),
				   dcp::Time (0, 0, 11, 31, 250),
				   15,
				   dcp::BOTTOM,
				   "My large wonderbra",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 1, 250),
				   dcp::Time (0, 0, 0, 1, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 0, 11, 95, 250), dcp::Time (0, 0, 11, 96, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 1);
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFontId"),
				   false,
				   dcp::Colour (255, 255, 255),
				   39,
				   dcp::Time (0, 0, 11, 94, 250),
				   dcp::Time (0, 0, 13, 63, 250),
				   15,
				   dcp::BOTTOM,
				   "Once belonged to the Shah",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 1, 250),
				   dcp::Time (0, 0, 0, 1, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 0, 14, 42, 250), dcp::Time (0, 0, 14, 43, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 1);
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFontId"),
				   false,
				   dcp::Colour (255, 255, 255),
				   39,
				   dcp::Time (0, 0, 13, 104, 250),
				   dcp::Time (0, 0, 15, 177, 250),
				   15,
				   dcp::BOTTOM,
				   "And these are Roy Hattersley's jeans",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 1, 250),
				   dcp::Time (0, 0, 0, 1, 250)
				   ));
}

/** And similarly for another one */
BOOST_AUTO_TEST_CASE (subtitles2)
{
	dcp::InteropSubtitleContent subs ("test/data/subs2.xml");

	list<dcp::SubtitleString> s = subs.subtitles_during (dcp::Time (0, 0, 42, 100, 250), dcp::Time (0, 0, 42, 101, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 0, 41, 62, 250),
				   dcp::Time (0, 0, 43, 52, 250),
				   89,
				   dcp::TOP,
				   "At afternoon tea with John Peel",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 0, 41, 62, 250),
				   dcp::Time (0, 0, 43, 52, 250),
				   95,
				   dcp::TOP,
				   "I enquired if his accent was real",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 0, 50, 50, 250), dcp::Time (0, 0, 50, 51, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 0, 50, 42, 250),
				   dcp::Time (0, 0, 52, 21, 250),
				   89,
				   dcp::TOP,
				   "He said \"out of the house",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 0, 50, 42, 250),
				   dcp::Time (0, 0, 52, 21, 250),
				   95,
				   dcp::TOP,
				   "I'm incredibly scouse",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 1, 2, 300, 250), dcp::Time (0, 1, 2, 301, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 2, 208, 250),
				   dcp::Time (0, 1, 4, 10, 250),
				   89,
				   dcp::TOP,
				   "At home it depends how I feel.\"",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 2, 208, 250),
				   dcp::Time (0, 1, 4, 10, 250),
				   95,
				   dcp::TOP,
				   "I spent a long weekend in Brighton",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 1, 15, 50, 250), dcp::Time (0, 1, 15, 51, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 15, 42, 250),
				   dcp::Time (0, 1, 16, 42, 250),
				   89,
				   dcp::TOP,
				   "With the legendary Miss Enid Blyton",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 15, 42, 250),
				   dcp::Time (0, 1, 16, 42, 250),
				   95,
				   dcp::TOP,
				   "She said \"you be Noddy",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 1, 27, 200, 250), dcp::Time (0, 1, 27, 201, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 27, 115, 250),
				   dcp::Time (0, 1, 28, 208, 250),
				   89,
				   dcp::TOP,
				   "That curious creature the Sphinx",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 27, 115, 250),
				   dcp::Time (0, 1, 28, 208, 250),
				   95,
				   dcp::TOP,
				   "Is smarter than anyone thinks",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 1, 42, 300, 250), dcp::Time (0, 1, 42, 301, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   false,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 42, 229, 250),
				   dcp::Time (0, 1, 45, 62, 250),
				   89,
				   dcp::TOP,
				   "It sits there and smirks",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   false,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 42, 229, 250),
				   dcp::Time (0, 1, 45, 62, 250),
				   95,
				   dcp::TOP,
				   "And you don't think it works",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 1, 45, 200, 250), dcp::Time (0, 1, 45, 201, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   false,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 45, 146, 250),
				   dcp::Time (0, 1, 47, 94, 250),
				   89,
				   dcp::TOP,
				   "Then when you're not looking, it winks.",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   false,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 45, 146, 250),
				   dcp::Time (0, 1, 47, 94, 250),
				   95,
				   dcp::TOP,
				   "When it snows you will find Sister Sledge",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 1, 47, 249, 250), dcp::Time (0, 1, 47, 250, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   false,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 47, 146, 250),
				   dcp::Time (0, 1, 48, 167, 250),
				   89,
				   dcp::TOP,
				   "Out mooning, at night, on the ledge",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   false,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 1, 47, 146, 250),
				   dcp::Time (0, 1, 48, 167, 250),
				   95,
				   dcp::TOP,
				   "One storey down",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));

	s = subs.subtitles_during (dcp::Time (0, 2, 6, 210, 250), dcp::Time (0, 2, 6, 211, 250));
	BOOST_REQUIRE_EQUAL (s.size(), 2);
	BOOST_CHECK_EQUAL (s.front(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 2, 5, 208, 250),
				   dcp::Time (0, 2, 7, 31, 250),
				   89,
				   dcp::TOP,
				   "HELLO",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
	BOOST_CHECK_EQUAL (s.back(), dcp::SubtitleString (
				   string ("theFont"),
				   true,
				   dcp::Colour (255, 255, 255),
				   42,
				   dcp::Time (0, 2, 5, 208, 250),
				   dcp::Time (0, 2, 7, 31, 250),
				   95,
				   dcp::TOP,
				   "WORLD",
				   dcp::BORDER,
				   dcp::Colour (0, 0, 0),
				   dcp::Time (0, 0, 0, 0, 250),
				   dcp::Time (0, 0, 0, 0, 250)
				   ));
}