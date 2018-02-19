#include <iostream>
#include <algorithm>
using namespace std;
int d[100001], c[100001], x[5][100001];
int k0, k1, n, j;
//////////////////////////////////////
void A(int x) {
	int i;
	for (i = 1; i <= x; i++) {
		swap(d[i], d[i + x]);
	}
}
void B() {
	swap(d[1], d[n / 2 + 1]);
	swap(d[1], d[n / 2 + 1]);
}
//////////////////////////////////////
void ex_hunt(int p)
{
	int k;
	if (p == 0) j = k0;
	else j = k1;
	if (j == 0) return;
	while (1) {
		j--;
		A(x[p][j]);
		if (j <= 0) return;
	}
}
//////////////////////////////////////
void hunt(int alpha, int beta, int gamma) {
	int k = 0;
	if (beta != 1) {
		if (beta == 2) goto hunt_end2;
	hunt_restart:
		if ((2 * alpha - 1) / beta == 1) {
			A(beta / 2);
			x[gamma][k] = beta / 2;
			k++;
		}
		beta /= 2;
		alpha %= beta;
		if (beta == 2) goto hunt_end2;
		else goto hunt_restart;
	}
hunt_end2:
	if (alpha != 1) {
		A(1);
		x[gamma][k] = 1;
		k++;
	}
hunt_end:
	if (gamma == 1)	k1 = k;
	else k0 = k;
}
//////////////////////////////////////
void xbox(int a, int b)
{
	if (a == b) return;
	if (a > b) {
		swap(a, b);
	}
	if (a == 1 && b == 2) {
		A(1);
		goto asdf;
	}
	if (a == 1 && b == (n / 2) + 1) {
		B();
		goto asdf;
	}
	if (a <= (n / 2) && b <= (n / 2)) {
		hunt(a, n / 2, 0);
		B();
		hunt(b, n / 2, 1);
		B();
		ex_hunt(1);
		B();
		ex_hunt(0);
		goto asdf;
	}
	else if (a > (n / 2) && b > (n / 2)) {
		A(n / 2);
		a -= (n / 2);
		b -= (n / 2);
		hunt(a, n / 2, 0);
		B();
		hunt(b, n / 2, 1);
		B();
		ex_hunt(1);
		B();
		ex_hunt(1);
		B();
		ex_hunt(0);
		a += (n / 2);
		b += (n / 2);
		A(n / 2);
		goto asdf;
	}
	else {
		hunt(a, n / 2, 0);
		A(n / 2);
		b -= n / 2;
		hunt(b, n / 2, 1);
		B();
		ex_hunt(1);
		A(n / 2);
		ex_hunt(0);
		b += n / 2;
		goto asdf;
	}
asdf:
	swap(c[d[a]], c[d[b]]);
	return;
}
//////////////////////////////////////
int main()
{
	int i;
	cin >> n;

	i = 1;
a:
	c[d[i]] = i;
	if (i < n) {
		i++;
		goto a;
	}

	i = n;
b:
	xbox(c[i], i);
	if (i > 1) {
		i--;
		goto b;
	}
	return 0;
}