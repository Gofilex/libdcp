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

/** @file  src/mono_picture_asset_writer.cc
 *  @brief MonoPictureAssetWriter class
 */

#include "AS_DCP.h"
#include "KM_fileio.h"
#include "mono_picture_asset_writer.h"
#include "exceptions.h"
#include "picture_asset.h"
#include "dcp_assert.h"

#include "picture_asset_writer_common.cc"

using std::istream;
using std::ostream;
using std::string;
using boost::shared_ptr;
using namespace dcp;

struct MonoPictureAssetWriter::ASDCPState : public ASDCPStateBase
{
	ASDCP::JP2K::MXFWriter mxf_writer;
};

/** @param a Asset to write to.  `a' must not be deleted while
 *  this writer class still exists, or bad things will happen.
 */
MonoPictureAssetWriter::MonoPictureAssetWriter (PictureAsset* asset, boost::filesystem::path file, Standard standard, bool overwrite)
	: PictureAssetWriter (asset, file, standard, overwrite)
	, _state (new MonoPictureAssetWriter::ASDCPState)
{

}

void
MonoPictureAssetWriter::start (uint8_t* data, int size)
{
	dcp::start (this, _state, _standard, _picture_asset, data, size);
	_picture_asset->set_frame_rate (_picture_asset->edit_rate());
}

FrameInfo
MonoPictureAssetWriter::write (uint8_t* data, int size)
{
	DCP_ASSERT (!_finalized);

	if (!_started) {
		start (data, size);
	}

 	if (ASDCP_FAILURE (_state->j2k_parser.OpenReadFrame (data, size, _state->frame_buffer))) {
 		boost::throw_exception (MiscError ("could not parse J2K frame"));
 	}

	uint64_t const before_offset = _state->mxf_writer.Tell ();

	string hash;
	ASDCP::Result_t const r = _state->mxf_writer.WriteFrame (_state->frame_buffer, _encryption_context, _hmac_context, &hash);
	if (ASDCP_FAILURE (r)) {
		boost::throw_exception (MXFFileError ("error in writing video MXF", _file.string(), r));
	}

	++_frames_written;
	return FrameInfo (before_offset, _state->mxf_writer.Tell() - before_offset, hash);
}

void
MonoPictureAssetWriter::fake_write (int size)
{
	DCP_ASSERT (_started);
	DCP_ASSERT (!_finalized);

	Kumu::Result_t r = _state->mxf_writer.FakeWriteFrame (size);
	if (ASDCP_FAILURE (r)) {
		boost::throw_exception (MXFFileError ("error in writing video MXF", _file.string(), r));
	}

	++_frames_written;
}

bool
MonoPictureAssetWriter::finalize ()
{
	if (_started) {
		Kumu::Result_t r = _state->mxf_writer.Finalize();
		if (ASDCP_FAILURE (r)) {
			boost::throw_exception (MXFFileError ("error in finalizing video MXF", _file.string(), r));
		}
	}

	_picture_asset->_intrinsic_duration = _frames_written;
	return PictureAssetWriter::finalize ();
}
