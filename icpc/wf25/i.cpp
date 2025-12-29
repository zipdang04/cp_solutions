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

namespace RNG{
	randomize;
	int rnd(int n) {return mt() % n;}
	int rnd(int l, int r) {return l + mt() % (r-l+1);}
}

int n, k;
void move(int i, int j) {
	cout << i << ' ' << j << endl;
	cin >> k; if (k == 1) exit(0);
}

void stageOne() {
	FOR(int, i, 1, n)
		while (true) {
			int oldK = k;
			move(i, 1);
			if (k > oldK) {
				move(i, -1);
				break;
			}
		}
}
// TODO: xử lý trường hợp các nhóm CÁCH ĐỀU
int lastStep = -1;
bool stageTwo(int root = 0) {
	// cerr << "stageTwo\n";
	if (root == 0) root = RNG::rnd(1, n);

	int oldK = k;
	int step = 0;
	do { move(root, 1); step++;} while (oldK < k);
	if (step == 1) {	// nhóm đơn lẻ
		while (oldK == k) move(root, 1);
		// cerr << root << ' ' << oldK << ' ' << k << '\n';
		assert(oldK > k);
		return true;
	}
	lastStep = step;
	
	bool allJumped = true;
	FOR(int, i, 1, n) if (i != root) {
		move(i, step);
		if (k > oldK) move(i, -step), allJumped = false;
		if (k < oldK) {allJumped = false; break;}
	}
	return not allJumped;
}

void removeCycle() {
	// cerr << "removeCycle\n";
	int root = 1;
	vector<int> all = {1};
	move(root, 1);
	FOR(int, i, 2, n) {
		int oldK = k;
		move(i, 1);
		if (k > oldK) move(i, -1);
		else all.push_back(i);
	}
	// // // cerr << "get group: "; for (int i: all) cerr << i << ' '; cerr << '\n';
	for (int i: all) move(i, lastStep - 1);
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	
	stageOne();
	// cerr << "end stage 1\n";
	while (true) {
		// cerr << "startTURN\n";
		if (stageTwo() == false) removeCycle();
		// cerr << "endTURN\n";
	}
}