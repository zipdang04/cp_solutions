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

ll dist(int k, ll r1, ll c1, ll r2, ll c2) {
	// cerr << k << ' ' << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
	if (k == 1) return abs(r2 - r1) + abs(c2 - c1);
	const ll FULL = 1ll << k, HALF = FULL >> 1;

	const int bitR1 = r1 >= HALF, bitR2 = r2 >= HALF,
		 	  bitC1 = c1 >= HALF, bitC2 = c2 >= HALF;
	ll newR1 = r1 - bitR1 * HALF, newC1 = c1 - bitC1 * HALF,
	   newR2 = r2 - bitR2 * HALF, newC2 = c2 - bitC2 * HALF;
	if (bitR1 == bitR2 and bitC1 == bitC2) 
		return dist(k-1, newR1, newC1, newR2, newC2);

	if (
		(r1 == 0 or r1 == FULL - 1) and
		(r2 == 0 or r2 == FULL - 1) and
		(c1 == 0 or c1 == FULL - 1) and
		(c2 == 0 or c2 == FULL - 1)
	) {
		ll answer = (HALF - 1) << 2;
		answer += (bitR1 != bitR2) + (bitC1 != bitC2);
		return answer;
	}
	
	return 	dist(k-1, newR1, newC1, (HALF-1) * int(!bitR1), (HALF-1) * int(!bitC1))
		+	dist(k-1, newR2, newC2, (HALF-1) * int(!bitR2), (HALF-1) * int(!bitC2))
		+	(bitR1 != bitR2) + (bitC1 != bitC2);
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll r1 = 0, c1 = 0;
	int k, q; cin >> k >> q;
	FOR(int, _, 1, q) {
		ll r2, c2; cin >> r2 >> c2;
		cout << dist(k, r1, c1, r2, c2) << '\n';
		r1 = r2, c1 = c2;
		// cerr << '\n';
	}
}