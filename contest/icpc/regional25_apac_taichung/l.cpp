#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define cntBit(n) __builtin_popcountll(1ll*n)
#define log2(n) (63-__builtin_clzll(1ll*n))

#define MAX 3005
#define oo 1'000'000'000

int n, m, k, a[MAX];

vector<int> pos; int len;
int f[MAX][MAX][2];
void fucked() {
	// cerr << '['; for (int i: pos) cerr << i << ' '; cerr << ']' << '\n';
	FOR(int, i, 0, len) FOR(int, j, 0, len) f[i][j][0] = f[i][j][1] = oo;
	f[0][a[pos[0]]][a[pos[0]]] = 0;
	if (pos[0] == k or pos[0] == n-k)
		f[0][!a[pos[0]]][!a[pos[0]]] = 1;
	for (int i = 0, nxt = 1; nxt < len; i++, nxt++) 
	FOR(int, valid, 0, nxt) FOR(int, cur, 0, 1) if (f[i][valid][cur] < oo){
		// cerr << i << ' ' << valid << ' ' << cur << '|' << f[i][valid][cur] << '\n';
		const int nxtCur = a[pos[nxt]];
		// nothing
		minimize(f[nxt][valid + nxtCur][nxtCur], f[i][valid][cur]);
		// i-nxt
		int nxtValid = valid + (cur ? -1 : 1) + (!nxtCur);
		// cerr << nxtValid << '\n';
		minimize(f[nxt][nxtValid][!nxtCur], f[i][valid][cur] + 1);
		
		if (pos[nxt] != k and pos[nxt] != n-k) continue;
		// nxt
		// cerr << "nxtValid" << '\n';
		minimize(f[nxt][valid + !nxtCur][!nxtCur], f[i][valid][cur] + 1);
		// i-nxt + nxt = i
		nxtValid = valid + (cur ? -1 : 1) + (nxtCur);
		minimize(f[nxt][nxtValid][nxtCur], f[i][valid][cur] + 2);
	}
	// FOR(int, valid, 0, len) FOR(int, cur, 0, 1) if (f[len-1][valid][cur] < oo) cerr << len-1 << ' ' << valid << ' ' << cur << '|' << f[len-1][valid][cur] << '\n';
}

int minCost[MAX], total, tmp[MAX];
void again() {
	// cerr << "again " << len << '\n';
	FOR(int, i, 0, len)
		tmp[i] = min(f[len-1][i][0], f[len-1][i][1]);
	
	// FOR(int, i, 0, total) cerr << minCost[i] << " |"[i == total];
	// FOR(int, i, 0, len) cerr << tmp[i] << " \n"[i == len];
	
	REV(int, val, total, 0) {
		if (minCost[val] < oo) FOR(int, j, 1, len) if (tmp[j] < oo)
			minimize(minCost[val+j], minCost[val] + tmp[j]);
	}
	FOR(int, val, 0, len)
		minimize(minCost[val], tmp[val]);
	total += len;
}

void input();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input(); if (n == 1) {cout << 1; return 0;}
	memset(minCost, 0x3f, sizeof minCost);
	FOR(int, i, 1, k) {
		// cerr << i << '\n';
		pos.clear(); 
		for (int p = i; p <= n-1; p += k) pos.push_back(p);
		len = pos.size();
		fucked(); again();
	}
	int ans = 1;
	REV(int, i, n-1, 0) if (minCost[i] <= m) {ans= i+1; break;}
	cout << ans << '\n';
}
void input(){
	cin >> n >> m >> k;
	string s;  cin >> s;
	FOR(int, i, 1, n-1)
		a[i] = s[i] != s[i-1];
}