#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
template <class T> using PQMax = priority_queue<T>;
template <class T> using PQMin = priority_queue<T, vector<T>, greater<T>>;
template <class T1, class T2>
void maximize(T1 &a, T2 b){
	if (b > a) a = b;
}
template <class T1, class T2>
void minimize(T1 &a, T2 b){
	if (b < a) a = b;
}
template <class T>
void read(T &number)
{
	bool negative = false;
	register int c;
	number = 0;
	c = getchar();
	while (c != '-' && !isalnum(c)) c = getchar();
	if (c=='-'){
		negative = true;
		c = getchar();
	}
	for (; (c>47 && c<58); c=getchar())
		number = number *10 + c - 48;
	if (negative)
		number *= -1;
}
template <class T, class ...Ts>
void read(T &a, Ts& ... args){
	read(a);
	read(args...);
}

/*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define REV(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define log2(n) (31 - __builtin_clz(n))
#define log2ll(n) (63 - __builtin_clzll(n))
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

#define MAX 1000000
#define MOD 1000000007

ll power(ll a, ll n) {
	a %= MOD;
	ll ans = 1;
	for (; n; a = a * a % MOD, n >>= 1)
		if (n & 1) ans = ans * a % MOD;
	return ans;
}
ll inv[MAX + 1];
void build() {
	FOR(int, i, 1, MAX)
		inv[i] = power(i, MOD - 2);
}
ll C(ll n, ll k) {
	if (k < 0 or k > n) return 0;
	ll ans = 1;
	for (ll i1 = 1, i2 = n; i1 <= k; i1++, i2--) {
		ans *= i2 % MOD; ans %= MOD;
		ans *= inv[i1] % MOD; ans %= MOD;
	}
	return ans;
}
ll euler(ll n, ll k) {
	if (k == 0) return 1;
	return C(k+n-1, k);
}

bitset<10'000'001> notP;
ll primes[MAX+1], cntP = 0;
void sieve() {
	for (ll i = 2; i < 10'000'000; i++) {
		if (notP[i]) continue;
		primes[++cntP] = i;
		for (ll j = i * i; j < 10'000'000; j += i)
			notP[j] = true;
	}
	// FOR(int, i, 1, cntP) cerr << primes[i] << " \n"[i == cntP];
}

vector<pll> factorize(ll number) {
	vector<pll> ans;
	// cerr << number << " => ";
	for (int i = 1; i <= cntP and primes[i] * 1ll * primes[i] <= number; i++) {
		int prime = primes[i], cnt = 0;
		while (number % prime == 0)
			number /= prime, cnt++;
		if (cnt)
			ans.push_back({prime, cnt});
	}
	// cerr << number << '\n';
	if (number > 1) ans.push_back({number, 1});
	return ans;
}

ll n, a, b;
vector<pll> total;
vector<pair<ll, vector<pll>>> divisors;

vector<pll> _current;
void build(const int pos, ll prod) {
	if (pos == (int) total.size()) {
		divisors.push_back({prod, _current});
		return;
	}
	const auto [p, maxCnt] = total[pos];
	FOR(int, i, 0, maxCnt) {
		_current.push_back({p, i});
		build(pos + 1, prod);
		_current.pop_back(); prod *= p;
	}
}

ll cal(vector<pll> divisor) {
	ll ans = 1; ll length = n;
	for (auto [_, cnt]: divisor) {
		if (cnt > length) return 0;
		ans *= euler(length, cnt); ans %= MOD;
		// length -= cnt;
	}
	return ans;
}
ll cal(pair<ll, vector<pll>> divisor) {
	auto [num, factors] = divisor;
	// cerr << num << '|'; for (auto [p, cnt]: factors) cerr << p << '^' << cnt << ' '; cerr << '\n';
	if (num > a) return 0;
	ll ans = cal(factors);
	for (int i = 0; i < total.size(); i++)
		factors[i].second = total[i].second - factors[i].second;
	num = b / num;
	// // // cerr << num << '|'; for (auto [p, cnt]: factors) cerr << p << '^' << cnt << ' '; cerr << '\n';
	ans = ans * cal(factors) % MOD;
	// cerr << b / num << ' ' << n << '=' << ans << '\n';
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	build(); sieve();

	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		total.clear(), divisors.clear();
		cin >> n >> a >> b;
		total = factorize(b);
		// cerr << b << '|'; for (auto [p, cnt]: total) cerr << p << '^' << cnt << ' '; cerr << '\n';
		build(0, 1);

		ll ans = 0;
		for (auto &it: divisors)
			ans += cal(it);
		ans %= MOD;

		cout << "Case #" << _ << ": " << ans << '\n';
		// cerr << '\n';
	}
}