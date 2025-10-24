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

#define MAX 100
#define MOD 1000000007

class Math{
	private:
		inline static ll _fact[MAX + 1] = {};
		inline static ll _ifac[MAX + 1] = {};
	public:
		Math(){
			_fact[0] = 1;
			FOR(ll, i, 1, MAX)
				_fact[i] = (_fact[i - 1] * i) % MOD;
			_ifac[MAX] = power(_fact[MAX], MOD - 2);
			REV(ll, i, MAX - 1, 0)
				_ifac[i] = (_ifac[i + 1] * (i + 1)) % MOD;
		}

		inline static ll power(ll a, ll n){
			if (n == 0) return 1;
			ll ans = power(a, n >> 1);
			ans *= ans, ans %= MOD;
			if (n & 1) return (ans * a) % MOD;
			return ans;
		}

		inline static ll C(ll n, ll k){
			return (((_fact[n] * _ifac[k]) % MOD) * _ifac[n - k]) % MOD;
		}
		
		inline static ll P(ll n, ll k){
			return (_fact[n] * _ifac[n - k]) % MOD;
		}

		inline static ll euler(ll n, ll k){ // k cho n nguoiwf
			return C(k+n-1, k);
		}
		
		inline static ll factorial(ll n){
			return _fact[n];
		}
} math;

int n, k;
int a[MAX];
int d[MAX];

int f[MAX][MAX][MAX];
ll oldF[MAX], newF[MAX];
main()
{

	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	FOR(int, i, 1, n) cin >> a[i];
	FOR(int, i, 1, n) d[i] = a[i] - a[i-1];
	d[n+1] = 1e9;
	f[0][k][k] = 1;
	FOR(int, i, 1, n+1) cerr << d[i] << " \n"[i == n+1];
	for (int i = 0, nxt = 1; i <= n; i++, nxt++)
	REV(int, remainP, k, 0) REV(int, remainM, k, 0) {
		const int fValue = f[i][remainP][remainM];
		if (fValue == 0) continue;
		cerr << i << ' ' << remainP << ' ' << remainM << ' ' << fValue << '\n';
		assert(remainP <= remainM);

		FOR(int, useP, 0, remainP) FOR(int, useM, 0, remainM){
			if (d[nxt] + useP - useM <= 0) continue;
			if (useM > )
			if (remainP - useP > remainM - useM) break;
			f[nxt][remainP - useP][remainM - useM] += fValue * Math::C(useP + useM, useP);
			f[nxt][remainP - useP][remainM - useM] %= MOD;
		}
	}
	REV(int, remainP, k, 0) REV(int, remainM, k, 0)
		if (f[n+1][remainP][remainM])
		cerr << n+1 << ' ' << remainP << ' ' << remainM << ' ' << f[n+1][remainP][remainM] << '\n';
	
	FOR(int, i, 0, k)
		oldF[i] = f[n+1][k-i][k-i];
	newF[0] = oldF[0];
	newF[1] = oldF[1];
	FOR(int, i, 2, k) {
		newF[2] = oldF[2];
		FOR(int, j, 0, i-1) {
			// 
		}
	}

	
	cout << f[n+1][0][0] << '\n';
}