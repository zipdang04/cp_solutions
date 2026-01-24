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

#define MAX
#define MOD

int n;
string s;

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> n >> s;

		int same = 0;
		FOR(int, i, 0, n-1) same += s[i] == 'W';
		if (same % 2) {cout << "NO\n"; continue;}

		bool oke = true;
		int block = same / 2;
		FOR(int, i, 0, block-1) oke &= s[i] == 'W';
		FOR(int, i, n*2-block, n*2-1) oke &= s[i] == 'R';

		cout << (oke ? "YES\n" : "NO\n");
	}
}
void input(){}
void clear(){}
