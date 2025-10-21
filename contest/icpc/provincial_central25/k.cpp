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

#define MAX 10
#define MOD 1000000007

int ASK(int pos) {
	cout << "? " << pos << endl;
	int value; cin >> value; return value;
}

void ANSWER(vector<int> a) {
	cout << "!";
	for (int i: a) cout << " " << i;
	cout << endl;
}

vector<int> answer;
void process(int n) {
	answer.clear();
	bool used[MAX] = {};
	vector<int> remain(n); iota(remain.begin(), remain.end(), 1);
	FOR(int, pos, 1, 6) {
		vector<int> cnt[MAX] = {};
		for (int i: remain)
			cnt[ASK((i-1) * 6 + pos)].push_back(i);
		// FOR(int, val, 1, 6) cerr << (used[val] ? -1 : (int)cnt[val].size()) << " \n"[val == 6];
		
		int minVal = 0;
		FOR(int, val, 1, 6) if (not used[val]) {
			if (minVal == 0 or (int)cnt[val].size() < (int)cnt[minVal].size())
				minVal = val;
		}
		answer.push_back(minVal);
		used[minVal] = true;
		remain = cnt[minVal];
	}
	ANSWER(answer);
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		int n; cin >> n;
		process(n);
		
	}

}