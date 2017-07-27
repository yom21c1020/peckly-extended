#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
using namespace std;

int s[100001];
void printS(int n) { for (int i = 1; i <= n; i++) cout << s[i] << " "; cout << endl; }
void randomize(int n);
void findErr();
class Grouping {
public:
	static int Start(int n) {
		return unit(n);
	}
	////////////////////////////////////////
protected:
	static void A(int x, int n) {
		int swap_array[10001];
		for (int i = 0; i <= 10000; i++) swap_array[i] = 0;
		for (int i = 1; i <= x; i++) {
			swap_array[i] = s[i];
		}
		for (int i = 1; i <= x; i++) {
			s[i] = s[i + x];
		}
		for (int i = x + 1; i <= x * 2; i++) {
			s[i] = swap_array[i - x];
		}
		//////////
		cout << "A: ";
		printS(n);
		//////////
		return;
	}
	////////////////////////////////////////
	static void B(int n) {
		int x = n / 2;
		swap(s[1], s[x + 1]);
		//////////
		cout << "B: ";
		printS(n);
		//////////
		return;
	}
	static void findGhana(int n, int *a, int *b) {
		for (int i = 1; i <= n / 2; i++) {
			if (s[i] >= 1 && s[i] <= n / 2) {
				*a = i;
				break;
			}
		}
		for (int i = n / 2 + 1; i <= n; i++) {
			if (s[i] >= n / 2 + 1 && s[i] <= n) {
				*b = i;
				break;
			}
		}
		return;
	}
	//End of declaration protected objects
private:
	static void g1(int alpha, int beta, int n) {
		int x = n / 4;
		cout << alpha << " " << beta << endl;
		while (1) {
			if ((alpha - 1) / x != 0) A(x, n);
			findGhana(n, &alpha, &beta);
			x /= 2;
			if (x == 0) break;
		}
		A(n / 2, n);
		findGhana(n, &alpha, &beta);
		x = n / 4;
		while (1) {
			if ((beta - 1) / x != 0) A(x, n);
			findGhana(n, &alpha, &beta);
			x /= 2;
			if (x == 0) break;
		}
		B(n);
	}
	////////////////////////////////////////
	static int unit(int n) {
		int p[100001];
		int i, cnt = 0;
		for (i = 0; i <= 100000; i++) p[i] = 0;
		for (i = 1; i <= n / 2; i++) {
			if (s[i] >= 1 && s[i] <= n / 2) {
				p[i] = 1;
				cnt++;
			}
		}
		for (i = n / 2 + 1; i <= n; i++) {
			if (s[i] >= n / 2 + 1 && s[i] <= n) {
				p[i] = 1;
			}
		}
		cout << cnt << endl;
		if (cnt == 0) {
			A(n / 2, n);
		}
		else if (cnt == n / 2) {

		}
		else if (cnt == 1) {
			int a, b;
			for (i = 1; i <= n / 2; i++) {
				if (p[i] == 1) {
					a = i;
					break;
				}
			}
			for (i = n / 2 + 1; i <= n; i++) {
				if (p[i] == 1) {
					b = i;
					break;
				}
			}
			g1(a, b, n);
		}
		else if (cnt >= 2 && cnt <= n / 4) {
			int a, b;
			for (i = 1; i <= n / 2; i++) {
				if (p[i] == 1) {
					a = i;
					break;
				}
			}
			for (i = n / 2 + 1; i <= n; i++) {
				if (p[i] == 1) {
					b = i;
					break;
				}
			}
			g1(a, b, n);
			unit(n);
		}
		else if (cnt >= n / 4 && cnt <= n / 2) {
			A(n / 2, n);
			int swap_array[100001];
			for (int i = 1; i <= n / 2; i++) {
				swap_array[i] = p[i];
			}
			for (int i = 1; i <= n / 2; i++) {
				p[i] = p[i + n / 2];
			}
			for (int i = n / 2 + 1; i <= n; i++) {
				p[i] = swap_array[i];
			}

			int a, b;
			for (i = 1; i <= n / 2; i++) {
				if (p[i] == 1) {
					a = i;
					break;
				}
			}
			for (i = n / 2 + 1; i <= n; i++) {
				if (p[i] == 1) {
					b = i;
					break;
				}
			}
			g1(a, b, n);
			unit(n);
		}

		cout << cnt << endl;
		return cnt;
	}
};
////////////////////////////////////////
class Ghana : Grouping {
public:
	static void Start(int n) {
		chocolate(n);
		return;
	}
private:

	static void chocolate(int n) {
		int m = 4, x, gha, na;
		while (1) {
			x = n / m;
			while (1) {
				findGhana(n, &gha, &na);
				if ((gha - 1) / x != 0) A(x, n);
				x /= 2;
				if (x == 0) break;
			}
			B(n);
			A(n / m, n);
			x = n / m;
			while (1) {
				if ((na - 1) / x != 0) A(x, n);
				x /= 2;
				if (x == 0) break;
			}
			B(n);
			A(n / m, n);
			B(n);
			m *= 2;
			if (m > n) break;
		}
		for (int i = 1; i <= n / 2; i++) {
			if (s[i] != i) {
				A(n / 2, n);
				break;
			}
		}
		return;
	}
};
////////////////////////////
//End of class declaration//
////////////////////////////

int main()
{
	int n;
	cin >> n;
	randomize(n); //Make random data

	int i;
	/*
	cin >> n;
	for (i = 1; i <= n; i++) { //Input from user
	cin >> s[i];
	}
	*/
	for (i = 1; i <= n; i++) { //Output starting
		cout << s[i] << " ";
	}
	cout << endl;


	Grouping::Start(n); //Starting grouping
	Ghana::Start(n); //Starting ghana algorithm

					 //findErr(); //Call error find function
	return 0;
}
/////////////////
//End of main()//
/////////////////
void randomize(int n)
{
	std::random_device rn;
	std::mt19937 mtRand(time(NULL));
	int i, a;
	int d[100001];
	for (i = 0; i <= 100000; i++) {
		d[i] = 0;
	}
	for (i = 1; i <= n; i++) {
	re:
		a = mtRand() % n + 1;

		if (d[a] != 1) {
			d[a] = 1;
			s[i] = a;
		}
		else goto re;
	}
	return;
}
/////////////
void findErr()
{
	int i, k, n, cnt = 0;
	int original_data[10];
	cin >> n;
	randomize(n);
	for (k = 1; k <= n; k++) original_data[k] = s[k];
	Grouping::Start(n);
	Ghana::Start(n);
	while (1) {
		for (k = 1; k <= n; k++) {
			if (s[k] != k) goto ERR;
		}
		randomize(n);
		for (k = 1; k <= n; k++) original_data[k] = s[k];
		Grouping::Start(n);
		Ghana::Start(n);
		cnt = 0;
	}

ERR:
	cout << endl << endl;

	for (i = 1; i <= n; i++) {
		cout << original_data[i] << " ";
	}
	return;
}	