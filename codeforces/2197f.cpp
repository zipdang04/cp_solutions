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

#define MAX 200'005
#define MOD 1000000007

int n;
string s;
vector<pair<char, int>> sq, cc;
void buildSet() {
	for (int i = 0; i < (int)s.size(); i++) {
		char c = s[i]; switch(c) {
		case '(':
			sq.push_back({c, i});
			break;
		case '[':
			cc.push_back({c, i});
			break;
		case ')':
			if (sq.empty() or sq.rbegin() -> fi != '(')
				sq.push_back({c, i});
			else
				sq.pop_back();
			break;
		case ']':
			if (cc.empty() or cc.rbegin() -> fi != '[')
				cc.push_back({c, i});
			else
				cc.pop_back();
			break;
		}
	}
}
void buildString() {
	s = "";
	int iSq = 0, iCC = 0;
	while (iSq < (int) sq.size() and iCC < (int) cc.size())
		if (sq[iSq].se < cc[iCC].se)
			s += sq[iSq++].fi;
		else
			s += cc[iCC++].fi;
	while (iSq < (int) sq.size())
		s += sq[iSq++].fi;
	while (iCC < (int) cc.size())
		s += cc[iCC++].fi;
}

int clsCC, clsSQ, opSQ, opCC, cntO, cntC;
void buildCount() {
	clsCC = clsSQ = 0;
	opCC = opSQ = INT_MAX;
	cntO = cntC = 0;

	for (int i = 0; i < (int)s.length(); i++) {
		char c = s[i]; switch(c) {
			case '(':
				cntO++; minimize(opCC, i);
				break;
			case '[':
				cntO++; minimize(opSQ, i);
				break;
			case ')':
				cntC++; maximize(clsCC, i);
				break;
			case ']':
				cntC++; maximize(clsSQ, i);
				break;
		}
	}
}

void input(), clear();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		buildSet();
		buildString();
		buildCount();

		ll ans = (cntO + cntC) / 2 + !(
			cntO % 2 == 0
			or opSQ < clsCC
			or opCC < clsSQ
		);
		cout << ans << '\n';
		clear();
	}
}
void input() {
	cin >> n >> s; s = " " + s;
}
void clear() {
	sq.clear(), cc.clear();
}
