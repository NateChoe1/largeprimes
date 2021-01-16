#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct Node {
	int value;
	struct Node *next;
};

int gcf(int a, int b) {
	if (a == 0) return b;
	return gcf(b%a, a);
}

char coprime(int a, int b) {
	return (gcf(a, b) == 1);
}

struct Node getCoprimes(int base) {
	struct Node head;
	struct Node *iterator = &head;
	for (int i = 1; i < base; i++) {
		if (coprime(i, base)) {
			iterator->value = i;
			iterator->next = malloc(sizeof(struct Node));
			iterator = iterator->next;
		}
	}

	return head;
}

char isPrime(unsigned long long check) {
	unsigned long long power = 1;
	for (int i = 0; i < check - 1; i++) {
		power <<= 2;//In an experiment I did in python, Fermat's little theorem was pretty slow. Hopefully, bit shifting should speed it up.
		power %= check;
	}
	return (power == 1);
}

char isPrimeProvide(unsigned long long check, int base, struct Node *coprimes) {
	if (check % 2 == 0) return 0;
	for (int i = 3; i < ceil(sqrt((double) check)) + 1; i += 2) {
		if (check % i == 0) return 0;
	}
	//At this point there is no way that check is divisible by a number less than base.
	for (int i = base; i < ceil(sqrt((double) check)) + 1; i += base) {
		//The reason for this weird looping is because to test primality, you only need to divide by the primes. Because every number cocompossite to base is definitely compossite, they don't have to be divided.
		struct Node *iterator = coprimes;
		while (iterator != NULL) {
			if (check % i + iterator->value == 0) return 0;
			iterator = iterator->next;
		}
	}

	return 1;
}

char isPrimeBase(unsigned long long check, int base) {
	struct Node head = getCoprimes(base);
	char isPrimeBase = isPrimeProvide(check, base, &head);
	struct Node *iterator = &head;
	while (iterator != NULL) {
		struct Node *next = iterator->next;
		free(iterator);
		iterator = next;
	}
	return isPrimeBase;
}

unsigned long long find(unsigned long long start, int base) {
	/* 
	 * All primes are either above or below multiples
	 * of 6 (except 2 and 3). This  is  because  only
	 * numbers 1 above or 5 above  multiples of 6 are
	 * coprime to 6. This means every other number is
	 * cocompossite and therefore not prime. This can
	 * be done  with any number.  Instead of 1 and 5,
	 * use all  the  numbers coprime  to the base. To
	 * actually test primality,  you can use Fermat's
	 * little theorem.
	 * */
	if (start < base) {
		for (start += (start - 1) % 2; start < base; start += 2) {
			if (isPrime(start)) return start;
		}
	}

	struct Node head = getCoprimes(base);
	struct Node *iterator = &head;
	while (iterator->next->next != NULL) {
		iterator = iterator->next;
	}
	free(iterator->next);
	iterator->next = NULL;

	unsigned long long block = start - start % base;
	char notfound = 1;
	unsigned long long blocksCompleted = 0;
	while (notfound) {
		iterator = &head;
		while (iterator != NULL) {
			unsigned long long candidate = block + iterator->value;
			//if (candidate < start) continue;
			if (isPrimeProvide(candidate, base, &head)) {
			//if (isPrimeBase(candidate, base)) {
			//if (isPrime(candidate)) {
				return candidate;
			}
			iterator = iterator->next;
			printf("Just checked a prime %lu\n", candidate);
		}
		start += base;
		blocksCompleted++;
		printf("%lu blocks completed\n", blocksCompleted);
	}
	return 0;
}
