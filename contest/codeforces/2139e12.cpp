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

#define MAX 200005
#define MOD 1000000007

int n, k;
int p[MAX], lvl[MAX];
bool isLeaf[MAX];
int cnt[MAX];

bitset<MAX> possibility;

void input();
void clear();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();

		int lastLevel = INT_MAX;
		FOR(int, i, 1, n) if (isLeaf[i]) minimize(lastLevel, lvl[i]);

		int total = 0;
		FOR(int, i, 0, lastLevel) total += cnt[i];

		FOR(int, i, 0, lastLevel) {
			possibility |= possibility << cnt[i];
			possibility[cnt[i]] = true;
		}

		int answer = lastLevel;
		FOR(int, value, 0, total) if (possibility[value]) {
			int remain = total - value;
			if (value <= k and remain <= n - k) {answer++; break;}
			if (remain <= k and value <= n - k) {answer++; break;}
		}

		cout << answer << '\n';
		clear();
	}

}
void input() {
	cin >> n >> k;
	cnt[0] = 1;
	FOR(int, i, 2, n) {
		cin >> p[i];
		lvl[i] = lvl[p[i]] + 1;
		cnt[lvl[i]]++;
		isLeaf[i] = true;
		isLeaf[p[i]] = false;
	}
}
void clear() {
	FOR(int, i, 1, n) cnt[i] = 0;
	FOR(int, i, 1, n) p[i] = 0;
	FOR(int, i, 1, n) lvl[i] = 0;
	FOR(int, i, 1, n) isLeaf[i] = 0;
	possibility = 0;
}