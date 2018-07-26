#include <iostream>
#include <algorithm>
using namespace std;
int d[100001];
int k0, k1, n, j, m;
//////////////////////////////////////
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
//////////////////////////////////////
/*
int max(int n, int m)
{
	int i, maxidx, max = INT_MIN;
	for (i = n; i <= m; i++) {
		if (max < d[i]) {
			max = d[i];
			maxidx = i;
		}
	}
	return maxidx;
}
*/
int chkSrt(int n)
{
	int size1, size2, i;
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
		if (!bgAr) return 2;
		return 1;
	}
}
//////////////////////////////////////

void s1(int n)
{
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

	return;
}
//////////////////////////////////////
void s2(int n)
{
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 < cnt2) A(n / 2);
	return;
}
void s2_R(int n)
{
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 > cnt2) A(n / 2);
	return;
}
//////////////////////////////////////
void s3(int n)
{
	int i, min, minidx;
	min = d[1];
	minidx = 1;

	if (d[n] < d[1]) A(n);

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

	return;
}
int proc(int n, int m)
{
	int chkStat;
	/*	auto chk = [n, m]() {
			int chkStat;
			if (chkStat = chkSrt(n)) {
				if (chkStat == 2) A(n / 2);
				proc(n, m / 2);
				A(n / 2);
				proc(n, m / 2);
				return 0;
			}};*/
	while (1) {
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		s1(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		s2(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		s3(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		B(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		s3(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		s2_R(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		s1(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
		B(n);
		if (chkStat = chkSrt(m - n + 1)) {
			if (chkStat == 2) A(n / 2);
			proc(n, m / 2);
			A(n / 2);
			proc(n, m / 2);
			return 0;
		}
	}
}
//////////////////////////////////////
int main()
{
	int i;
	cin >> n;
	for (i = 1; i <= n; i++) cin >> d[i];
	proc(1, n);
	return 0;
}