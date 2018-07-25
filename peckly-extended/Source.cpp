#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;
int d[100001];
int k0, k1, n, j, m;
int test(int n);
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
bool chkSrt()
{
	int i, prev = d[1];
	for (i = 2; i <= n; i++) {
		if (prev > d[i]) return 0;
		prev = d[i];
	}
	return 1;
}
//////////////////////////////////////

void s1()
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

	if (chkSrt()) 
		exit(0);
	return;
}
//////////////////////////////////////
void s2()
{
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 < cnt2) A(n / 2);
	if (chkSrt()) 
		exit(0);
	return;
}
void s2_R()
{
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 > cnt2) A(n / 2);
	if (chkSrt()) 
		exit(0);
	return;
}
//////////////////////////////////////
void s3()
{
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

	if (chkSrt()) 
		exit(0);
	return;
}
//////////////////////////////////////
int main()
{
	int i;
	cin >> n;
	for (i = 1; i <= n; i++) cin >> d[i];
	while (1) {
		cout << "St.1" << endl;
		s1();
		cout << "St.2" << endl;
		s2();
		cout << "St.3" << endl;
		s3();
		cout << "St.4" << endl;
		B(n);
		cout << "St.1_R" << endl;
		s3();
		cout << "St.2_R" << endl;
		s2_R();
		cout << "St.3_R" << endl;
		s1();
		cout << "St.4_R" << endl;
		B(n);
	}
	
	return 0;
}