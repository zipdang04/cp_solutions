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

#define MAX 50005
#define MOD

vector<int> ballots[MAX]; int cntBallot = 0;

int n, m;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	FOR(int, _, 1, m) {
		int a, b; cin >> a >> b;

		cntBallot++;
		FOR(int, i, 1, n) if (i != a and i != b) ballots[cntBallot].push_back(i);
		ballots[cntBallot].push_back(a);
		ballots[cntBallot].push_back(b);

		cntBallot++;
		ballots[cntBallot].push_back(a);
		ballots[cntBallot].push_back(b);
		REV(int, i, n, 1) if (i != a and i != b) ballots[cntBallot].push_back(i);
	}

	cout << "YES\n";
	cout << cntBallot << '\n';
	FOR(int, i, 1, cntBallot) FOR(int, j, 0, n-1) cout << ballots[i][j] << " \n"[j == n-1];
}
void input(){}
void clear(){}
