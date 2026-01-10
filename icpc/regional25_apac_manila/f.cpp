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

#define MAX 202

int ROW, COL; string board[MAX];
char R(int r, int c) {
	assert(c < COL-1);
	return board[r*2][c*2+1];
}
char D(int r, int c) {
	assert(r < ROW-1);
	return board[r*2+1][c*2];
}
bool checkRow(int rU, int rD, int cL, int cR, int row) { // row|row+1
	assert(row < rD);
	char need = D(row, cL);
	FOR(int, col, cL+1, cR) if (D(row, col) != need) return false;
	for (int r1 = row-1, r2 = row+1; rU <= r1 and r2 < rD; r1--, r2++) {
		bool same = D(r1, cL) == D(r2, cL);
		FOR(int, col, cL+1, cR)
			if (same != (D(r1, col) == D(r2, col))) return false;
	}

	for (int r1 = row, r2 = row+1; rU <= r1 and r2 <= rD; r1--, r2++)
		FOR(int, col, cL, cR-1)
			if (R(r1, col) == R(r2, col)) return false;
	return true;
}
bool checkCol(int rU, int rD, int cL, int cR, int col) { // row|row+1
	assert(col < cR);
	char need = R(rU, col);
	FOR(int, row, rU+1, rD) if (R(row, col) != need) return false;
	for (int c1 = col-1, c2 = col+1; cL <= c1 and c2 < cR; c1--, c2++) {
		bool same = R(rU, c1) == R(rU, c2);
		FOR(int, row, rU+1, rD)
			if (same != (R(row, c1) == R(row, c2))) return false;
	}

	for (int c1 = col, c2 = col+1; cL <= c1 and c2 <= cR; c1--, c2++)
		FOR(int, row, rU, rD-1)
			if (D(row, c1) == D(row, c2)) return false;
	return true;
}

bool check(int rU, int rD, int cL, int cR) {
	if (rU == rD and cL == cR) return true;
	FOR(int, row, rU, rD-1)
		if (checkRow(rU, rD, cL, cR, row)) {
			int up = row-rU+1, down = rD - row;
			if (up > down) return check(rU, row, cL, cR);
			return check(row+1, rD, cL, cR);
		}
	FOR(int, col, cL, cR-1)
		if (checkCol(rU, rD, cL, cR, col)) {
			int up = col-cL+1, down = cR - col;
			if (up > down) return check(rU, rD, cL, col);
			return check(rU, rD, col+1, cR);
		}
	return false;
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		cout << (check(0, ROW-1, 0, COL-1) ? "YES\n" : "NO\n");
		// cerr << '\n';
		clear();
	}
}
void input(){
	cin >> ROW >> COL;
	FOR(int, i, 0, ROW*2-2) cin >> board[i];
}
void clear(){
	//
}
