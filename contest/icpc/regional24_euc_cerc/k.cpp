#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	return b < a ? (a = b, true) : false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	return b > a ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 65
#define MOD

string s; int n;

string cur, ans; int cntAns = 0;
vector<int> removed;
void dqql(int pos) {
	if (pos == n) {
		if ((int)removed.size() > cntAns) ans = cur, cntAns = removed.size();
		return;
	}
	dqql(pos + 1); if (s[pos] == '#') return;
	for (int p2: removed) {
		if ((pos - p2) % 2) return;
		int mid = (pos + p2) / 2;
		if (cur[mid] == '.') return;
	}

	removed.push_back(pos); cur[pos] = '.';
	dqql(pos + 1);
	removed.pop_back(); cur[pos] = '#';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> s; n = s.length();
	if (n == 1) {
		cout << "1\n#\n";
		return 0;
	}
	FOR(int, i, 1, n) cur += "#"; ans = cur, cntAns = 0;
	dqql(0); cout << n - cntAns << '\n' << ans << '\n';
}
