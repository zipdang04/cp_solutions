#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define first fi
#define second se

template <class T1, class T2> bool minimize(T1& a, T2 b) {return b < a ? (a=b, true) : false;}
template <class T1, class T2> bool maximize(T1& a, T2 b) {return b > a ? (a=b, true) : false;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)
#define all(v) v.begin(), v.end()
#define all(v, l, r) v.begin() + l, v.begin() + r + 1

#define MAX 1005
#define MOD

int n, m, k;
string s[MAX];
set<int> dotR[MAX], dotC[MAX];
int u(int row, int col) {
	if (s[row][col] != '#') return false;
	auto it = dotC[col].lower_bound(row);
	int r2 = (it == dotC[col].begin()) ? 1 : (*(--it) + 1); 
	// cerr << "u " << row << ' ' << col << '=' << row-r2+1 << '\n';
	return row - r2 + 1;
}
int d(int row, int col) {
	if (s[row][col] != '#') return false;
	auto it = dotC[col].upper_bound(row);
	int r2 = (it == dotC[col].end()) ? n : (*it - 1); 
	// cerr << "d " << row << ' ' << col << '=' << r2-row+1 << '\n';
	return r2 - row + 1;
}
int l(int row, int col) {
	if (s[row][col] != '#') return false;
	auto it = dotR[row].lower_bound(col);
	int c2 = (it == dotR[row].begin()) ? 1 : (*(--it) + 1); 
	// cerr << "l " << row << ' ' << col << '=' << col-c2+1 << '\n';
	return col - c2 + 1;
}
int r(int row, int col) {
	if (s[row][col] != '#') return false;
	auto it = dotR[row].upper_bound(col);
	int c2 = (it == dotR[row].end()) ? m : (*it - 1); 
	// cerr << "r " << row << ' ' << col << '=' << c2-col+1 << '\n';
	return c2 - col + 1;
}
// int u[MAX][MAX], d(MAX, MAX), l(MAX, MAX), r(MAX, MAX);

// v^><:  udlr
bool inside(int row, int col) {
	return row >= 1 and col >= 1 and row <= n and col <= m;
}
void add(int row, int col) {
	s[row][col] = '_';
	dotR[row].insert(col);
	dotC[col].insert(row);
}
bool checkU(int row, int col) {
	row += k-1; if (not inside(row, col)) return false;
	if (r(row, col) < k or u(row, col) < k) return false;
	int c2 = col + k-1;
	if (u(row, c2) < k) return false;
	// cerr << "U " << row << ' ' << col << '\n';

	FOR(int, i, 0, k-1) {
		if (i < k-1) assert(s[row][col + i] == '#');
		assert(s[row - i][col] == '#');
		assert(s[row - i][c2] == '#');
		add(row, col+i);
		add(row-i, col);
		add(row-i, c2);
		// s[row][col + i] = s[row - i][col] = s[row - i][c2] = '_';
	}
	return true;
}
bool checkD(int row, int col) {
	if (r(row, col) < k or d(row, col) < k) return false;
	int c2 = col + k-1;
	if (d(row, c2) < k) return false;
	// cerr << "D " << row << ' ' << col << '\n';

	FOR(int, i, 0, k-1) {
		if (i < k-1) assert(s[row][col + i] == '#');
		assert(s[row + i][col] == '#');
		assert(s[row + i][c2] == '#');
		add(row, col+i);
		add(row+i, col);
		add(row+i, c2);
		// s[row][col + i] = s[row + i][col] = s[row + i][c2] = '_';
	}
	return true;
}
bool checkL(int row, int col) {
	col += k-1; if (not inside(row, col)) return false;
	// cerr << "L1\n";
	if (d(row, col) < k or l(row, col) < k) return false;
	// cerr << "L2\n";
	int r2 = row + k-1;
	if (l(r2, col) < k) return false;
	// cerr << "L " << row << ' ' << col << '\n';

	FOR(int, i, 0, k-1) {
		if (i < k-1) assert(s[row + i][col] == '#');
		assert(s[row][col - i] == '#');
		assert(s[r2][col - i] == '#');
		add(row+i, col);
		add(row, col-i);
		add(r2, col-i);
		// s[row + i][col] = s[row][col - i] = s[r2][col - i] = '_';
	}
	return true;
}
bool checkR(int row, int col) {
	if (d(row, col) < k or r(row, col) < k) return false;
	int r2 = row + k-1;
	if (r(r2, col) < k) return false;
	// cerr << "R " << row << ' ' << col << '\n';

	FOR(int, i, 0, k-1) {
		if (i < k-1) assert(s[row + i][col] == '#');
		assert(s[row][col + i] == '#');
		assert(s[r2][col + i] == '#');
		add(row+i, col);
		add(row, col+i);
		add(r2, col+i);
		// s[row + i][col] = s[row][col + i] = s[r2][col + i] = '_';
	}
	return true;
}

void input();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		FOR(int, row, 1, n) FOR(int, col, 1, m)
			if (s[row][col] == '.')
				dotR[row].insert(col),
				dotC[col].insert(row);
		
		bool oke = true;
		FOR(int, row, 1, n) FOR(int, col, 1, m) {
			// if (not oke) break;
			if (s[row][col] != '#') continue;
			// FOR(int, r, 1, n) cerr << s[r] << "\n";
			// cerr << "> " << row << ' ' << col << '\n';
			if (checkU(row, col)) continue;
			// cerr << "notU\n";
			if (checkD(row, col)) continue;
			// cerr << "notD\n";
			if (checkL(row, col)) continue;
			// cerr << "notL\n";
			if (checkR(row, col)) continue;
			// cerr << "NOT ALL\n";
			oke = false; goto skip_here;
		}
		skip_here:
		cout << (oke ? "yes\n" : "no\n");
	}
}
void input() {
	cin >> n >> m >> k;
	FOR(int, i, 1, n) cin >> s[i];
	FOR(int, i, 1, n) s[i] = " " + s[i];
	FOR(int, i, 1, n) dotR[i].clear();
	FOR(int, i, 1, m) dotC[i].clear();
}