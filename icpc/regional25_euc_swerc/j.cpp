#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 4004
#define MOD

bitset<MAX> f[MAX];
int n, m, a[MAX], b[MAX];

bool dp(){
	f[0][0] = true;
	FOR(int, iB, 1, m) {
		FOR(int, iA, 1, n) {
			if (f[iB][iA]) continue;

			if (a[iA] == b[iB] and f[iB-1][iA-1]) f[iB][iA] = true;
			if (b[iB] <= iA and f[iB-1][iA - b[iB]]) {
				while (iA <= n) f[iB][iA++] = true;
			}
		}
	}
	return f[m][n];
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		cout << (dp() ? "YES\n" : "NO\n");
		clear();
	}
}
void input() {
	cin >> n >> m;
	FOR(int, i, 1, n) cin >> a[i];
	FOR(int, i, 1, m) cin >> b[i];
}
void clear() {
	FOR(int, i, 1, m) f[i] = 0;
}
