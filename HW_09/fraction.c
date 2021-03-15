#include <stdio.h>

typedef struct {
	long long numerator;
	long long denominator;
} Fraction;

Fraction CreateFrac(long long p, long long q) {
    Fraction F;
    F.numerator = p;
    F.denominator = q;
    return F;
}

long long GreatestCommonDivisor(long long x, long y) {
    if (y == 0)
        return x;
    else
        return GreatestCommonDivisor(y, x % y);
}

void Reduction(Fraction *F) {
    long long gcd = GreatestCommonDivisor(F->numerator, F->denominator);
    F->numerator /= gcd;
    F->denominator /= gcd;
}

Fraction Add(Fraction f1, Fraction f2) {
    Fraction F;
    F.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    F.denominator = f1.denominator * f2.denominator;
    Reduction(&F);
    return F;
}

Fraction Sub(Fraction f1, Fraction f2) {
    Fraction F;
    F.numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    F.denominator = f1.denominator * f2.denominator;
    Reduction(&F);
    return F;
}
Fraction Mul(Fraction f1, Fraction f2) {
    Fraction F;
    F.numerator = f1.numerator * f2.numerator;
    F.denominator = f1.denominator * f2.denominator;
    Reduction(&F);
    return F;
}
Fraction Div(Fraction f1, Fraction f2) {
    Fraction F;
    F.numerator = f1.numerator * f2.denominator;
    F.denominator = f1.denominator * f2.numerator;
    Reduction(&F);
    return F;
}
int Compare(Fraction f1, Fraction f2) {
    long long F1 = f1.numerator * f2.denominator;
    long long F2 = f2.numerator * f1.denominator;
    return F1 > F2;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int type, p1, q1, p2, q2;
		scanf("%d %d/%d %d/%d", &type, &p1, &q1, &p2, &q2);
		Fraction f1 = CreateFrac(p1, q1), f2 = CreateFrac(p2, q2), ans;
		switch (type) {
			case 0:
				ans = Add(f1, f2);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 1:
				ans = Compare(f1, f2) ? Sub(f1, f2) : Sub(f2, f1);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 2:
				ans = Mul(f1, f2);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 3:
				ans = Div(f1, f2);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 4:
				Reduction(&f1), Reduction(&f2);
				printf("%lld/%lld %lld/%lld\n", f1.numerator, f1.denominator, f2.numerator, f2.denominator);
				break;
		}
	}
    return 0;
}
