/*
    Copyright (C) 2012 Carl Hetherington <cth@carlh.net>

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

/** @file  src/types.h
 *  @brief Miscellaneous types.
 */

#ifndef LIBDCP_TYPES_H
#define LIBDCP_TYPES_H

namespace libdcp
{

/** Identifier for a sound channel */
enum Channel {
	LEFT = 0,    ///< left
	RIGHT = 1,   ///< right
	CENTRE = 2,  ///< centre
	LFE = 3,     ///< low-frequency effects (sub)
	LS = 4,      ///< left surround
	RS = 5       ///< right surround
};

enum ContentKind
{
	FEATURE,
	SHORT,
	TRAILER,
	TEST,
	TRANSITIONAL,
	RATING,
	TEASER,
	POLICY,
	PUBLIC_SERVICE_ANNOUNCEMENT,
	ADVERTISEMENT
};

enum Effect
{
	NONE,
	BORDER,
	SHADOW
};

enum VAlign
{
	TOP,
	CENTER,
	BOTTOM
};
	
class Fraction
{
public:
	Fraction () : numerator (0), denominator (0) {}
	Fraction (std::string s);
	Fraction (int n, int d) : numerator (n), denominator (d) {}

	int numerator;
	int denominator;
};

enum EqualityFlags {
	LIBDCP_METADATA = 0x1,
	MXF_BITWISE = 0x2,
	MXF_INSPECT = 0x4
};

struct EqualityOptions {
	EqualityFlags flags;
	bool verbose;
	double max_mean_pixel_error;
	double max_std_dev_pixel_error;
};

class Color
{
public:
	Color ();
	Color (int r_, int g_, int b_);
	Color (std::string argb_hex);

	int r;
	int g;
	int b;
};

extern bool operator== (Color const & a, Color const & b);
extern std::ostream & operator<< (std::ostream & s, Color const & c);

}

#endif
