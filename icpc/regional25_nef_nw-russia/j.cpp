#include <bits/stdc++.h>
using namespace std;

template<class T1, class T2> bool minimize(T1 &a, T2 b) {return b < a ? (a = b, true) : false;}
template<class T1, class T2> bool maximize(T1 &a, T2 b) {return b > a ? (a = b, true) : false;}

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define fi first
#define se second

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 100'005

int n;
pair<string, string> probs[MAX];
unordered_map<string, int> cntF, cntS;

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();

		FOR(int, i, 1, n)
			cntF[probs[i].fi]++,
			cntS[probs[i].se]++;

		bool oke = true;
		FOR(int, i, 1, n) {
			if (i > 1 and probs[i].fi != probs[i-1].fi and probs[i].se != probs[i-1].se) {
				if (cntF[probs[i-1].fi] or cntS[probs[i-1].se]) {
					oke = false; break;
				}
			}
			cntF[probs[i].fi]--, cntS[probs[i].se]--;
		}

		cout << (oke ? "Yes\n" : "No\n");

		clear();
	}
}
void input() {
	cin >> n;
	string s1, s2;
	FOR(int, i, 1, n) {
		cin >> s1 >> s2;
		probs[i] = {s1, s2};
	}
}
void clear() {
	cntF.clear(), cntS.clear();
}
