#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
//Start of Array = 1
int s[100001];
int G_n;
void randomize(int n);
class Grouping {
public:
	void A(int x, int n) {
		int i;
		for (i = 1; i <= x; i++) {
			swap(s[i], s[i + x]);
		}
		for (i = 1; i <= n; i++) cout << s[i] << " ";
		cout << endl;
	}
	void B(int n) {
		swap(s[1], s[G_n / 2 + 1]);
		for (int i = 1; i <= n; i++) cout << s[i] << " ";
		cout << endl;
	}
	void hunt(int a, int b, int n) {
		switch (b) {
		case 1: {
			return;
			break;
		}
		case 2: {
			if (a == 0 || a == 2) A(1,n);
			return;
			break;
		}
		default: {
		bIsntTwo:
			if ((2 * a - 1) / b == 0) {
				b /= 2;
				a %= b;
				if (b != 2) goto bIsntTwo;
				else if (a == 0 || a == 2) A(1, n);
				return;
			}
			else A(b / 2, n);
			break;
		}
		}
	}

	void G(int n) {
		int c, i, x, y;
	regroup:
		c = 0;
		for (i = 1; i <= n / 2; i++) {
			if (s[i] > n / 2) {
				x = i;
				c = 1;
				break;
			}
		}
		if (!c) return;
		for (i = n / 2 + 1; i <= n; i++) {
			if (s[i] <= n / 2) {
				y = i;
				break;
			}
		}
		hunt(x, n / 2, n);
		A(n / 2, n);
		y -= n / 2;
		hunt(y, n / 2, n);
		A(n / 2, n);
		B(n);
		goto regroup;
	}
};

class Ghana : Grouping {
public:
	int g(int a, int b) {
		if (a % b == 0) return b;
		else return a % b;
	}
	void fnc(int x)
	{
		int c, i, m, n;
	refnc:
		c = 0;
		for (i = 1; i <= x / 2; i++) {
			if (g(s[i], x) > x / 2) {
				m = i;
				c = 1;
				break;
			}
		}
		if (c == 0) return;
		for (i = x / 2 + 1; i <= x; i++) {
			if (g(s[i], x) <= x / 2) {
				n = i;
				break;
			}
		}
		hunt(m, x / 2, n);
		B(n);
		A(x / 2, n);
		n -= x / 2;
		hunt(n, x / 2, n);
		B(n);
		A(x / 2, n);
		B(n);
		goto refnc;
		return;
	}
	void Gh(int x, int n)
	{
		if (x == 1) return;
		fnc(x);
		Gh(x / 2, n);
		A(x / 2, n);
		Gh(x / 2, n);
		A(x / 2, n);
		return;
	}
};
int main()
{
	int n;
	cin >> n;
	G_n = n;
	int i;

	for (i = 1; i <= n; i++) {
		cin >> s[i];
	}

	//randomize(n);
	Grouping Grp;
	Ghana Ghn;
	/*int x, y;
	cin >> x >> y;
	cout << Ghn.findErr(x, y);*/

	Grp.G(n);
	Ghn.Gh(n / 2, n);
	Grp.A(n / 2, n);
	Ghn.Gh(n / 2, n);
	Grp.A(n / 2, n);
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