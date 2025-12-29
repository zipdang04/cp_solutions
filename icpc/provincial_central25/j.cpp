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

#define MAX 200
#define MOD 1000000007

class Point{
	private:
		inline static int M = 0, N = 0;
	public:
		int r, c;
		inline static void setLimit(int N, int M) {
			Point::N = N; Point::M = M;
		}
		Point(int r, int c): r(r), c(c) {}
		Point(): Point(0, 0) {}
		inline bool check() {
			return 0 <= r and r < N and 0 <= c and c < M;
		}
		inline Point operator + (Point oth) const {
			return {r + oth.r, c + oth.c};
		}
		inline bool operator == (Point oth) const {
			return r == oth.r and c == oth.c;
		}
		inline vector<Point> getAdjacent() const;
};
const Point DIREC[4] = {
	Point(0, -1),
	Point(0, +1),
	Point(-1, 0),
	Point(+1, 0),
};
inline vector<Point> Point::getAdjacent() const {
	vector<Point> res;
	for (Point add: DIREC) {
		Point newP = (*this) + add;
		// cerr << r << ' ' << c << ' ' << newP.r << ' ' << newP.c << '\n';
		if (not newP.check()) continue; 
		// cerr << "passed\n";
		res.push_back(newP);
	}
	return res;
}

int R, C;
char s[MAX][MAX];
Point start, dest;

#define S 'S'
#define D 'D'
#define BLOCK '+'

int cost[3][MAX][MAX];
queue<pair<int, Point>> q;
int bfs() {
	cost[2][start.r][start.c] = 1;
	q.push({2, start});
	while (not q.empty()) {
		const auto [curHP, curPoint] = q.front(); q.pop();
		const int nxtCost = cost[curHP][curPoint.r][curPoint.c] + 1;

		for (Point nxtPoint: curPoint.getAdjacent()) {
			const char ch = s[nxtPoint.r][nxtPoint.c];
			if (ch == 'D') return nxtCost-1;
			
			int nxtHP = curHP - (ch == BLOCK);
			if (nxtHP < 0) continue;

			if (cost[nxtHP][nxtPoint.r][nxtPoint.c]) continue;
			cost[nxtHP][nxtPoint.r][nxtPoint.c] = nxtCost;
			q.push({nxtHP, nxtPoint});
		}
	}
	return -1;
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	cout << bfs() << '\n';

}
void input() {
	cin >> R >> C; Point::setLimit(R, C);
	FOR(int, i, 0, R-1) cin >> s[i];

	FOR(int, i, 0, R-1) FOR(int, j, 0, C-1)
		if (s[i][j] == S) start = {i, j};
		else if (s[i][j] == D) dest = {i, j};
}