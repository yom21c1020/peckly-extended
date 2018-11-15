#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
int d[100001], input[100001];
int k0, k1, n, j, m, inputn;
////////////////////////////////////////
//Operator
void A(int x) {
	int i;
	for (i = 1; i <= x; i++) {
		swap(d[i], d[i + x]);
	}
	//////////////////////////////////
	cout << "    A(" << x << ") : ";
	for (i = 1; i <= n; i++) {
		cout << d[i] << " ";
	}
	cout << endl;
}
void B(int x) {
	swap(d[1], d[x / 2 + 1]);
	//////////////////////////////////
	cout << "    B(" << x << ") : ";
	for (int i = 1; i <= n; i++) {
		cout << d[i] << " ";
	}
	cout << endl;
}
////////////////////////////////////////
int chkSrt(int n)
{
	long long int size1, size2, i;
	bool bgAr = false;
	size1 = size2 = 0;

	if (n == 2) {
		if (d[n] < d[1]) return 2;
		return 1;
	}
	for (i = 1; i <= n / 2; i++) size1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) size2 += d[i];

	if (size1 < size2) bgAr = true; // 1 ~ n/2 < n/2+1 ~ n
	int min = INT_MAX, max = INT_MIN, minidx, maxidx;

	for (i = 1; i <= n / 2; i++) {
		if (bgAr) {
			if (max < d[i]) { max = d[i]; maxidx = i; }
		}
		else {
			if (min > d[i]) { min = d[i]; minidx = i; }
		}
	}
	for (i = n / 2 + 1; i <= n; i++) {
		if (!bgAr) {
			if (max < d[i]) { max = d[i]; maxidx = i; }
		}
		else {
			if (min > d[i]) { min = d[i]; minidx = i; }
		}
	}
	if (max > min) return false;
	else {
		if (bgAr) return 2;
		return 1;
	}
}
////////////////////////////////////////
//Subroutine
void s1(int n)
{
	cout << "St.1" << endl;
	int i, max, maxidx;
	max = d[1];
	maxidx = 1;
	for (i = 1; i <= n / 2; i++) {
		if (max < d[i]) {
			max = d[i];
			maxidx = i;
		}
	}
	int curN = n / 2;
	while (maxidx != 1) {
		if (maxidx > curN / 2) {
			A(curN / 2);
			maxidx -= curN / 2;
		}
		curN /= 2;
	}
	cout << endl;
	return;
}
void s2(int n)
{
	cout << "St.2" << endl;
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 < cnt2) A(n / 2);
	cout << endl;
	return;
}
void s2_R(int n)
{
	cout << "St.2_r" << endl;
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 > cnt2) A(n / 2);
	cout << endl;
	return;
}
void s3(int n)
{
	cout << "St.3" << endl;
	int i, min, minidx;
	min = d[1];
	minidx = 1;

	for (i = 1; i <= n / 2; i++) {
		if (min > d[i]) {
			min = d[i];
			minidx = i;
		}
	}
	int curN = n / 2;
	while (minidx != 1) {
		if (minidx > curN / 2) {
			A(curN / 2);
			minidx -= curN / 2;
		}
		curN /= 2;
	}
	cout << endl;
	return;
}
////////////////////////////////////////
//Recursive Processing
int proc(int n)
{
	cout << "proc(" << n << ")" << endl;
	if (n <= 1) return 0;
	int chkStat;
	auto chk = [n](int chkStat) {
		if (chkStat == 2) A(n / 2);
		proc(n / 2);
		cout << "End of proc(" << n / 2 << ")" << endl;
		if (n != 2) A(n / 2);
		proc(n / 2);
		cout << "End of proc(" << n / 2 << ")" << endl;
		return 0;
	};
	while (1) {
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		s1(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		s2(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		s3(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		cout << "St.4" << endl;
		B(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		s3(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		s2_R(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		s1(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		cout << "St.4_R" << endl;
		B(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
	}
}

void findpow(int inputn)
{
	int n = 1;
	while (1) {
		if (n >= inputn) break;
		else n *= 2;
	}
	for (int i = 0; i <= n - inputn; i++) d[i] = INT_MIN;
	int temp = 1;
	for (int i = n - inputn + 1; i <= n; i++) d[i] = input[temp++];
	::n = n;
	proc(n);
	for (int i = n - inputn + 1; i <= n; i++) cout << d[i] << " ";
	cout << endl;
}

bool chkSrt_(int n);
int testRandom(int n);
int main()
{
	//srand((unsigned)time(NULL));
	int i;
	cin >> inputn;
	for (i = 1; i <= inputn; i++) cin >> input[i];
	//testRandom(n);
	//cin >> n;
	//for (i = 1; i <= n; i++) cin >> d[i];
	//proc(n);
	findpow(inputn);
	return 0;
}

bool chkSrt_(int n)
{
	int i, prev = d[1];
	for (i = 2; i <= n; i++) {
		if (prev > d[i]) return 0;
		prev = d[i];
	}
	return 1;
}
int d_o[100001];
int isUsed[100001];
int cnt;
int testRandom(int n)
{
	int i;

	for (i = 1; i <= n; i++) isUsed[i] = 0;
	for (i = 1; i <= n; i++) {
		int r;
	re:
		r = rand() % n + 1;
		if (isUsed[r]) goto re;
		d_o[i] = d[i] = r;
		isUsed[r] = 1;
	}
	//for (i = 1; i <= n; i++) cout << d[i] << " ";
	//cout << endl;
	cnt++;
	proc(n);

	if (!chkSrt_(n)) {
		cout << endl << endl << "Err: ";
		for (i = 1; i <= n; i++) {
			cout << d_o[i] << " ";
		}
		cout << endl;
		system("pause");
	}


	return 0;
}
