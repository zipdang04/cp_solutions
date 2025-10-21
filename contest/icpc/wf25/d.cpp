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

#define MAX 205
#define MOD 1000000007

struct Point{
	int x, y;
	Point(int x, int y): x(x), y(y) {}
	Point() {x=y=0;}
	inline void _selfMove(char c) {
		if (c == 'N') x--;
		else if (c == 'W') y--;
		else if (c == 'S') x++;
		else if (c == 'E') y++;
		else assert(false);
	}
	inline Point move(char c) const {
		Point p = *this;
		p._selfMove(c); return p;
	}
	// inline static Point move(Point p, char c) {
	// 	return p.move(c);
	// }
};

const string DIREC[24] = {
	"NEWS", "NESW", "NSWE", "NSEW", "NWES", "NWSE",
	"SNWE", "SNEW", "SEWN", "SENW", "SWNE", "SWEN",
	"ENWS", "ENSW", "ESWN", "ESNW", "EWNS", "EWSN",
	"WENS", "WESN", "WSNE", "WSEN", "WNES", "WNSE",
};

int R, C, n;
string board[MAX], s;
Point start;

int f[MAX * MAX][24];

char findFirst(const Point p, const string &P) {
	for (char c: P) {
		Point newP = p.move(c);
		if (board[newP.x][newP.y] != '#') return c;
	}
	assert(false);
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();

	memset(f, 0x3f, sizeof(f));
	FOR(int, i, 0, 23) f[0][i] = 0;
	for (int i = 0, nxt = 1; nxt <= n; i++, nxt++) {
		FOR(int, d, 0, 23)
			if (findFirst(start, DIREC[d]) == s[nxt])
				f[nxt][d] = f[i][d];
		FOR(int, d, 0, 23) FOR(int, d2, 0, 23) if (d != d2)
			if (findFirst(start, DIREC[d2]) == s[nxt])
				minimize(f[nxt][d2], f[i][d] + 1);

		start._selfMove(s[nxt]);
	}

	int answer = INT_MAX; string hihi = "";
	FOR(int, d, 0, 23) if (f[n][d] < answer)
		answer = f[n][d], hihi = DIREC[d];
	cout << answer << '\n';
}
void input() {
	cin >> R >> C;
	FOR(int, i, 1, R) {
		cin >> board[i];
		board[i] = "#" + board[i] + "#";
	}
	cin >> s; n = s.length(); s = " " + s;
	FOR(int, row, 1, R) FOR(int, col, 1, C) if (board[row][col] == 'S') start = {row, col};
	FOR(int, col, 0, C+1) board[0] += '#';
	FOR(int, col, 0, C+1) board[R+1] += '#';

}