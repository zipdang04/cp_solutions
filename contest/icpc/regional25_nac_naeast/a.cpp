#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX
#define MOD

int n, total[256] = {};

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	memset(total, false, sizeof(total));
	int n; cin >> n;
	FOR(int, i, 1, n) {
		char c; int num; cin >> c >> num;
		total[c] += num;
	}

	int ans = total['S'] / 6 + !!(total['S'] % 6);
	ans += total['M'] / 8 + !!(total['M'] % 8);
	ans += total['L'] / 12 + !!(total['L'] % 12);
	cout << ans << '\n';
}
void input(){}
void clear(){}
