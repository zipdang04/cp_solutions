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

#define MAX 2003
#define MOD 1000000007

struct Point {
	int x, y; 
	Point(int x, int y): x(x), y(y){}
	Point(): Point(0, 0) {}
	Point operator + (Point p) const { return {x + p.x, y + p.y}; }
	Point operator - (Point p) const { return {x - p.x, y - p.y}; }
};
const Point DIREC[4] = {Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1)};
#define DIREC_CODE "ULDR"

int n, m, k;
string s[MAX];

struct State {
	short cnt[MAX][MAX] = {};
	Point pos; int visited;
	State(){}
	State(Point pos): pos(pos), visited(0){
		_add(pos);
	}
	stack<stack<Point>> history;

	inline void _add(const Point &pos) {
		visited += cnt[pos.x][pos.y]++ == 0;
		// cerr << "add " << pos.x << ' ' << pos.y << '|' << cnt[pos.x][pos.y] << '\n';
	}
	inline void _del(const Point &pos) {
		visited -= --cnt[pos.x][pos.y] == 0;
		// cerr << "del " << pos.x << ' ' << pos.y << '|' << cnt[pos.x][pos.y] << '\n';
	}

	inline void move(const int d) {
		stack<Point> curHistory;
		while (true) {
			Point newPos = pos + DIREC[d];
			if (s[newPos.x][newPos.y] == '#') break;
			_add(newPos); curHistory.push(pos);
			pos = newPos;
		}
		history.push(curHistory);
	}
	inline void unmove() { 
		stack<Point> lastHistory = history.top(); history.pop();
		while (not lastHistory.empty()) {
			Point newPos = lastHistory.top(); lastHistory.pop();
			_del(pos); pos = newPos;
		}
	}
} original;

pair<int, string> dqql(string prefix, int remainDepth, State &state, int prev = -1) {
	// cerr << prefix << ' ' << remainDepth << ' ' << ' ' << state.pos.x << '.' << state.pos.y << ' ' <<  state.visited << '\n';
	if (remainDepth == 0) return {state.visited, prefix};
	pair<int, string> ans = {0, ""};
	FOR(int, d, 0, 3) if (d != prev) {
		state.move(d);
		auto cur = dqql(prefix + DIREC_CODE[d], remainDepth - 1, state, d);
		state.unmove();
		ans = max(ans, cur);
	}
	return ans;
}


Point oriPos;

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cerr << "here" << endl;
	input();
	cerr << "here" << endl;
	original = State(oriPos);
	int depth = min(14, k);
	
	string answer = ""; int best = 0, prv = -1;
	FOR(int, i, 1, k-depth+1) {
		cerr << i << endl;
		State copied = original;
		auto [res, haha] = dqql("", depth, copied, prv);
		best = res;
		if (i == k-depth+1) answer += haha;
		else {
			char c = haha[0];
			int d; for (d = 0; d < 4; d++) if (c == DIREC_CODE[d]) break;
			prv = d;
			original.move(d); answer += c;
		}
		cerr << "oke" << endl;
	}

	cout << answer << endl;
	cerr << best << '\n';
}

void input(){
	cin >> n >> m >> k;
	FOR(int, i, 1, n) {
		cin >> s[i]; s[i] = " " + s[i];
	}
	FOR(int, i, 0, m+1) s[0] += "#", s[n+1] += '#';
	FOR(int, i, 0, m+1) s[0][i] = s[n+1][i] = true;
	FOR(int, i, 0, n+1) s[i][0] = s[i][n+1] = true;
	FOR(int, i, 1, n) FOR(int, j, 1, m) 
		if (s[i][j] == 'O') oriPos = {i, j};
}