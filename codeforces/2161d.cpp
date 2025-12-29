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

int n, a[MAX];
vector<int> pos[MAX], f[MAX];

void input();
void clear();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		for (int i = 0, j = pos[1].size(); j >= 0; i++, j--)
			f[1][i] = j;
		FOR(int, val, 2, n) {
			int cnt = pos[val].size(), prvCnt = pos[val-1].size();
			// no val => all val-1
			f[val][cnt] = f[val-1][0];
			int ptr = prvCnt;
			REV(int, i, cnt-1, 0) {
				// auto 1
				f[val][i] = 1;
				// not cut here
				if (i < cnt-1)
					maximize(f[val][i], f[val][i+1] + 1);
				// cut here
				while (ptr > 0 and pos[val][i] < pos[val-1][ptr-1]) ptr--;
				if (ptr == prvCnt or pos[val][i] < pos[val-1][ptr])
					maximize(f[val][i], f[val-1][ptr] + 1);
			}
			REV(int, i, cnt-1, 0)
				maximize(f[val][i], f[val][i + 1]);
		}
		int ans = 0;
		for (int res: f[n]) maximize(ans, res);
		cout << n - ans << '\n';
		clear();
	}
}
void input() {
	cin >> n; FOR(int, i, 1, n) cin >> a[i];
	FOR(int, i, 1, n)
		pos[a[i]].push_back(i);
	FOR(int, val, 1, n)
		f[val].resize((int)pos[val].size() + 1, 0);
}
void clear() {
	FOR(int, i, 1, n) pos[i].clear();
	FOR(int, i, 1, n) f[i].clear();
}
