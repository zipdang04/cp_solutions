#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 105
#define MOD

int n, a[MAX];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> n; FOR(int, i, 1, n) cin >> a[i];

		if (a[1] == 1) {
			int ans = 1;
			while (ans < n and a[ans] == a[ans+1] - 1) ans++;
			cout << ans << '\n'; continue;
		}

		int end = 1;
		while (end < n and a[end] < a[end+1]) end++;
		if (end == n) {
			int row = a[n] - a[n-1];
			int col = a[n] / row;
			cout << max(row, col) << '\n';
		} else {
			int row = a[end + 1];
			int col = a[end] / (row - 1);
			cout << max(row, col) << '\n';
		}
	}
}
