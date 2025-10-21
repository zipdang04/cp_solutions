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

#define MAX_N 200005
#define MAX_K 2000
#define MOD 1000000007

struct Tree{int x, w;};
inline bool operator < (Tree a, Tree b) {
	return a.x < b.x;
}

int n, K, P;
Tree trees[MAX_N];
ll sumW[MAX_N];

ll jmp[MAX_N];
ll f[MAX_N];
inline bool check(int L) {
	memset(f, false, sizeof(f));
	int ptr = 1;
	FOR(int, i, 1, n) {
		while (trees[i].x - trees[ptr].x > L) ptr++;
		jmp[i] = ptr-1;
	}
	// cerr << L << '|'; FOR(int, i, 1, n) cerr << jmp[i] << " \n"[i == n];

	FOR(int, k, 1, K) {
		REV(int, i, n, 1)
			maximize(f[i], f[jmp[i]] + (sumW[i] - sumW[jmp[i]]));
		FOR(int, i, 1, n)
			maximize(f[i], f[i-1]);
		if (f[n] >= P) return true;
	}
	return false;
}


main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	read(n, K, P);
	FOR(int, i, 1, n) {
		int x, w; read(x, w);
		trees[i] = {x, w};
	}
	FOR(int, i, 1, n) sumW[i] = sumW[i-1] + trees[i].w;

	int lo = 0, hi = 1e9, ans = -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (check(mid))
			ans = mid, hi = mid-1;
		else
			lo = mid + 1;
	}
	cout << ans << '\n';
}