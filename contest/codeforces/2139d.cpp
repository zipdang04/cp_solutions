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

#define MAX 500005
#define MOD 1000000007

struct Node {
	int mini, maxi;
	Node() {mini = INT_MAX, maxi = INT_MIN;}
	Node(int value) {mini = maxi = value;}
	void update(Node left, Node right) {
		maximize(maxi, left.maxi);
		maximize(maxi, right.maxi);
		minimize(mini, left.mini);
		minimize(mini, right.mini);
	}
};

class SegTree {
	private:
		int sz;
		vector<Node> tree;
		void update(int idx, int lo, int hi, int pos, int value) {
			if (lo == hi) {
				tree[idx] = Node(value);
				return;
			}
			int y = idx << 1, mid = (lo + hi) >> 1;
			if (pos <= mid)
				update(y, lo, mid, pos, value);
			else
				update(y + 1, mid + 1, hi, pos, value);
			tree[idx].update(tree[y], tree[y + 1]);
		}
		Node get(int idx, int lo, int hi, int posL, int posR) {
			if (hi < posL or posR < lo) return Node();
			if (posL <= lo and hi <= posR) return tree[idx];
			
			int y = idx << 1, mid = (lo + hi) >> 1;
			Node ans; ans.update(
				get(y, lo, mid, posL, posR),
				get(y + 1, mid + 1, hi, posL, posR)
			);
			return ans;
		}
	public:
		void init(int sz) {
			this -> sz = sz;
			tree = vector<Node>((sz+1) * 4);
		}
		void update(int pos, int value) {
			update(1, 1, sz, pos, value);
		}
		Node get(int posL, int posR) {
			return get(1, 1, sz, posL, posR);
		}
		void print() {
			for (Node node: tree) cerr << node.mini << '.' << node.maxi << ' '; cerr << '\n';
		}
} seg;

int n, q;
int a[MAX];
pii queries[MAX];

int firstG[MAX], firstL[MAX];
vector<pii> updA[MAX], qTurn[MAX];
bool answer[MAX];

void buildFirst() {
	stack<int> st;
	FOR(int, i, 1, n) firstG[i] = INT_MIN;
	FOR(int, i, 1, n) {
		while (not st.empty() and a[st.top()] < a[i]) st.pop();
		if (not st.empty()) firstG[i] = st.top();
		st.push(i);
	}
	
	st = stack<int>();
	FOR(int, i, 1, n) firstL[i] = INT_MAX;
	REV(int, i, n, 1) {
		while (not st.empty() and a[st.top()] > a[i]) st.pop();
		if (not st.empty()) firstL[i] = st.top();
		st.push(i);
	}

	FOR(int, i, 1, n) if (firstG[i] > 0 and firstL[i] <= n)
		updA[firstG[i]].push_back({i, firstL[i]});

	// FOR(int, i, 1, n) cerr << firstG[i] << " \n"[i == n];
	// FOR(int, i, 1, n) cerr << firstL[i] << " \n"[i == n];
}

void input();
void clear();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		buildFirst();
		seg.init(n);
		REV(int, l, n, 1) {
			for (auto [i, r]: updA[l]) 
				seg.update(i, r);
			for (auto [i, r]: qTurn[l])
				answer[i] = seg.get(l, r).mini > r;
		}
		FOR(int, i, 1, q) cout << (answer[i] ? "YES\n" : "NO\n");// << " \n"[i == n];
		
		clear();
	}
}
void input() {
	cin >> n >> q;
	FOR(int, i, 1, n) cin >> a[i];
	FOR(int, i, 1, q) {
		int l, r; cin >> l >> r;
		queries[i] = {l, r};
		qTurn[l].push_back({i, r});
	}
}
void clear() {
	FOR(int, i, 1, n) firstG[i] = 0;
	FOR(int, i, 1, n) firstL[i] = 0;
	FOR(int, i, 1, n) updA[i].clear();
	FOR(int, i, 1, n) qTurn[i].clear();
}