#include "bits/stdc++.h"
using namespace std;

template<class T1, class T2>
void minimize(T1&a, T2 b) { if (b < a) a = b; }
template<class T1, class T2>
void maximize(T1&a, T2 b) { if (b > a) a = b; }

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(num) __builtin_popcount(num)
#define testBit(num, bit) ((num) >> (bit) & 1)

#define MAX 105

struct Point { int x, y; Point() {x=y=0;} Point(int x, int y): x(x),y(y){}};
Point operator + (Point a, Point b) {return {a.x+b.x,a.y+b.y};}
const Point direc[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

int n, m;
char s[MAX][MAX];
Point root;
bool check(Point p) {
	return p.x >= 0 and p.y >= 0 and p.x < n and p.y < m;
}



bool visited[MAX][MAX];
long long dfs(Point p) {
	visited[p.x][p.y] = true;
	if (isdigit(s[p.x][p.y])) return s[p.x][p.y] - '0';
	vector<ll> all;
	for (Point d: direc) {
		Point newP = p + d;
		if (not check(newP)) continue;
		if (visited[newP.x][newP.y]) continue;
		if (s[newP.x][newP.y] == '.') continue;
		all.push_back(dfs(newP));
	}
	// cerr << p.x << ' ' << p.y << '|'; for (int i: all) cerr << i << ' ' ; cerr << '\n';
	if (s[p.x][p.y] == '#' || s[p.x][p.y] == 'P') {
		assert((all.size() == 1));
		return all[0];
	}
	assert(all.size() == 2);
	if (all[0] < all[1]) swap(all[0], all[1]);
	switch (s[p.x][p.y]) {
		case '+': return all[0] + all[1]; break;
		case '-': return all[0] - all[1]; break;
		case '*': return all[0] * all[1]; break;
		case '/': return all[0] / all[1]; break;
	}
}


void input();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	cout << dfs(root);
}
void input() {
	cin >> n >> m;
	FOR(int, i, 0, n-1) cin >> s[i];
	FOR(int, i, 0, n-1) FOR(int, j, 0, m-1) if (s[i][j] == 'P') root = {i, j};
}
