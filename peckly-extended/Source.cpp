#include <iostream>
#include <algorithm>
using namespace std;
//Start of Array = 1
int s[100001];
class Grouping {
	void A(int x) {
		int i;
		for (i = 1; i <= x; i++) {
			swap(s[i], s[i + x]);
		}
	}
	void B(int n) {
		swap(s[1], s[n / 2 + 1]);
	}
	void G(int n) {
		int cnt = 0;
		int i;
		for (i = 1; i <= n / 2; i++) {
			if (s[i] <= n / 2) cnt++;
		}		
		if (cnt == 0) {

		}
		else if (cnt == n / 2) {
			
		}
		else if(cnt == 1){
		
		}
		else if(cnt >= 2 && cnt <= n/4) {
		
		}
		else if (cnt >= n / 4 && cnt <= n / 2) {
		
		}
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
	
	return 0;
}