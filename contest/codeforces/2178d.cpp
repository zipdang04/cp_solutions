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

struct Elf{ int h, a, i; };

int n, m;
Elf elves[MAX];
vector<pii> actions;
void buildM(int m) {
	int r = n;
	FOR(int, i, 1, m-1)
		actions.push_back({elves[r].i, elves[r-1].i}),
		r -= 2;
	FOR(int, i, 1, r-2)
		actions.push_back({elves[i].i, elves[i+1].i});
	actions.push_back({elves[r].i, elves[r-1].i});
}
bool build0() {
	int pos = n-1;
	while (pos >= 1) {
		if (elves[pos].a < elves[n].h) {
			actions.push_back({elves[pos].i, elves[n].i});
			elves[n].h -= elves[pos--].a;
		}
		else break;
	}
	if (pos == 0) return false;
	FOR(int, i, 1, pos-1)
		actions.push_back({elves[i].i, elves[i+1].i});
	actions.push_back({elves[pos].i, elves[n].i});
	return true;
}

void input();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input(); actions.clear();
		if (m * 2 > n) {cout << "-1\n"; continue;}
		bool oke = true;
		if (m >= 1) buildM(m); else oke = build0();
		if (not oke) { cout << "-1\n"; continue; }
		cout << actions.size() << '\n';
		for (auto [i1, i2]: actions) cout << i1 << ' ' << i2 << '\n';
	}
}
void input() {
	int _x; cin >> n >> m;
	FOR(int, i, 1, n) {cin >> _x; elves[i] = {_x, _x, i};}
	sort(elves+1, elves+1+n, [](Elf a, Elf b) -> bool {return a.a < b.a;});
}
