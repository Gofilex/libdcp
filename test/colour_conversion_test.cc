/*
    Copyright (C) 2014 Carl Hetherington <cth@carlh.net>

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

#include "gamma_transfer_function.h"
#include "colour_conversion.h"
#include "modified_gamma_transfer_function.h"
#include <boost/test/unit_test.hpp>
#include <cmath>

using std::pow;
using boost::shared_ptr;
using namespace dcp;

static void
check_gamma (shared_ptr<const TransferFunction> tf, int bit_depth, bool inverse, float gamma)
{
	double const * lut = tf->lut (bit_depth, inverse);
	int const count = rint (pow (2.0, bit_depth));

	for (int i = 0; i < count; ++i) {
		BOOST_CHECK_CLOSE (lut[i], pow (float(i) / (count - 1), gamma), 0.001);
	}
}

static void
check_modified_gamma (shared_ptr<const TransferFunction> tf, int bit_depth, bool inverse, double power, double threshold, double A, double B)
{
	double const * lut = tf->lut (bit_depth, inverse);
	int const count = rint (pow (2.0, bit_depth));

	for (int i = 0; i < count; ++i) {
		double const x = double(i) / (count - 1);
		if (x > threshold) {
			BOOST_CHECK_CLOSE (lut[i], pow ((x + A) / (1 + A), power), 0.001);
		} else {
			BOOST_CHECK_CLOSE (lut[i], (x / B), 0.001);
		}
	}
}

/** Check that the gamma correction LUTs are right for sRGB */
BOOST_AUTO_TEST_CASE (colour_conversion_test1)
{
	ColourConversion cc = ColourConversion::srgb_to_xyz ();

	check_modified_gamma (cc.in(), 8, false, 2.4, 0.04045, 0.055, 12.92);
	check_modified_gamma (cc.in(), 12, false, 2.4, 0.04045, 0.055, 12.92);
	check_modified_gamma (cc.in(), 16, false, 2.4, 0.04045, 0.055, 12.92);

	check_gamma (cc.out(), 8, true, 1 / 2.6);
	check_gamma (cc.out(), 12, true, 1 / 2.6);
	check_gamma (cc.out(), 16, true, 1 / 2.6);
}

/** Check that the gamma correction LUTs are right for REC709 */
BOOST_AUTO_TEST_CASE (colour_conversion_test2)
{
	ColourConversion cc = ColourConversion::rec709_to_xyz ();

	check_modified_gamma (cc.in(), 8, false, 1 / 0.45, 0.081, 0.099, 4.5);
	check_modified_gamma (cc.in(), 12, false, 1 / 0.45, 0.081, 0.099, 4.5);
	check_modified_gamma (cc.in(), 16, false, 1 / 0.45, 0.081, 0.099, 4.5);

	check_gamma (cc.out(), 8, true, 1 / 2.6);
	check_gamma (cc.out(), 12, true, 1 / 2.6);
	check_gamma (cc.out(), 16, true, 1 / 2.6);
}

/** Check that the xyz_to_rgb matrix is the inverse of the rgb_to_xyz one */
BOOST_AUTO_TEST_CASE (colour_conversion_matrix_test)
{
	ColourConversion c = ColourConversion::srgb_to_xyz ();

	boost::numeric::ublas::matrix<double> A = c.rgb_to_xyz ();
	boost::numeric::ublas::matrix<double> B = c.xyz_to_rgb ();

	BOOST_CHECK_CLOSE (A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0), 1, 0.1);
	BOOST_CHECK (fabs (A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1)) < 1e-6);
	BOOST_CHECK (fabs (A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2)) < 1e-6);

	BOOST_CHECK (fabs (A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0)) < 1e-6);
	BOOST_CHECK_CLOSE (A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1), 1, 0.1);
	BOOST_CHECK (fabs (A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2)) < 1e-6);

	BOOST_CHECK (fabs (A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0)) < 1e-6);
	BOOST_CHECK (fabs (A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1)) < 1e-6);
	BOOST_CHECK_CLOSE (A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2), 1, 0.1);
}
