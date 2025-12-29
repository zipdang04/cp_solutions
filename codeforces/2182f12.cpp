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

#define BIT 60
#define MAX 1000001
#define MOD 998244353

class Math{
	private:
		inline static ll fact[MAX + 1] = {};
		inline static ll ifac[MAX + 1] = {};
	public:
		inline static ll p2[MAX + 1] = {};
		Math(){
			fact[0] = 1;
			FOR(ll, i, 1, MAX)
				fact[i] = (fact[i - 1] * i) % MOD;
			ifac[MAX] = power(fact[MAX], MOD - 2);
			REV(ll, i, MAX - 1, 0)
				ifac[i] = (ifac[i + 1] * (i + 1)) % MOD;
			p2[0] = 1; FOR(int, i, 1, MAX) p2[i] = p2[i-1] * 2 % MOD;
		}

		ll power(ll a, ll n){
			assert(n >= 0);
			if (n == 0) return 1;
			ll ans = power(a, n >> 1);
			ans *= ans, ans %= MOD;
			if (n & 1) return (ans * a) % MOD;
			return ans;
		}

		ll C(ll n, ll k){
			assert(n <= MAX and n >= k and k >= 0);
			return (((fact[n] * ifac[k]) % MOD) * ifac[n - k]) % MOD;
		}

		ll P(ll n, ll k){
			assert(n <= MAX and n >= k and k >= 0);
			return (fact[n] * ifac[n - k]) % MOD;
		}

		ll FACT(ll n){
			assert(n <= MAX and n >= 0);
			return fact[n];
		}
		ll IFAC(ll n){
			assert(n <= MAX and n >= 0);
			return ifac[n];
		}
		ll INV(ll n) {
			assert(n > 0);
			return (ifac[n] * fact[n-1] % MOD);
		}
} math;

int n, m;
int cntAll[BIT+5];
ll calTotal() {
	ll total = 0; FOR(int, i, 0, BIT) total += cntAll[i];
	return Math::p2[total];
}

int pos[BIT + 5], cntPos = 0;
ll cal(ll NUM) {
	cntPos = 0; REV(int, i, BIT, 0) if (testBit(NUM, i)) pos[cntPos++] = i;
	FOR(int, i, 0, cntPos-1) pos[i] += i;

	int curCnt[BIT+5] = {}; FOR(int, i, 0, BIT) curCnt[i] = cntAll[i];

	ll answer = 0, prefix = 1;
	int last = MAX, cnt = 0, pool = 0;
	FOR(int, i, 0, cntPos-1) {
		int need = pos[i];

		ll cur = 1;
		FOR(int, bit, 0, need-1) (cur *= Math::p2[cntAll[bit]]) %= MOD;
		(cur *= prefix) %= MOD;
		(answer += cur) %= MOD;

		if (curCnt[need] == 0) break;
		if (need == last) {
			(prefix *= math.FACT(cnt) * math.FACT(pool - cnt) % MOD) %= MOD;
			cnt++; if (cnt > pool) break;
			(prefix *= math.IFAC(cnt) * math.IFAC(pool - cnt) % MOD) %= MOD;
		} else {
			last = need; cnt = 1, pool = curCnt[need];
			(prefix *= pool) %= MOD;
		}
		curCnt[need]--;
	}


	return (calTotal() + MOD - answer) % MOD;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	FOR(int, i, 1, n) {
		int c; cin >> c; cntAll[c]++;
	}

	FOR(int, _, 1, m) {
		int type; ll x; cin >> type >> x;
		if (type == 1) cntAll[x]++;
		else if (type == 2) cntAll[x]--;
		else {
			ll ans = cal(x);
			cout << ans << '\n';
		}
	}
}
