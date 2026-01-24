#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> se;
#define fi first
#define se second

template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	return b < a ? (a = b, true) : false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	return b > a ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 200'005
#define MOD

int n;
string s[MAX], t;
string answer;

vector<int> remain, stage1;

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	while (not t.empty()) {
		char c = *t.rbegin();
		// cerr << "> " << c << "===============\n";
		for (int pos: remain) {
			while (not s[pos].empty()) {
				char cur = *s[pos].rbegin();
				if (cur == c) break;
				// cerr << cur << ' ';
				answer += cur; s[pos].pop_back();
			}
			// cerr << pos << ' ' << s[pos] << '\n';
			if (not s[pos].empty()) stage1.push_back(pos);
		}
		if (stage1.empty()) break;
		t.pop_back();

		answer += c;
		remain = stage1; stage1.clear();
		for (int pos: remain) s[pos].pop_back();

		// FOR(int, i, 1, n) cerr << s[i] << "|\n"[i == n];
	}
	if (not t.empty()) cout << "YES\n" << answer << '\n';
	else cout << "NO\n";
}
void input(){
	cin >> n;
	FOR(int, i, 1, n) cin >> s[i];
	cin >> t;

	FOR(int, i, 1, n) reverse(s[i].begin(), s[i].end());
	reverse(t.begin(), t.end());

	remain.resize(n); iota(remain.begin(), remain.end(), 1);
	// for (int i: remain) cerr << i << ' '; cerr << '\n';
}
void clear(){}
