#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
//Start of Array = 1
int s[100001];
void randomize(int n);
class Grouping {
public:
	void A(int x) {
		int i;
		for (i = 1; i <= x; i++) {
			swap(s[i], s[i + x]);
		}
	}
	void B(int n) {
		swap(s[1], s[n / 2 + 1]);
	}
	void g1(int n) {
		int x = n / 4;
		int alpha, beta;
		while (1) {
			for (int i = 1; i <= n / 2; i++) {
				if (s[i] <= n / 2) {
					alpha = i;
					break;
				}
			}
			if ((alpha - 1) / x != 0) A(x);
			x /= 2;
			if (x == 0) break;
		}
		A(n / 2);
		x = n / 4;
		while (1) {
			for (int i = n / 2 + 1; i <= n; i++) {
				if (s[i] > n / 2) {
					beta = i;
					break;
				}
			}
			if ((beta - 1) / x != 0) A(x);
			x /= 2;
			if (x == 0) break;
		}
		B(n);
	}
	void G(int n) {
		int cnt = 0;
		int i;
		for (i = 1; i <= n / 2; i++) {
			if (s[i] <= n / 2) cnt++;
		}

		if (cnt == 0) {
			A(n / 2);
		}
		else if (cnt == n / 2) {

		}
		else if (cnt == 1) {
			g1(n);
		}
		else if (cnt >= 2 && cnt <= n / 4) {
			g1(n);
			G(n);
		}
		else if (cnt >= n / 4 && cnt <= n / 2) {
			A(n / 2);
			g1(n);
			G(n);
		}
	}
};

class Ghana : Grouping {
public:
	int findErr(int x, int y, bool albt) { // x - 시작 위치, y - 끝 위치, albt - 알파/베타(False - 알파, True - 베타)
		for (int i = x; i <= y; i++) {
			if (albt == false) if ((s[i] % 2 * y ? s[i] % 2 * y : 2 * y) >= y + 1) return i;
			else if (albt == true) if ((s[i] % 2 * y ? s[i] % 2 * y : 2 * y) <= y) return i;
		}
		return -1;
	}
	void fnc(int n) {
		int x = n / 2;
		int m = x / 2;
		int errLoc;
		while (1) {
			errLoc = findErr(1, m, false);
			if (errLoc != -1) {
				if (2 * errLoc / m != 0) A(m / 2);
				m /= 2;
				if (m == 0) break;
			}
			else break;
			B(n);
		}

		A(x / 2);
		m = x / 2;
		while (1) {
			errLoc = findErr(1, m, true);
			if (errLoc != -1) {
				if (2 * errLoc / m != 0) A(m / 2);
				m /= 2;
				if (m == 0) break;
			}
			else break;
			B(n);
		}
		A(x / 2);
		B(n);
	}
public:
	void Gh(int x) {
		if (x == 1) return;
		while (1) {
			s[1];
			int errLoc = findErr(1, x / 2, false);
			if (errLoc == -1) break;
			fnc(x);
		}
		Gh(x / 2);
		Gh(x / 2);
		return;
	}
};

int main()
{
	int n;
	cin >> n;
	int i;

	for (i = 1; i <= n; i++) {
		cin >> s[i];
	}

	//randomize(n);
	Grouping Grp;
	Ghana Ghn;
	//int y;
	//cin >> y;
	//cout << Ghn.findErr(1, y, false) << " " << Ghn.findErr(1, y, true) << endl;

	Grp.G(n);
	Ghn.Gh(n / 2);
	Grp.A(n / 2);
	Ghn.Gh(n / 2);
	if (s[1] != 1) Grp.A(n / 2);
	for (i = 1; i <= n; i++) {
		cout << s[i] << " ";
	}
	cout << endl;

	return 0;
}

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