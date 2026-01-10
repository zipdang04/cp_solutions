#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> bool minize(T1 &a, T2 b) {return b < a ? ((a = b), true) : false;}
template<class T1, class T2> bool maxize(T1 &a, T2 b) {return b > a ? ((a = b), true) : false;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

#define MAX 105
#define MOD

#define DOT '.'
#define OBS 'X'
#define STA 'S'
#define FIN 'D'

struct Point{
	inline static int _R, _C;

	int r, c;
	Point() {}
	Point(int r, int c): r(r), c(c) {}
	static Point build(int idx){
		return Point(idx / _C, idx % _C);
	}

	int idx() const {return r * _C + c;}
	bool in() const {return r >= 0 and c >= 0 and r < _R and c < _C;}
};
const Point DIREC[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
Point operator + (Point a, Point b) {return {a.r + b.r, a.c + b.c};}

constexpr int OO = 1e9;

int R, C;
string brdA[MAX], brdB[MAX];
Point staA, staB;

int f[1005][1005];
queue<pii> q;
void bfs() {
	memset(f, 0x3f, sizeof f);
	f[staA.idx()][staB.idx()] = 0; q.push({staA.idx(), staB.idx()});
	while (not q.empty()) {
		auto [iA, iB] = q.front(); q.pop();
		Point posA = Point::build(iA), posB = Point::build(iB);
		int curF = f[iA][iB];
		// cerr << iA << ' ' << posA.r << '.' << posA.c << '|' << iB << ' ' << posB.r << '.' << posB.c << '|' << curF << '\n';
		for (auto d: DIREC) {
			Point newA = posA + d, newB = posB + d;
			if (not newA.in() or brdA[newA.r][newA.c] == OBS) continue;
			if (not newB.in() or brdB[newB.r][newB.c] == OBS) newB = posB;

			const int jA = newA.idx(), jB = newB.idx();
			if (f[jA][jB] < OO) continue;
			f[jA][jB] = curF + 1; q.push({jA, jB});
			if (brdB[newB.r][newB.c] == FIN) {
				cout << curF + 1 << '\n';
				return;
			}
		}
	}
	cout << "-1\n";
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		FOR(int, i, 0, R-1) FOR(int, j, 0, C-1) if (brdA[i][j] == STA) staA = {i, j};
		FOR(int, i, 0, R-1) FOR(int, j, 0, C-1) if (brdB[i][j] == STA) staB = {i, j};
		bfs();
		clear();
	}
}
void input(){
	cin >> R >> C; Point::_R = R, Point::_C = C;
	FOR(int, i, 0, R-1) cin >> brdA[i];
	FOR(int, i, 0, R-1) cin >> brdB[i];
}
void clear(){
	q = queue<pii>();
}
