#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
	int n; cin >> n;

	ll sum = 0;

	for (int i = 1; i <= n/2; i++) {
		ll x; cin >> x;
		sum += x;
	}

	for (int i = 1; i <= n/2; i++) {
		ll x; cin >> x;
		sum -= x;
	}

	cout << abs(sum);

	


	
}