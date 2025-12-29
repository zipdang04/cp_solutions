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

int ASK(int i, int x) {
	cout << "? "  << i << ' ' << x << endl;
	int ans; cin >> ans; return ans;
}
void ANSWER(int num) {
	cout << "! " << num << endl;
}

vector<int> pool, all;

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t) {
		int n; cin >> n;
		pool.resize(n); iota(pool.begin(), pool.end(), 1);
		all = pool; pool.pop_back();

		// int answer = 0;
		for (int bit = 0, MASK = 1; (int)all.size() > 1; bit++, MASK <<= 1) {
			vector<int> expect[2], res[2];
			for (int i: all) expect[testBit(i, bit)].push_back(i);
			// cerr << bit << '|';
			// FOR(int, val, 0, 1) {for (int i: expect[val]) cerr << i << ' '; cerr << '|';} cerr << "===";
			// for (int i: pool) cerr << i << '\n';

			if (expect[0].empty() or expect[1].empty()) {
				// answer |= MASK * expect[0].empty();
				continue;
			}

			bool test = expect[1].size() < expect[0].size();
			auto it = pool.begin();
			for (it = pool.begin(); it < pool.end() and res[0].size() < expect[0].size() and res[1].size() < expect[1].size(); it++) {
				const int pos = *it;
				if (!!ASK(pos, MASK) == test)
					res[test].push_back(pos);
				else
					res[not test].push_back(pos);
			}
			// FOR(int, val, 0, 1) {for (int i: res[val]) cerr << i << ' '; cerr << '|';} cerr << '\n';

			vector<int> remain(it, pool.end());
			// cerr << test << ' ' << "remain: "; for (int i: remain) cerr << i << ' '; cerr << '\n';
			assert(res[0].size() == expect[0].size() or res[1].size() == expect[1].size());

			if (res[0].size() < expect[0].size())
				pool = res[0], all = expect[0];
			else
				// answer |= MASK,
				pool = res[1], all = expect[1];
			pool.insert(pool.end(), remain.begin(), remain.end());
		}

		ANSWER(all[0]);
	}
}
