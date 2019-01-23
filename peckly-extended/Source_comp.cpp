#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#pragma warning(disable:4996)
using namespace std;
using namespace std::chrono;
int d[100001], input[100001], worstVal[100001]; // worstVal[0] : 최대 카운트, worstVal[1] ~ [n] : 최대값
int k0, k1, n, j, m, inputn, cnt;
////////////////////////////////////////
//Operator
void A(int x) {
	int i;
	for (i = 1; i <= x; i++) {
		swap(d[i], d[i + x]);
	}
	//////////////////////////////////
	//cout << "    A(" << x << ") : ";
	//for (i = 1; i <= n; i++) {
	//	cout << d[i] << " ";
	//}
	//cout << endl;
	cnt++;
}
void B(int x) {
	swap(d[1], d[x / 2 + 1]);
	//////////////////////////////////
	//cout << "    B(" << x << ") : ";
	//for (int i = 1; i <= n; i++) {
	//	cout << d[i] << " ";
	//}
	//cout << endl;
	cnt++;
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
	//cout << "St.1" << endl;
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
	//cout << endl;
	return;
}
void s2(int n)
{
	//cout << "St.2" << endl;
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 <= cnt2) A(n / 2);
	//cout << endl;
	return;
}
void s2_R(int n)
{
	//cout << "St.2_r" << endl;
	int i, cnt1, cnt2;
	cnt1 = cnt2 = 0;
	for (i = 1; i <= n / 2; i++) cnt1 += d[i];
	for (i = n / 2 + 1; i <= n; i++) cnt2 += d[i];
	if (cnt1 >= cnt2) A(n / 2);
	//cout << endl;
	return;
}
void s3(int n)
{
	//cout << "St.3" << endl;
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
	//cout << endl;
	return;
}
////////////////////////////////////////
//Recursive Processing
int proc(int n)
{
	//cout << "proc(" << n << ")" << endl;
	if (n <= 1) return 0;
	int chkStat;
	auto chk = [n](int chkStat) {
		if (chkStat == 2) A(n / 2);
		proc(n / 2);
		//cout << "End of proc(" << n / 2 << ")" << endl;
		if (n != 2) A(n / 2);
		proc(n / 2);
		//cout << "End of proc(" << n / 2 << ")" << endl;
		return 0;
	};
	while (1) {
		//chkStat = chkSrt(n);
		//if (chkStat) {
		//	chk(chkStat);
		//	return 0;
		//}
		s1(n);
		//chkStat = chkSrt(n);
		//if (chkStat) {
		//	chk(chkStat);
		//	return 0;
		//}
		s2(n);
		//chkStat = chkSrt(n);
		//if (chkStat) {
		//	chk(chkStat);
		//	return 0;
		//}
		s3(n);
		//chkStat = chkSrt(n);
		//if (chkStat) {
		//	chk(chkStat);
		//	return 0;
		//}
		//cout << "St.4" << endl;
		B(n);
		chkStat = chkSrt(n);
		if (chkStat) {
			chk(chkStat);
			return 0;
		}
		s3(n);
		//chkStat = chkSrt(n);
		//if (chkStat) {
		//	chk(chkStat);
		//	return 0;
		//}
		s2_R(n);
		//chkStat = chkSrt(n);
		//if (chkStat) {
		//	chk(chkStat);
		//	return 0;
		//}
		s1(n);
		//chkStat = chkSrt(n);
		//if (chkStat) {
		//	chk(chkStat);
		//	return 0;
		//}
		//cout << "St.4_R" << endl;
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
	//cout << "\n\nResult: ";
	//for (int i = n - inputn + 1; i <= n; i++) cout << d[i] << " ";
	//cout << endl;
}

bool chkSrt_(int n);
int testRandom(int n);
int makeArr(int n, int p, int q);
void sortTest(int n, int m);
int main()
{
	freopen("input.txt", "r", stdin);
	//srand((unsigned)time(NULL));
	//int i;
	//cin >> inputn;
	//for (i = 1; i <= inputn; i++) cin >> input[i];
	//testRandom(n);
	int n;
	int m;
	n = 1024;
	m = 500;
	//cin >> n >> m;
	//for (i = 1; i <= n; i++) cin >> d[i];
	//proc(n);
	//findpow(inputn);
	//makeArr(n, 1, n);
	sortTest(n, m);
	//cout << endl;
	//cout << worstVal[0] << endl;
	//for (int i = 1; i <= n; i++) cout << worstVal[i] << " ";
	//cout << endl;
	return 0;
}

int makeArr(int n, int p, int q) //p: 현재 idx, q: 마지막 idx
{
	int i;
	if (p > q) {
		findpow(n);
		if (cnt > worstVal[0]) {
			for (i = 1; i <= n; i++) {
				worstVal[i] = input[i];
			}
			worstVal[0] = cnt;
		}
		cnt = 0;
		return 0;
	}

	for (i = 1; i <= n; i++) {
		input[p] = i;
		makeArr(n, p + 1, q);
	}
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
////////////////////////////////////////////////////
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}
void CocktailSort(int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) {
		// reset the swapped flag on entering 
		// the loop, because it might be true from 
		// a previous iteration. 
		swapped = false;

		// loop from left to right same as 
		// the bubble sort 
		for (int i = start; i < end; ++i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}

		// if nothing moved, then array is sorted. 
		if (!swapped)
			break;

		// otherwise, reset the swapped flag so that it 
		// can be used in the next stage 
		swapped = false;

		// move the end point back by one, because 
		// item at the end is in its rightful spot 
		--end;

		// from right to left, doing the 
		// same comparison as in the previous stage 
		for (int i = end - 1; i >= start; --i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}

		// increase the starting point, because 
		// the last stage would have moved the next 
		// smallest number to its rightful spot. 
		++start;
	}
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element 
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		// pi is partitioning index, arr[p] is now
		//	at right place 
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// create temp arrays /
	int L[100001], R[100001];

	// Copy data to temp arrays L[] and R[] /
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r] /
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if there
	//	are any /
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if there
	//	are any /
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}
////////////////////////////////////////////////////

