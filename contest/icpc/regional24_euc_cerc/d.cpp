#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	if (b < a) return a = b, true; return false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	if (b > a) return a = b, true; return false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX
#define MOD

ull mul(ull a, ull b, ull mod) {
	// ull oldA = a, oldB = b;
	return __int128(a) * __int128(b) % __int128(mod);
}
ull pw(ull a, ull n, ull mod) {
	// ull oldA = a, oldB = n;
	ull ans = 1;
	while (n) {
		if (n & 1) ans = mul(ans, a, mod);
		a = mul(a, a, mod), n >>= 1;
	}
	// cerr << oldA<< '^' << oldB << '%' << mod << '=' << ans << '\n';
	return ans;
}

bool isPrime(ull n) {
	if (n < 2 or n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
		s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a: A) {
		ull p = pw(a%n, d, n), i = s;
		while (p != 1 and p != n-1 and a % n and i--)
			p = mul(p, p, n);
		if (p != n-1 and i != s) return false;
	}
	return true;
}

ull pollard(ull n) {
	auto f = [n](ull x) {
		return mul(x, x, n) + 1;
	};

	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		// cerr << t << '\n';
		if (x == y) x = ++i, y = f(x);
		if ((q = mul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	// cerr << n << "isnotprime\n";
	ull x = pollard(n);
	// cerr << "hehe\n";
	auto l = factor(x), r = factor(n/x);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int t; cin >> t;
	FOR(int, _, 1, t) {
		ull n; cin >> n;
		string haha = to_string(n); sort(haha.begin(), haha.end());
		unordered_map<ull, int> pw;
		for (ull p: factor(n)) pw[p]++;

		vector<ull> allD = {n};
		int ans = 0;
		for (auto [p, x]: pw) {
			int sz = allD.size();
			FOR(int, i, 0, sz-1) {
				ull newNum = allD[i];
				FOR(int, j, 1, x) {
					newNum /= p;
					string hihi = to_string(newNum);
					if (hihi.length() < haha.length()) continue;
					allD.push_back(newNum);
					sort(hihi.begin(), hihi.end());
					ans += haha == hihi;
				}
			}
		}
		// cerr << '\n';
		cout << ans << '\n';
	}
}
