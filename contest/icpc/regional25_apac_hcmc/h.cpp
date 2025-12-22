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

#define MAX 6005
#define MOD 1000000007
constexpr ll oo = 1e18;

struct Point{
	ll x, y;
	Point() {x = y = 0;}
	Point(ll x, ll y): x(x), y(y) {}

	Point operator - (Point oth) const { return {x - oth.x, y - oth.y}; }
	ll dist2() const {return x*x + y*y;}
	ld dist() const { return sqrt(dist2()); }
} pts[MAX];

int n;
ld f[MAX][3005][2];

#define HEAD_L 0
#define HEAD_R 1

void dp() {
	// f[head][tail]
	FOR(int, i, 1, 2*n) f[i][1][0] = f[i][1][1] = 0;
	for (int prvLen = 1, len = 2; len <= n; prvLen++, len++){
		for (int l = 1, r = prvLen; r <= 2*n; l++, r++) {
			const ld costLL = l == 1 ? oo : (pts[l] - pts[l-1]).dist(); // l -> l-1
			const ld costLR = r == 2*n ? oo : (pts[l] - pts[r+1]).dist(); // l -> r+1
			const ld costRL = l == 1 ? oo : (pts[r] - pts[l-1]).dist(); // r -> l-1
			const ld costRR = r == 2*n ? oo : (pts[r] - pts[r+1]).dist(); // r -> r+1

			if (l > 1)
				minimize(f[l-1][len][HEAD_L], min(
					f[l][prvLen][HEAD_L] + costLL,
					f[l][prvLen][HEAD_R] + costRL
				));
			minimize(f[l][len][HEAD_R], min(
				f[l][prvLen][HEAD_L] + costLR,
				f[l][prvLen][HEAD_R] + costRR
			));
		}
	}
}

void trace(int l, int r, bool head, ld best) {
	vector<int> path;
	REV(int, remain, n-1, 1) {
		// cerr << l << ' ' << r << '\n';
		int whereHead = (head == HEAD_L) ? l++ : r--;
		Point pHead = pts[whereHead];
		path.push_back(whereHead);

		const ld costL = (pHead - pts[l]).dist();//, costR = (pHead - pts[r-1]).dist();

		if (abs(best - (f[l][remain][HEAD_L] + costL)) <= 1e-9)
			head = HEAD_L;
		else
			head = HEAD_R;
		best = f[l][remain][head];
	}
	assert(l == r); path.push_back(l);
	// cerr << l << ' ' << r << '\n';

	for (int i: path) cout << (i-1)%n+1 << ' '; cout << '\n';
}

void input();
void clear();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	cout << fixed << setprecision(7);
	// cerr << fixed << setprecision(7);
	FOR(int, ____, 1, tests) {
		input();
		clear();

		dp();
		int bestL = 1, bestR = n, bestHead = HEAD_L; ld best = f[bestL][bestR][bestHead];
		FOR(int, l, 1, n) FOR(int, head, HEAD_L, HEAD_R) {
			if (best > f[l][n][head])
				best = f[l][n][head],
				tie(bestL, bestR, bestHead) = tuple<int, int, int>(l, l+n-1, head);
		}
		// cerr << best << '\n';
		// trace(bestL, bestR, bestHead, best);
	}
}
void input() {
	cin >> n; FOR(int, i, 1, n) cin >> pts[i].x >> pts[i].y;
	FOR(int, i, 1, n) pts[i+n] = pts[i];
}
void clear() {
	FOR(int, i, 0, n*2) FOR(int, j, 0, n) f[i][j][0] = f[i][j][1] = oo;
}
