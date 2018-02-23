#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;
int d[100001], c[100001], x[5][100001], f[100001];
int k0, k1, n, j, m;
int test(int n);
//////////////////////////////////////
void A(int x) {
	int i;
	for (i = 1; i <= x; i++) {
		swap(d[i], d[i + x]);
	}
	//////////////////////////////////
	cout << "A(" << x << ") : ";
	for (i = 1; i <= n; i++) {
		cout << d[i] << " ";
	}
	cout << endl;
}
void B() {
	swap(d[1], d[n / 2 + 1]);
	//////////////////////////////////
	cout << "B() : ";
	for (int i = 1; i <= n; i++) {
		cout << d[i] << " ";
	}
	cout << endl;
}
//////////////////////////////////////
void ex_hunt(int p)
{
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
	if (beta == 1) goto hunt_end;
	if (beta == 2) goto hunt_end2;
hunt_restart:
	if (((2 * alpha - 1) / beta) == 1) {
		A(beta / 2);
		x[gamma][k] = beta / 2;
		k++;
	}
	beta /= 2;
	alpha % beta == 0 ? alpha = alpha : alpha %= beta;
	if (beta == 2) goto hunt_end2;
	else goto hunt_restart;

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
	else if (a > (m / 2) && b > (m / 2)) {
		A(n / 2);
		hunt(a - (n / 2), n / 2, 0);
		B();
		hunt(b - (n / 2), n / 2, 1);
		B();
		ex_hunt(1);
		B();
		ex_hunt(0);
		A(n / 2);
		goto asdf;
	}
	else {
		hunt(a, n / 2, 0);
		A(n / 2);
		hunt(b - (n / 2), n / 2, 1);
		B();
		ex_hunt(1);
		A(m / 2);
		ex_hunt(0);
		goto asdf;
	}
asdf:
	swap(c[d[a]], c[d[b]]);
	swap(f[a], f[b]);
	cout << "//////////////////////////////////////" << endl;
	return;
}
//////////////////////////////////////
int main()
{
	int i;
	cin >> m;
	test(m);

	while (m < n) n *= 2;
	i = 1;
	while (i < n) {
		f[i] = 1;
		i++;
	}
	i = m + 1;
	while (i < n) {
		d[i] = INT_MAX;
		i++;
	}

	i = 1;
main_b:
	j = i + 1;
main_a:
	if (d[i] > d[j]) d[i]++;
	else d[j]++;
	j++;
	if (j <= n) goto main_a;
	if (i <= n) goto main_b;
	for (i = 1; i < m; i++) c[f[i]] = i;
	for (i = m; i > 1; i--) xbox(c[i], i);

	cout << endl;
	for (i = 1; i <= n; i++) {
		cout << d[i] << " ";
	}
	cout << endl;
	return 0;
}
//////////////////////////////////////
int test(int n)
{
	int is_test, i;
	cin >> is_test;
	if (!is_test) {
		for (i = 1; i <= n; i++) {
			cin >> d[i];
		}
	}
	else {
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 10);
		for (i = 1; i <= n; i++) {
			d[i] = distribution(generator);
		}
	}
	return 0;
}