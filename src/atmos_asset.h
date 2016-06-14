/*
    Copyright (C) 2016 Carl Hetherington <cth@carlh.net>

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

    In addition, as a special exception, the copyright holders give
    permission to link the code of portions of this program with the
    OpenSSL library under certain conditions as described in each
    individual source file, and distribute linked combinations
    including the two.

    You must obey the GNU General Public License in all respects
    for all of the code used other than OpenSSL.  If you modify
    file(s) with this exception, you may extend this exception to your
    version of the file(s), but you are not obligated to do so.  If you
    do not wish to do so, delete this exception statement from your
    version.  If you delete this exception statement from all source
    files in the program, then also delete it here.
*/

#ifndef LIBDCP_ATMOS_ASSET_H
#define LIBDCP_ATMOS_ASSET_H

#include "asset.h"
#include "mxf.h"

namespace dcp {

class AtmosAsset : public Asset, public MXF
{
public:
	explicit AtmosAsset (boost::filesystem::path file);

	std::string pkl_type (Standard) const;

	Fraction edit_rate () const {
		return _edit_rate;
	}

	int64_t intrinsic_duration () const {
		return _intrinsic_duration;
	}

	/** @return frame number of the frame to align with the FFOA of the picture track */
	int first_frame () const {
		return _first_frame;
	}

	/** @return maximum number of channels in bitstream */
	int max_channel_count () const {
		return _max_channel_count;
	}

	/** @return maximum number of objects in bitstream */
	int max_object_count () const {
		return _max_object_count;
	}

private:
	Fraction _edit_rate;
	int64_t _intrinsic_duration;
	int _first_frame;
	int _max_channel_count;
	int _max_object_count;
};

}

#endif