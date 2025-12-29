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

struct Point{
	int x, y;
	Point(int x, int y): x(x), y(y) {}
	Point() {x=y=0;}
};
istream& operator >> (istream& ist, Point &p) {
	ist >> p.x >> p.y; return ist;
}

int n;
Point from, to;
Point dl[MAX], ur[MAX];

map<int, int> sum;

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	FOR(int, i, 1, n) {
		int yL = dl[i].y, yR = ur[i].y;
		sum[yL]++, sum[yR]--;
	}
	
	sum[-((int)1e6 + 1)] = 0;
	int prv = 0;
	for (auto [i, _]: sum) {
		prv += sum[i];
		sum[i] = prv;
	}
	sum[(int) 1e6+1] = prv;

	int yL = from.y, yR = to.y;
	if (yR > yL) {
		cout << 0; return 0; 
	}
	swap(yL, yR);
	// cerr << yL << ' ' << yR << '\n';

	int prvPos = yL, prvValue;
	int answer = 0;
	// for (const auto [y, _]: sum)  cerr << y << '|' << _ << '\n';
	for (const auto [y, _]: sum) {
		if (prvPos > yR) break;
		if (y >= prvPos) {
			int endPoint = min(y, yR);
			if (prvValue == 0) answer += endPoint - prvPos;
			// cerr << y << ' ' << prvPos << ' ' << answer << '\n';
			prvPos = y;
		}
		prvValue = _;
	}

	cout << answer << '\n';

}
void input() {
	cin >> n >> from >> to;
	FOR(int, i, 1, n) cin >> dl[i] >> ur[i];

}