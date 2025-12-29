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

set<string> dict;

int n;
string s;
bool f[MAX]; int trace[MAX];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; FOR(int, _, 1, n) {
		string word; cin >> word;
		dict.insert(word);
	}

	int q; cin >> q; 
	FOR(int, _, 1, q) {
		cin >> s; n = s.length(); s = " " + s;
		FOR(int, i, 0, n) f[i] = false; f[0] = true;

		FOR(int, pos, 1, n) {
			FOR(int, prv, max(0, pos-20), pos-1) 
			if (f[prv] and dict.find(s.substr(prv+1, pos-prv)) != dict.end()) {
				f[pos] = true, trace[pos] = prv;
			}
		}

		if (not f[n]) {cout << "-1\n"; continue;}
		vector<string> result;
		while (n > 0) {
			int nxt = trace[n];
			result.push_back(s.substr(nxt + 1, n-nxt));
			n = nxt;
		}
		reverse(result.begin(), result.end());
		for (string word: result) cout << word << ' '; cout << '\n';
	}
}