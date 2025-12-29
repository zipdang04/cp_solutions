#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 75
#define MOD

int n, m;
int all[MAX][MAX];
int nxt[MAX*MAX];
int perm[MAX*MAX], vis[MAX*MAX], cnt = 0;
void dfs(int u) {
	perm[++cnt] = u; vis[u] = true;
	if (nxt[u] and not vis[nxt[u]]) dfs(nxt[u]);
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		FOR(int, row, 1, n) FOR(int, col, 1, m-1) nxt[all[row][col]] = all[row][col+1];
		FOR(int, row, 1, n) if (not vis[all[row][1]]) dfs(all[row][1]);
		FOR(int, i, 1, cnt) cout << perm[i] << " \n"[i == cnt];
		clear();
	}
}
void input() {
	cin >> n >> m;
	FOR(int, i, 1, n) FOR(int, j, 1, m) cin >> all[i][j];
}
void clear() {
	FOR(int, i, 1, n*m) nxt[i] = 0;
	FOR(int, i, 1, n*m) vis[i] = 0;
	FOR(int, i, 1, n*m) perm[i] = 0;
	cnt = 0;
}
