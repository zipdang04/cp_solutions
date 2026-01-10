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

#define MAX 150'005
#define MOD 1006903069

int n, kA, kB;
unordered_map<int, ll> A[MAX];

ll sum = 0;

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	cin >> n;
	cin >> kA;
	FOR(int, i, 1, kA) {
		int row, col, val; cin >> row >> col >> val;
		A[row][col] = val;
	}

	cin >> kB;
	FOR(int, i, 1, kB) {
		int row, col, val; cin >> row >> col >> val;
		sum += 1ll * val * A[col][row] % MOD;
		sum %= MOD;
	}
	cout << sum << '\n';
}
void input(){


}
void clear(){
	//
}
