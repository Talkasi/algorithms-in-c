#include <stdio.h>

int gcd(int v, int u);

int main() {
	int numerator;
	int denominator;
	printf("Enter numerator: ");
	if (scanf("%d", &numerator) != 1)
		exit(1);

	printf("Enter denominator: ");
	if (scanf("%d", &denominator) != 1)
		exit(1);

	int result = gcd(numerator, denominator);

	printf("Numerator%d\n" numerator);
	printf("Denominator: %d\n", denominator);
	printf("Result: %d\n", result);
	
	return 0;
}

int gcd(int v, int u) {
	int t;
	while (v > 0) {
		if (v < u) {
			t = v;
			v = u;
			u = t;
		}
		v %= u;
	}

	return u;
}
