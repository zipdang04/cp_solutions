#include <bits/stdc++.h>
using namespace std;

template<class T1, class T2> void minimize(T1& a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1& a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {

		int n, m; cin >> n >> m;
		if (n == 1) { cout << "1\n"; continue; }
		if (n == 2) {
			if (m % 2 == 1) cout << "2 1\n";
			else cout << "1 2\n";
			continue;
		}
		int times = min(m, n-1);
		vector<int> ans;
		FOR(int, i, 1, times) ans.push_back(n - i +1);
		FOR(int, i, 1, n-times) ans.push_back(i);
		// if (m >= n and (m-n) % 2 == 0)
		// 	swap(ans[n-1], ans[n-2]);
		FOR(int, i, 1, n) cout << ans[i-1] << " \n"[i == n];
	}

}