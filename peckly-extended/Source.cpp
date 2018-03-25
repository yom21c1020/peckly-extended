#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <fstream>
using namespace std;
int d[10001], c[10001], x[2][10001], f[10001];
int k0, k1, n = 1, j, m;
int cnt = 0;
ofstream out("result.txt");
ofstream max_output("max.txt");
int test(int n);
int finderr(void);
//////////////////////////////////////
void A(int x) {
	int i;
	for (i = 1; i <= x; i++) {
		swap(d[i], d[i + x]);
	}
	cnt++;
	//////////////////////////////////
	out << "A(" << x << ") : ";
	for (i = 1; i <= n; i++) {
		out << d[i] << " ";
	}
	out << endl;
}
void B() {
	swap(d[1], d[n / 2 + 1]);
	cnt++;
	//////////////////////////////////
	out << "B() : ";
	for (int i = 1; i <= n; i++) {
		out << d[i] << " ";
	}
	out << endl;
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
	//alpha % beta == 0 ? alpha = beta : alpha %= beta;
	if (alpha % beta == 0) alpha = beta;
	else alpha %= beta;
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
		ex_hunt(0);
		hunt(b, n / 2, 1);
		B();
		ex_hunt(1);
		hunt(a, n / 2, 0);
		B();
		ex_hunt(0);
		goto asdf;
	}
	else if (a > (n / 2) && b > (n / 2)) {
		A(n / 2);
		hunt(a - (n / 2), n / 2, 0);
		B();
		ex_hunt(0);
		hunt(b - (n / 2), n / 2, 1);
		B();
		ex_hunt(1);
		hunt(a - (n / 2), n / 2, 0);
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
		A(n / 2);
		ex_hunt(0);
		goto asdf;
	}
asdf:
	swap(c[f[a]], c[f[b]]);
	swap(f[a], f[b]);
	//cout << "//////////////////////////////////////" << endl;
	return;
}
//////////////////////////////////////
int proc() {
	int i;
	while (m > n) n *= 2;
	for (i = 1; i <= n; i++) f[i] = 1;
	for (i = m + 1; i <= n; i++) d[i] = INT_MAX;

	for (i = 1; i < n; i++) {
		for (j = i + 1; j <= n; j++) {
			if (d[i] > d[j]) f[i]++;
			else f[j]++;
		}
	}

	for (i = 1; i <= m; i++) c[f[i]] = i;

	for (i = m; i >= 1; i--) xbox(c[i], i);
	return 0;
}
//////////////////////////////////////
int main()
{
	cin >> m;
	//test(m);
	finderr();
	proc();

	//cout << endl;
	//for (int i = 1; i <= m; i++) {
	//	cout << d[i] << " ";
	//}
	//cout << endl;

	system("pause");
	return 0;
}
//////////////////////////////////////
int test_inf(int n)
{
	int i;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 10);
	for (i = 1; i <= n; i++) {
		d[i] = distribution(generator);
	}

	return 0;
}

int finderr() {
	int inputData[10001], m_cnt = 0, m_inputData[10001];
	while (1) {
		test_inf(m);
		for (int i = 1; i <= n; i++)
			inputData[i] = d[i];
		proc();
		if (cnt > m_cnt) {
			m_cnt = cnt;		
			for (int i = 1; i <= n; i++) m_inputData[i] = inputData[i];
			max_output << m_cnt << endl;
			for (int i = 1; i <= n; i++) max_output << m_inputData[i] << " ";
			max_output << endl;
		}
		cnt = 0;


		return 0;
	}
}
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
