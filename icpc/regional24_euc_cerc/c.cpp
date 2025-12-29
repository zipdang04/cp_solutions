#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	if (b < a) return a = b, true; return false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	if (b > a) return a = b, true; return false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX
#define MOD

map<string, vector<string>> nick, name;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n; cin >> n;
	FOR(int, i, 1, n) {
		string s; cin >> s;
		nick[s.substr(0, 4)].push_back(s);
	}
	FOR(int, i, 1, n) {
		string s; cin >> s;
		name[s.substr(0, 4)].push_back(s);
	}

	for (auto [s, _]: nick)
		if (name[s].size() != _.size()) {
			cout << "NO\n";
			return 0;
		}
	cout << "YES\n";
	for (auto [s, _]: nick) {
		FOR(int, i, 0, _.size()-1) cout << _[i] << ' ' << name[s][i] << '\n';
	}
}
