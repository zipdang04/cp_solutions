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
bool maximize(T1 &a, T2 b){
	return (b > a) ? (a = b, true) : false;
}
template <class T1, class T2>
bool minimize(T1 &a, T2 b){
	return (b < a) ? (a = b, true) : false;
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

pair<ll, ll> cal(ll x, ll y) {
	FOR(int, i, 0, 29)
		if (testBit(x, i) and testBit(y, i))
			x -= 1 << i;
	return {x, y};
}

ll x, y;
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> x >> y;
		if ((x & y) == 0) {
			cout << x << ' ' << y << '\n';
			continue;
		}

		ll ansX = -1, ansY = -1, best = LLONG_MAX;
		REV(int, bit, 29, 0) {
			int ALL = (1 << bit) - 1;
			int needX = ALL+1 - (x & ALL);
			int needY = ALL+1 - (y & ALL);

			for (auto [newX, newY]: {cal(x + needX, y), cal(x, y + needY)}) {
				if (minimize(best, abs(x-newX) + abs(y-newY)))
					ansX = newX, ansY = newY;
			}

			needX = x & ALL, needY = y & ALL;
			for (auto [newX, newY]: {cal(x - needX-1, y), cal(x, y - needY-1)}) {
				if (newX < 0 or newY < 0) continue;
				if (minimize(best, abs(x-newX) + abs(y-newY)))
					ansX = newX, ansY = newY;
			}
		}
		cout << ansX << ' ' << ansY << '\n';
		// cerr << _ << '|' << ansX << ' ' << ansY << '|' << abs(x-ansX) + abs(y-ansY) << '\n';
		cout.flush();
		assert(((ansX & ansY) == 0));
	}
}
