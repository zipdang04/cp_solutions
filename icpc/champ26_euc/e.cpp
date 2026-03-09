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

#define MAX 1'000'005
#define MOD 1'000'000'007

struct modint {
	ll v;
	modint(ll v = 0): v(v % MOD) {}
	modint operator + (const modint a) const {return (v + a.v) % MOD;}
	modint operator - (const modint a) const {return (v + MOD - a.v) % MOD;}
	modint operator * (const modint a) const {return (v * a.v) % MOD;}
	inline static modint power(modint a, ll n) {
		modint ans = 1;
		for (; n > 0; n >>= 1, a = a * a)
			if (n & 1) ans = ans * a;
		return ans;
	}
	modint operator / (modint a) const {return (power(a, MOD-2) * v);}
};

int n;
string num;

modint prefix[MAX];//, suffix[MAX];
void build() {
	modint W = 0;
	FOR(int, i, 1, n) {
		modint wAdd = prefix[i-1] + modint::power(3, max(0, i-2));
		prefix[i] = wAdd * num[i] 					// ...*d or ...+d
				  + prefix[i-1]*10 + W * num[i];		// ...*...d
		W = W + wAdd;
		// cerr << i << ' ' << prefix[i].v << ' ' << W.v << '\n';
	}
	// FOR(int, i, 1, n) cerr << prefix[i].v << " \n"[i == n];

	// W = 0;
	// REV(int, i, n, 1) {
	// 	modint wAdd = suffix[i+1] + 1;
	// 	suffix[i] = wAdd * num[i]
	// 			  + suffix[i+1]*10 + W * num[i];
	// 	W = W + wAdd;
	// }
	// FOR(int, i, 1, n) cerr << suffix[i].v << " \n"[i == n];
}

modint sumPref[MAX];
void calculate() {
	// FOR(int, i, 1, n) sumPref[i] = sumPref[i-1] + prefix[i];
	// FOR(int, i, 1, n) cerr << sumPref[i].v << " \n"[i == n];

	modint ans = 0;
	FOR(int, i, 1, n) {
		ans = ans + prefix[i] * modint::power(3, max(0, n-i-1));
	}

	cout << ans.v << '\n';
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	build();
	calculate();
}
void input() {
	cin >> n >> num; num = " " + num; 
	for (char &c: num) c -= '0';
}
void clear() {}