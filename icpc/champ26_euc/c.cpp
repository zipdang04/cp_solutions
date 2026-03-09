#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> bool minimize(T1 &a, T2 b) {
	return (b < a) ? (a = b, true) : false;
}
template<class T1, class T2> bool maximize(T1 &a, T2 b) {
	return (b > a) ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(n) __builtin_popcountll(n)
#define log2ll(n) (63-__builtin_clz(n))

#define MAX 1000'000
#define MOD

#define copy(x) ((x)+2)
/*
 * obs1: either two action:
 * - a
 * - ctrl+acvvvvvvvv
 * 
 * obs2:
 * - x n: a+c+v*(n-1)
 */

// #ifndef HIEU
// int f[MAX + 5];
// void preCal() {
// 	f[1] = 1;
// 	for (int i = 1; i <= MAX; i++) {
// 		minimize(f[i], f[i-1] + 1);
// 		for (int j = 2; i * j <= MAX; i++)
// 			minimize(f[j], f[i] + copy(j));
// 	}
// }
// #endif

unordered_map<ll, int> fBig;
ll dp(ll n, ll minusable = 10, int limit = 240) {
	// #ifndef HIEU
	// if (n <= MAX) return f[n];
	// #endif
	auto it = fBig.find(n);
	if (it != fBig.end() and it -> second > 0) 
		return it -> second;
	if (n == 1) return fBig[n] = 1;
	
	// if called twice, must finished
	if (it != fBig.end()) limit = 240, maximize(minusable, 1);	

	// cerr << "calling " << n << '\n';
	int best = INT_MAX;
	for (int d = 2; d+2 <= min(best,limit) and d * d <= n; d++) if (n % d == 0) {
		ll remain = n / d;
		minimize(best, dp(remain) + copy(d));
		if (remain+2 <= min(best, limit))
			minimize(best, dp(d) + copy(remain));
	}

	if (minusable > 0 or best == INT_MAX) 
		minimize(best, dp(n-1, minusable - 1, min(best, limit)) + 1);
	if (best == INT_MAX) return INT_MAX;
	// cerr << n << " => " << best << '\n';
	return fBig[n] = best;
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	ll n; cin >> n;
	cout << dp(n);
}
void input() {}
void clear() {}
