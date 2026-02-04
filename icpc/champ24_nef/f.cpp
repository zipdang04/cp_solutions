#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> 
bool minimize(T1 &a, T2 b) {
	return (b < a) ? (a = b, true) : false;
}
template<class T1, class T2> 
bool maximize(T1 &a, T2 b) {
	return (b > a) ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 200'005
#define MULTIPLE 2

#define cntBit(n) __builtin_popcountll(n)
#define testBit(n, bit) (((n) >> (bit)) & 1)

int n;
bool dam[MAX][2];

int f[MAX][5];

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _,1, tests) {
		input();

		f[0][0b11] = 1;
		for (int i = 0, nxt = 1; nxt <= n; i++, nxt++) {
			const int curMsk = (int(dam[nxt][1]) << 1) | int(dam[nxt][0]);
			// cerr << curMsk << '|' << (curMsk | 0b01) << ' ' << (curMsk | 0b10) << '\n';
			do {
				f[nxt][curMsk] += f[i][0b11];
				if (curMsk == 0b11) break;
				// // cerr << nxt << ":\t"; FOR(int, j, 0, 3) cerr << f[nxt][j] << " \n"[j == 3];
				if (curMsk == 0b00)
					f[nxt][0b11] += f[i][0b00] + f[i][0b11]; // = + ||
				// // cerr << nxt << ":\t"; FOR(int, j, 0, 3) cerr << f[nxt][j] << " \n"[j == 3];
				if (not testBit(curMsk, 0))
					f[nxt][curMsk | 0b01] += f[i][0b10];
				// // cerr << nxt << ":\t"; FOR(int, j, 0, 3) cerr << f[nxt][j] << " \n"[j == 3];
				if (not testBit(curMsk, 1))
					f[nxt][curMsk | 0b10] += f[i][0b01];
			} while (false);
			
			
			// // cerr << nxt << ":\t"; FOR(int, j, 0, 3) cerr << f[nxt][j] << " \n"[j == 3];
			FOR(int, msk, 0b00, 0b11)
				minimize(f[nxt][msk], MULTIPLE);
			// // cerr << nxt << ":\t"; FOR(int, j, 0, 3) cerr << f[nxt][j] << " \n"[j == 3];
		}
		if (f[n][0b11] == 0) cout << "None\n";
		else if (f[n][0b11] == 1) cout << "Unique\n";
		else cout << "Multiple\n";
		// cerr << "==========\n";

		clear();
	}
}
void input() {
	cin >> n;
	FOR(int, col, 0, 1) {
		string s; cin >> s;
		FOR(int, row, 1, n) 
			dam[row][col] = s[row-1] == '#';
	}
} 
void clear() {
	FOR(int, i, 0, n) dam[i][0] = dam[i][1] = false;
	FOR(int, i, 0, n) f[i][0] = f[i][1] = f[i][2] = f[i][3] = false;
}