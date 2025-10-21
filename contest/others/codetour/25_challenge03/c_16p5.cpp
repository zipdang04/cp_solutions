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

#define MAX_NM 1001
#define MAX_K 31
#define MOD 1000000007

#define S 'S'
#define F 'F'
#define COOL 'C'
#define BLOCK '#'

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

int N, M, K;
int visited[MAX_NM][MAX_NM];
string s[MAX_NM];
deque<tuple<int, int, Point>> q;
Point start, finish;

inline int bfs(Point start) {
	visited[start.r][start.c] = 1;
	q.push_back({0, 0, start});
	int curCost = 0;
	while (not q.empty()) {
		vector<tuple<int, int, Point>> all;
		while (not q.empty() and get<0>(q.front()) == curCost)
			all.push_back(q.front()), q.pop_front();
		for (auto [uCost, uCool, u]: all) {
			if (s[u.r][u.c] == F) return uCost;
			// cerr << uCool << '-' << u.r << ' ' << u.c << ' ' << s[u.r][u.c] << '|' << uCost << '\n';
			int vCost = uCost + 1 + (uCool == 0);
			for (Point v: u.getAdjacent()) {
				const char c = s[v.r][v.c];
				if (c == BLOCK) continue;
				int vCool = (c == 'C' ? K : (uCool - (uCool > 0)));
				if (testBit(visited[v.r][v.c], vCool)) continue;
				
				visited[v.r][v.c] |= (1 << (1 + vCool)) - 1;
				if (uCool > 0) q.push_front({vCost, vCool, v});
				else q.push_back({vCost, vCool, v});
			}
		}
		curCost++;
	}
	return -1;
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	cout << bfs(start) << '\n';
}
void input() {
	cin >> N >> M >> K;
	FOR(int, i, 0, N-1) cin >> s[i];
	Point::setLimit(N, M);

	FOR(int, i, 0, N-1) FOR(int, j, 0, M-1)
		if (s[i][j] == S)
			start = {i, j};
		else if (s[i][j] == F)
			finish = {i, j};
}