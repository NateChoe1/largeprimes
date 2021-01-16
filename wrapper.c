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
#include <string.h>

char stringsEqual(char string1[], char string2[]) {
	int len1 = strlen(string1);
	int len2 = strlen(string2);

	if (len1 != len2) return 0;
	for (int i = 0; i < len1; i++) {
		if (string1[i] != string2[i]) return 0;
	}
	return 1;
}

char nextIsNumber(int length, char *arguments[], int index) {
	if (index + 1 >= length) return 0;
	for (int i = 0; arguments[index + 1][i] != '\0'; i++) {
		if (arguments[index + 1][i] < '0' || arguments[index + 1][i] > '9') return 0;
	}
	return 1;
}

unsigned long long atoull(char convert[]) {
	unsigned long long current = 0;
	for (int i = 0; convert[i] != '\0'; i++) {
		current *= 10;
		current += convert[i] - '0';
	}
	return current;
}

int main(int argc, char *argv[]) {
	char quiet = 0;
	int method = 0;
	unsigned long long start = 1000000000000000;
	char exstart = 0;
	int base = 210;

	for (int i = 0; i < argc; i++) {
		if (stringsEqual(argv[i], "--help")) {
			printf("%s%s%s%s%s%s%s%s%s%s\n",
				"Flag       Short form     Purpose\n"
				"--quiet    -q             Don't print terminal outputs\n",
				"--method   -m             Set the method for prime finding\n",
				"                              0: Coprime method (default)\n",
				"                              1: Fermat's little theorem\n",
				"--start    -s             Set the starting point to look for primes\n",
				"                              (Default: 1 quadrillion)\n",
				"--explicit -e             Look for primes strictly greater than the start\n",
				"                              (note, this only makes sense with the coprime method)\n",
				"--base     -b             Set the base for primality checking\n",
				"                              (Default: 210)\n");
			return 0;
		}
		if (stringsEqual(argv[i], "--quiet") || stringsEqual(argv[i], "-q")) {
			quiet = 1;
		}
		if (stringsEqual(argv[i], "--method") || stringsEqual(argv[i], "-m")) {
			if (nextIsNumber(argc, argv, i)) {
				method = atoi(argv[i+1]);
			}
		}
		if (stringsEqual(argv[i], "--start") || stringsEqual(argv[i], "-s")) {
			if (nextIsNumber(argc, argv, i)) {
				start = atoull(argv[i+1]);
			}
		}
		if (stringsEqual(argv[i], "--explicit") || stringsEqual(argv[i], "-e")) {
			exstart = 1;
		}
		if (stringsEqual(argv[i], "--base") || stringsEqual(argv[i], "-b")) {
			if (nextIsNumber(argc, argv, i)) {
				base = atoi(argv[i+1]);
			}
		}
	}

	if (!quiet) {
		printf("\n%s%s%s%s\n",
			"largeprimes  Copyright (C) 2020  Nate Choe\n",
			"This program comes with ABSOLUTELY NO WARRANTY.'.\n",
			"This is free software, and you are welcome to redistribute it\n",
			"under certain conditions; type see license.txt for details.\n"
		);
	}

	printf("%lu\n", find(start, base, method, quiet, exstart));
	return 0;
}