void sortTest(int n, int m)
{
	high_resolution_clock::time_point s, e;
	int i;
	////////////////////////////////////////////////
	s = high_resolution_clock::now();
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) cin >> input[j];
		findpow(n);
	}
	e = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(e - s).count();
	cout << "PECKLY Sort Done!\n  Time Elapsed: " << duration * (0.000001) << "s\n";
	////////////////////////////////////////////////
	s = high_resolution_clock::now();
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) cin >> input[j];
		bubbleSort(input, n);
	}
	e = high_resolution_clock::now();
	duration = duration_cast<microseconds>(e - s).count();
	cout << "Bubble Sort Done!\n  Time Elapsed: " << duration * (0.000001) << "s\n";
	////////////////////////////////////////////////
	s = high_resolution_clock::now();
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) cin >> input[j];
		CocktailSort(input, n);	
	}
	e = high_resolution_clock::now();
	duration = duration_cast<microseconds>(e - s).count();
	cout << "Cocktail Sort Done!\n  Time Elapsed: " << duration * (0.000001) << "s\n";
	////////////////////////////////////////////////
	s = high_resolution_clock::now();
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) cin >> input[j];
		quickSort(input, 1, n);
	}
	e = high_resolution_clock::now();
	duration = duration_cast<microseconds>(e - s).count();
	cout << "Quick Sort Done!\n  Time Elapsed: " << duration * (0.000001) << "s\n";
	////////////////////////////////////////////////
	s = high_resolution_clock::now();
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) cin >> input[j];
		mergeSort(input, 1, n);
	}
	e = high_resolution_clock::now();
	duration = duration_cast<microseconds>(e - s).count();
	cout << "Merge Sort Done!\n  Time Elapsed: " << duration * (0.000001) << "s\n";
	////////////////////////////////////////////////
	return;
}