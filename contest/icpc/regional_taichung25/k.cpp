#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define cntBit(n) __builtin_popcountll(1ll*n)
#define log2(n) (63-__builtin_clzll(1ll*n))

#define MAX_N 1005
#define MAX_VAL 1'000'000
#define NaN -1

int n, m, q;
char s[MAX_N][MAX_N];
int cnt[MAX_VAL + 1];

bool check(int x, int y) {return 0 <= x and x < n and 0 <= y and y < m;}

void dfs(int x, int y, int addX, int addY) {
	// cerr << x << ' ' << y << ' ' << addX << ' ' << addY << '\n';
	ll sum = 0, mul = NaN, cur = NaN;
	bool prvSign = true, ongoing = true, oke = false;
	while (check(x, y) and ongoing) {
		switch (s[x][y]) {
			case '+': {
				if (prvSign) {ongoing = false; break;} prvSign = true;
				mul = (mul == NaN) ? cur : mul * cur;
				sum = (sum == NaN) ? mul : sum + mul;
				mul = cur = NaN;
			} break;
			case '*': {
				if (prvSign) {ongoing = false; break;} prvSign = true;
				mul = (mul == NaN) ? cur : mul * cur;
				cur = NaN;
			} break;
			default: {
				// cerr << x << ' ' << y << '|' << s[x][y] << "=>";
				prvSign = false; assert(isdigit(s[x][y]));
				cur = ((cur == NaN) ? 0 : (cur*10)) + (s[x][y] - '0');
				ll val = (sum == NaN ? 0 : sum) + (mul == NaN ? 1 : mul) * cur;
				// cerr << (oke ? val : -1) << '\n';
				if (val > MAX_VAL) {ongoing = false; break;}
				cnt[val] += oke;
			}
		}
		x += addX, y += addY; oke = true;
	}
}

void input();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	FOR(int, x, 0, n-1) FOR(int, y, 0, m-1) {
		dfs(x, y, 0, -1); 
		dfs(x, y, 0, 1); 
		dfs(x, y, -1, 0);
		dfs(x, y, 1, 0);
		dfs(x, y, 1, 1);
		dfs(x, y, 1, -1);
		dfs(x, y, -1, 1);
		dfs(x, y, -1, -1);
		if (isdigit(s[x][y])) cnt[s[x][y] - '0']++;
	}
	
	FOR(int, i, 1, q) {
		int num; cin >> num;
		cout << cnt[num] << '\n';
	}
}
void input(){
	cin >> n >> m >> q;
	FOR(int, i, 0, n-1) cin >> s[i];
}