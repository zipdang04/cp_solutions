#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 200005
#define MOD

int n, l, r;
int a[MAX];
ll sum[MAX];

ll test(ll coef) {
	// small: p - a[i] => coef++
	// large: a[i] - p => coef--
	ll small = max(0ll, coef), large = max(0ll, -coef), add = (n - (small + large)) / 2;
	small += add, large += add;

	ll ans = (sum[n] - sum[n - large]) - (sum[small]);
	ans += coef * (coef < 0 ? r : l);
	return ans;
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		ll ans = 0;
		FOR(int, coef, -n, n)
			maximize(ans, test(coef));
		cout << ans << '\n';
		clear();
	}
}
void input() {
	cin >> n >> l >> r;
	FOR(int, i, 1, n) cin >> a[i];
	sort(a + 1, a + 1 + n);
	FOR(int, i, 1, n) sum[i] = sum[i-1] + a[i];
}
void clear() {
	FOR(int, i, 1, n) sum[i] = 0;
}
