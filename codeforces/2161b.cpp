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

#define MAX 105
#define MOD 1000000007

int n;
bitset<MAX> state[MAX];

bool firstCheck() {
	FOR(int, row, 1, n) FOR(int, col, 1, n-2) {
		if (state[row][col] and state[row][col+1] and state[row][col+2])
			return false;
		if (state[col][row] and state[col+1][row] and state[col+2][row])
			return false;
	}
	return true;
}
bool secondCheck() {
	FOR(int, row, 1, n) {
		bool one = false, two = false;
		FOR(int, col, 1, n) {
			if (state[row][col] == 0) {
				if (not one) continue;
				two = true;
			} else {
				one = true;
				if (two) return false;
			}
		}
	}
	FOR(int, col, 1, n) {
		bool one = false, two = false;
		FOR(int, row, 1, n) {
			if (state[col][row] == 0) {
				if (not one) continue;
				two = true;
			} else {
				one = true;
				if (two) return false;
			}
		}
	}
	return true;
}
bool thirdCheck() {
	int row, col = n+1;
	for (row = 1; row <= n; row++) {
		for (col = 1; col <= n; col++)
			if (state[row][col]) break;
		if (col <= n) break;
	}

	int count = 0;
	FOR(int, r, 1, n) FOR(int, c, 1, n)
		count += state[r][c];
	if (count != 4) return false;
	FOR(int, addR, -1, 0) FOR(int, addC, -1, 0) {
		if (row+addR < 1) continue;
		if (col+addC < 1) continue;
		int r = row + addR, c = col + addC;
		if (state[r][c] and state[r][c+1] and state[r+1][c] and state[r+1][c+1])
			return true;
	}
	return false;
}
bool forthCheck() {
	int row, col = n+1;
	for (row = 1; row <= n; row++) {
		for (col = 1; col <= n; col++)
			if (state[row][col]) break;
		if (col <= n) break;
	}
	int count = 0;
	FOR(int, r, 1, n) FOR(int, c, 1, n)
		count += state[r][c];

	int expectedCol = col - (row-1);
	// case 1
	int curCount = 0, needCol = expectedCol;
	FOR(int, row, 1, n) {
		if (1 <= needCol and needCol <= n)
			curCount += state[row][needCol];
		if (1 <= needCol+1 and needCol+1 <= n)
			curCount += state[row][needCol+1];
		needCol++;
	}
	if (curCount == count) return true;
	// case 2
	curCount = 0, needCol = expectedCol;
	FOR(int, row, 1, n) {
		if (1 <= needCol and needCol <= n)
			curCount += state[row][needCol];
		if (1 <= needCol-1 and needCol-1 <= n)
			curCount += state[row][needCol-1];
		needCol++;
	}
	if (curCount == count) return true;
	// case 3
	expectedCol = col + (row-1);
	curCount = 0, needCol = expectedCol;
	FOR(int, row, 1, n) {
		if (1 <= needCol and needCol <= n)
			curCount += state[row][needCol];
		if (1 <= needCol-1 and needCol-1 <= n)
			curCount += state[row][needCol-1];
		needCol--;
	}
	if (curCount == count) return true;
	// case 4
	curCount = 0, needCol = expectedCol;
	FOR(int, row, 1, n) {
		if (1 <= needCol and needCol <= n)
			curCount += state[row][needCol];
		if (1 <= needCol+1 and needCol+1 <= n)
			curCount += state[row][needCol+1];
		needCol--;
	}
	if (curCount == count) return true;
	return false;
}

void input();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _,1, tests) {
		input();
		state[0] = 0; FOR(int, i, 1, n) state[0] |= state[i];
		if (state[0] == 0) {cout << "YES\n"; continue;}
		if (not firstCheck()) { cout << "NO\n"; continue; }
		if (not secondCheck()) { cout << "NO\n"; continue; }
		if (thirdCheck()) { cout << "YES\n"; continue; }
		if (forthCheck()) { cout << "YES\n"; continue; }
		cout << "NO\n";
	}
}
void input() {
	cin >> n;
	FOR(int, i, 1, n) state[i] = 0;
	FOR(int, i, 1, n) {
		string s; cin >> s;
		FOR(int, j, 1, n) state[i][j] = s[j-1] == '#';
	}
}
