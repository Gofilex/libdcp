/*
    Copyright (C) 2012-2014 Carl Hetherington <cth@carlh.net>

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

/** @file  src/mono_picture_frame.h
 *  @brief MonoPictureFrame class.
 */

#include "types.h"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <string>
#include <stdint.h>

namespace ASDCP {
	namespace JP2K {
		class FrameBuffer;
		class MXFReader;
	}
	class AESDecContext;
}

namespace dcp {

class OpenJPEGImage;

/** @class MonoPictureFrame
 *  @brief A single frame of a 2D (monoscopic) picture asset.
 */
class MonoPictureFrame : public boost::noncopyable
{
public:
	explicit MonoPictureFrame (boost::filesystem::path path);
	MonoPictureFrame (uint8_t const * data, int size);
	~MonoPictureFrame ();

	boost::shared_ptr<OpenJPEGImage> xyz_image (int reduce = 0) const;

	uint8_t const * j2k_data () const;
	uint8_t* j2k_data ();
	int j2k_size () const;

private:
	friend class MonoPictureAssetReader;

	MonoPictureFrame (ASDCP::JP2K::MXFReader* reader, int n, ASDCP::AESDecContext *);

	ASDCP::JP2K::FrameBuffer* _buffer;
};

}
