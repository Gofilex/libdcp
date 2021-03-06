/*
    Copyright (C) 2014 Carl Hetherington <cth@carlh.net>

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

/** @file  src/file.h
 *  @brief File class.
 */

#ifndef LIBDCP_FILE_H
#define LIBDCP_FILE_H

#include <boost/filesystem.hpp>
#include <boost/noncopyable.hpp>

namespace dcp {

/** @class File
 *  @brief Helper class which loads a file into memory.
 */
class File : public boost::noncopyable
{
public:
	explicit File (boost::filesystem::path file);
	~File ();

	uint8_t* data () const {
		return _data;
	}

	int64_t size () const {
		return _size;
	}

private:
	uint8_t* _data; ///< file's data
	int64_t _size;  ///< data size in bytes
};

}

#endif
