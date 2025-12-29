#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	if (b < a) return a = b, true; return false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	if (b > a) return a = b, true; return false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 1005
#define MOD

struct Point {
	inline static int _N;
	int r, c;
	Point() {}
	Point(int r, int c): r(r), c(c) {}
	friend Point operator + (Point a, Point b) {return  {a.r + b.r, a.c + b.c};}
	bool isInside() const {return 1 <= r and 1 <= c and r <= _N and c <= _N;}
};
const Point DIREC[4] = {{0, +1}, {-1, 0}, {0, -1}, {+1, 0}}; // RULD

#define BLOCK '#'
#define EMPTY '.'
#define WIN 'O'

int n, q;
char board[MAX][MAX];

#define NOT_YET -100
#define VISITING 0
#define NO -1
int res[MAX][MAX][4];
stack<pair<Point, int>> st;

int iter = 0;
inline void dfs(Point pos, int direc) {
	int ans = VISITING;
	while (ans == VISITING) {
		assert((++iter <= 4*n*n));
		st.push({pos, direc});
		// cerr << '(' << pos.r << '.' << pos.c << ' ' << "RULD"[direc] << ')';
		res[pos.r][pos.c][direc] = VISITING;

		bool fail = true;
		for (int i = 1, newD = (direc+3) % 4; i <= 4; i++, newD = (newD + 1)%4) {
			Point newPos = pos + DIREC[newD];
			if (not newPos.isInside()) {fail = false, ans = 1; break;}
			if (board[newPos.r][newPos.c] == BLOCK) continue;

			fail = false;
			int newRes = res[newPos.r][newPos.c][newD];
			if (newRes > NOT_YET)
				ans = (newRes == NO or newRes == VISITING) ? NO : newRes + 1;
			else
				tie(pos, direc) = {newPos, newD};
			break;
		}
		if (fail) ans = NO;
	}
	// cerr << '\n';
	while (st.empty() == false) {
		auto [pos, d] = st.top(); st.pop();
		res[pos.r][pos.c][d] = (ans == NO) ? NO : ans++;
	}
}

void input();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	memset(res, -0x3f, sizeof(res));
	// cerr << res[0][0][0] << '\n';
	input();
	FOR(int, r, 1, n) FOR(int, c, 1, n)
		if (board[r][c] != BLOCK) FOR(int, d, 0, 3)
			if (res[r][c][d] < NOT_YET) {
				dfs({r, c}, d);
				// cerr << '\n';
			}
	// cerr << "oke\n";
	FOR(int, __, 1, q) {
		int r, c; char d; cin >> r >> c >> d;
		if (board[r][c] == BLOCK) {
			cout << NO << '\n';
			continue;
		}
		// assert(board[r][c] != BLOCK);
		switch(d) {
			case 'R': d = 0; break;
			case 'U': d = 1; break;
			case 'L': d = 2; break;
			case 'D': d = 3; break;
			default: assert(false);
		}

		cout << res[r][c][d] << '\n';
	}
}
void input() {
	cin >> n >> q; Point::_N = n;
	FOR(int, i, 1, n) cin >> board[i];
	FOR(int, i, 1, n) REV(int, j, n, 1)  board[i][j] = board[i][j-1];
}
