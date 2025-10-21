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

#define MAX 1000001
#define MOD 1000000007

ll n, C, D;
ll a[MAX], b[MAX], curMaxA, curMaxB;

const ll NaN = -1;

ll checkC(const ll maxA) {
	// cerr << "check " << maxA << '\n'
	vector<int> curA(a, a + 1 + n);
	vector<int> curB(b, b + 1 + n);
	ll ops = 0;
	FOR(int, i, 1, n) {
		ll need = max(maxA - C - curA[i], 0ll);
		curA[i] += need, curB[i] += need, ops += need;
	}

	ll maxB = INT_MIN, minB = INT_MAX;
	FOR(int, i, 1, n)
		maximize(maxB, curB[i]),
		minimize(minB, curB[i]);
	
	if (maxB - minB <= D) return ops;
	FOR(int, i, 1, n) {
		ll need = max(maxB - D - curB[i], 0ll);
		if (curA[i] + need > maxA) return NaN;
		ops += need;
	}
	return ops;
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		ll ans = NaN, lo = curMaxA, hi = INT_MAX;
		while (lo <= hi) {
			ll mid = (lo + hi) / 2;
			ll cur = checkC(mid);
			if (cur == NaN)
				lo = mid + 1;
			else {
				// cerr << mid << "=>" << cur << '\n';
				ans = cur, hi = mid - 1;
			}
		}
		cout << ans << '\n';
	}
}
void input() {
	cin >> n >> C >> D;
	FOR(int, i, 1, n) cin >> a[i];
	FOR(int, i, 1, n) cin >> b[i];
	curMaxA = curMaxB = INT_MIN;
	FOR(int, i, 1, n) maximize(curMaxA, a[i]);
	FOR(int, i, 1, n) maximize(curMaxB, b[i]);
}