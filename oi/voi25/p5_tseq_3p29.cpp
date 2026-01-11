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

#define oo 1'000'000'000
#define MAX_Q 500005
#define MOD 1000000007

struct Query{int type, n1, n2;};
int q; Query queries[MAX_Q];
int checkSubtask() {
	bool k500 = true, no2 = true;
	FOR(int, i, 1, q) 
		k500 &= queries[i].type != 1 || queries[i].n2 <= 500,
		no2 &= queries[i].type != 2;

	if (q <= 500 and k500) return 1;
	if (q <= 5000) return 2;
	if (no2) return 4;
	return 5;
}
/***************************************************/
class Base{ public:
	int l, r;
	Base *prv, *nxt;
	vector<Base*> branches; // connected to r
	Base(int l, int r);
	
	bool split(int cnt);
	// void addBranch(Base *node) {
	// 	Base *oldNxt = this -> nxt;
	// 	node -> prv = this; oldNxt -> prv = node;
	// 	this -> nxt = node; node -> nxt = oldNxt;
	// 	node -> prv = this; this -> nxt = node;
	// 	this -> branches.push_back(node);
	// }
	// void addParent(Base *par) {
	// 	// TODO

	// }
	void cut() {
		assert(this -> nxt != nullptr);
		(this -> nxt) -> prv = nullptr;
		this -> branches.pop_back();
		this -> nxt = branches.empty() ? nullptr : branches.back();
	}
};
map<int, Base*> allL;
Base* findNode(int num) {return (--allL.upper_bound(num)) -> second;}
Base::Base(int l, int r): l(l), r(r) {
	// cerr << "add: " << l << ' ' << r  << '\n';
	assert(allL.find(l) == allL.end());
	allL[l] = this;
	prv = nxt = nullptr;
}
bool Base::split(int cnt) { // [l, num] &  [num + 1, r]
	// cerr << this -> l << '-' << this -> r << ' ' << cnt << '\n';
	if (cnt == r - l + 1) return false;
	assert((cnt > 0 and cnt < r - l + 1));
	
	allL.erase(this -> l);
	// // for (auto i: allL) cerr << i.fi << ' '  ; cerr << '\n';
	Base *newNode = new Base(l, l + cnt - 1);
	this -> l += cnt; allL[l] = this;

	Base *oldPrv = prv;
	if (oldPrv != nullptr) oldPrv -> nxt = newNode;
	newNode -> prv = oldPrv; newNode -> nxt = this;
	this -> prv = newNode; 
	newNode -> branches.push_back(this);
	return true;
}


Base *root = new Base(1, oo);
/***************************************************/
namespace Sub2{
	class Node: public Base{ public:
		Node(int l, int r): Base(l, r) {}
		void changeNext(Node *node) {
			Node* oldNxt = (Node*) this -> nxt;
			node -> prv = this; node -> nxt = oldNxt;
			this -> nxt = node; if (oldNxt != nullptr) oldNxt -> prv = node;
		}
	};
	Node *current = new Node(0, 0);
	void addK(int x, int k) {
		if (root->split(k)) root = root -> prv;
		Node *node = (Node*)root; root = root -> nxt; 
		if (node -> nxt != nullptr) node->cut();

		Node *parent = (Node*) findNode(x);
		if (parent -> split(x - parent -> l + 1)) parent = (Node*) parent -> prv;
		// if (parent -> nxt != nullptr) cerr << parent -> l << ' ' << parent -> r << ' ' << parent -> nxt -> l << ' ' << parent -> nxt -> r << ' ' << node -> l << ' ' << node -> r << '\n';
		parent->changeNext(node);
	}
	ll calLR(int l, int r) {
		int curCnt = 0;
		Base *node = current;
		ll answer = 0;
		while (node != nullptr) {
			int nodeL = node -> l, nodeR = node -> r;
			// cerr << nodeL << ' ' << nodeR << '\n';
			int nodeCnt = nodeR - nodeL + 1;
			int posL = curCnt + 1, posR = curCnt + nodeCnt;
			if (r < posL) break;
			if (posR >= l) {
				maximize(posL, l), minimize(posR, r);
				posL -= curCnt, posR -= curCnt;
				if (posL <= posR) {
					int begNum = nodeL + posL - 1, endNum = nodeL + posR - 1;
					// cerr << begNum << "->" << endNum << '\n';
					answer += ll(begNum + endNum) * (posR - posL + 1) / 2;
				}
			}
			curCnt += nodeCnt; node = node -> nxt;
		}
		return answer;
	}
	void delH(int y, int h) {
		Node* node = (Node*) findNode(y);
		if (node->split(y - (node -> l) + 1)) node = (Node*) node -> prv;
		Node* nxt = (Node*) node -> nxt;
		while (h > 0) {
			int len = min(h, (nxt -> r) - (nxt -> l) + 1);
			if (nxt -> split(len)) nxt = (Node*) nxt -> prv;
			h -= len; nxt = (Node*) nxt -> nxt;
		}
		node -> nxt = nxt; 
		if (nxt != nullptr) nxt -> prv = node;
	}

	void solve() {
		FOR(int, i, 1, q) {
			// cerr << "state:\n";
			// // // cerr << "one:"; Base *node = root; while (node != nullptr) {cerr << node -> l << '-' << node -> r << ' '; node = node -> nxt;} cerr << '\n';
			// // // cerr << "two:";node = current; while (node != nullptr) {cerr << node -> l << '-' << node -> r << ' '; node = node -> nxt;} cerr << '\n';
			// cerr << "query: " << i << '\n';
			Query query = queries[i];
			switch (query.type)  {
				case 1:{
					int x = query.n1, k = query.n2;
					addK(x, k);
					break;
				}
				case 2:{
					int y = query.n1, h = query.n2;
					delH(y, h);
					break;
				}
				case 3:{
					int l = query.n1, r = query.n2;
					ll answer = calLR(l, r);
					cout << answer << '\n';
					break;
				}
				
				default:
					assert(false);
			}
			// cerr << '\n';
		}
	}
};
/***************************************************/
/***************************************************/

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef HIEU
	freopen("tseq.inp", "r", stdin);
	freopen("tseq.out", "w", stdout);
	#endif
	input();
	int subtask = checkSubtask();

	Sub2::solve();
}
void input(){
	cin >> q;
	FOR(int, _, 1, q) {
		int type, n1, n2; cin >> type >> n1 >> n2;
		queries[_] = {type, n1, n2};
	}
}