/*
    Copyright (C) 2015 Carl Hetherington <cth@carlh.net>

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

#include "smpte_subtitle_asset.h"
#include "util.h"
#include <getopt.h>
#include <cstdlib>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cerr;
using std::map;

static void
help (string n)
{
	cerr << "Syntax: " << n << " [OPTION] <MXF>\n"
	     << "  -h, --help                   show this help\n"
	     << "  -n, --no-fonts               don't extract fonts\n";
}

int
main (int argc, char* argv[])
{
	bool extract_fonts = true;

	int option_index = 0;
	while (1) {
		static struct option long_options[] = {
			{ "help", no_argument, 0, 'h'},
			{ "no-fonts", no_argument, 0, 'n'},
			{ 0, 0, 0, 0 }
		};

		int c = getopt_long (argc, argv, "hn", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
		case 'h':
			help (argv[0]);
			exit (EXIT_SUCCESS);
		case 'n':
			extract_fonts = false;
			break;
		}
	}

	if (argc <= optind || argc > (optind + 2)) {
		help (argv[0]);
		exit (EXIT_FAILURE);
	}

	dcp::SMPTESubtitleAsset sub (argv[optind]);

	cout << sub.xml_as_string() << "\n";

	if (extract_fonts) {
		map<string, dcp::Data> fonts = sub.fonts_with_load_ids ();
		for (map<string, dcp::Data>::const_iterator i = fonts.begin(); i != fonts.end(); ++i) {
			FILE* f = dcp::fopen_boost (i->first + ".ttf", "wb");
			if (!f) {
				cerr << "Could not open font file " << i->first << ".ttf for writing";
				exit (EXIT_FAILURE);
			}
			fwrite (i->second.data.get(), 1, i->second.size, f);
			fclose (f);
		}
	}
}