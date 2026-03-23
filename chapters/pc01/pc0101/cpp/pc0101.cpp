/**
 * pc110101
 * uva100
 */

 #include <cstdio>

 int calculateCollatzLen(int num) {
	int collatzLen = 1;

	long current = (long)num;
	while (current != 1) {
		if (current & 1) {
			current += (current << 1) + 1;
		} else {
			current = current >> 1;
		}
		collatzLen++;
	}

	return collatzLen;
}

int findHighestCollatzLen(int i, int j) {
	int highestCollatzLen;

	int min = (i < j) ? i : j;
	int max = (i > j) ? i : j;

	highestCollatzLen = 1;
	for (int num = min; num <= max; num++) {
		int collatzLen = calculateCollatzLen(num);
		if (collatzLen > highestCollatzLen) {
			highestCollatzLen = collatzLen;
		}
	}

	return highestCollatzLen;
}

int main(void) {
	int i;
	int j;

	while (scanf("%d %d", &i, &j) == 2) {
		int highestCollatzLen = findHighestCollatzLen(i, j);
		printf("%d %d %d\n", i, j, highestCollatzLen);
	}

	return 0;
}