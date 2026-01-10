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
#define TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()

#define MAX 255
#define MOD

ll r, c, a[MAX][MAX];
ll d[MAX];
ll answer = LLONG_MAX, opt;
stack<pll> cur[MAX];
void dqql(int pos, int cnt, ll flat, ll curSum = 0) {
	if (pos == r) {
		if (cnt == 0) return;
		minize(answer, flat + curSum);
		return;
	}

	dqql(pos+1, cnt, flat, curSum);
	if (cnt+1 > c) return;

	if (flat + d[pos] + opt > answer) return;

	bool oke = false;
	FOR(int, i, 0, c-1) if (a[pos][i] < cur[i].top().se)
		oke = true, curSum += (cur[i].size() == 1) ? a[pos][i] : a[pos][i] - cur[i].top().se, cur[i].push({pos, a[pos][i]});
	if (not oke) return;

	dqql(pos+1, cnt+1, flat + d[pos], curSum);
	FOR(int, i, 0, c-1) if (cur[i].top().fi == pos) cur[i].pop();

}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	FOR(int, i, 0, 250) cur[i].push({0, LLONG_MAX});
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		dqql(0, 0, 0);
		cout << answer << '\n';
		clear();
	}
}

mt19937_64 mt(TIMESTAMP);
int perm[MAX];
void input(){
	cin >> c >> r;
	iota(perm,perm+r, 0);
	shuffle(perm, perm+r, mt);
	FOR(int, i, 0, c-1) {
		FOR(int, j, 0, r-1) cin >> a[perm[j]][i];
		ll tmp = LLONG_MAX;
		FOR(int, j, 0, r-1) minize(tmp, a[perm[j]][i]);
		opt += tmp;
	}
	FOR(int, i, 0, r-1) cin >> d[perm[i]];
}
void clear(){
	answer = LLONG_MAX, opt = 0;
}
