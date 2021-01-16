/*
 * largeprimes, an actually good version of a science fair experiment to find large primes.
 * Copyright (C) 2020  Nate Choe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * */

#include "primes.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf(
		"    largeprimes  Copyright (C) 2020  Nate Choe\n" +
		"    This program comes with ABSOLUTELY NO WARRANTY.'.\n" +
		"    This is free software, and you are welcome to redistribute it\n" +
		"    under certain conditions; type see license.txt for details.\n" +
	);
	printf("%lu\n", find(6103612132986129756, 210));
	return 0;
}
