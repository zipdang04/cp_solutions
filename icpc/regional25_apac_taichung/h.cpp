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

#define MAX 600001

int k, t, len, MOD;
char s[MAX];
// int diff[MAX];

int d, blCnt, blLen;

int val[MAX], perm[MAX];
bool minu[MAX];

void reVal(function<bool(int, int)> cmp) {
	REV(int, i, len-1, 1) {
		if (i > 0) {
			int p1 = perm[i-1], p2 = perm[i];
			minu[i] = cmp(p1, p2);
		}
	}
	int ptr = len;
	REV(int, i, len-1, 0) {
		val[perm[i]] = ptr;
		ptr -= minu[i];
	}
	REV(int, i, len-1, 0) minu[i] = false;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> k >> t >> s;

	len = 1 << k; MOD = len-1;
	t %= k; d = 1 << ((k - t) % k);
	blLen = len / d, blCnt = d;

	FOR(int, i, 0, len-1) val[i] = s[i];
	iota(perm, perm+len, 0);

	for (int i = 0; (1<<i) < blLen; i++) {
		auto cmp = [&](int one, int two) -> bool {
			const int D = d << i;
			return (val[one] != val[two])
				? (val[one] < val[two])
				: (val[(one + D) & MOD] < val[(two + D) & MOD]);
		};
		sort(perm, perm+len, cmp);
		reVal(cmp);
	}
	for (int i = 0; (1<<i) < blCnt; i++) {
		auto cmp = [&](int one, int two) -> bool {
			const int D = 1 << i;
			return (val[one] != val[two])
				? (val[one] < val[two])
				: (val[(one + D) & MOD] < val[(two + D) & MOD]);
		};
		sort(perm, perm+len, cmp);
		reVal(cmp);
	}

	int start = perm[0];
	FOR(int, i, 0, blCnt-1)
		FOR(int, j, 0, blLen-1)
			cout << s[(start+i + j * d) & MOD];
}
