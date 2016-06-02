/*
    Copyright (C) 2012-2015 Carl Hetherington <cth@carlh.net>

    This file is part of libdcp.

    libdcp is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    libdcp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libdcp.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file  src/reel_mxf.h
 *  @brief ReelMXF
 */

#ifndef LIBDCP_REEL_ENCRYPTABLE_ASSET_H
#define LIBDCP_REEL_ENCRYPTABLE_ASSET_H

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace cxml {
	class Node;
}

namespace dcp {

/** @class ReelMXF
 *  @brief Part of a Reel's description which refers to an asset which can be encrypted.
 */
class ReelMXF
{
public:
	ReelMXF () {}
	explicit ReelMXF (boost::optional<std::string> key_id);
	explicit ReelMXF (boost::shared_ptr<const cxml::Node>);
	virtual ~ReelMXF () {}

	/** @return the 4-character key type for this MXF (MDIK, MDAK, etc.) */
	virtual std::string key_type () const = 0;

	/** @return true if a KeyId is specified for this asset, implying
	 *  that its content is encrypted.
	 */
	bool encrypted () const {
		return static_cast<bool>(_key_id);
	}

	/** @return Key ID to describe the key that encrypts this asset's
	 *  content, if there is one.
	 */
	boost::optional<std::string> key_id () const {
		return _key_id;
	}

private:
	boost::optional<std::string> _key_id; ///< The &lt;KeyId&gt; from the reel's entry for this asset, if there is one
};

}

#endif
