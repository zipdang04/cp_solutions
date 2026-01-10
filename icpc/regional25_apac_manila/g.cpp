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

#define MAX
#define MOD

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n, b; cin >> n >> b;
	int num, best = INT_MIN; bool done = false;
	FOR(int, i, 1, n-1) {
		cin >> num;
		if (num >= 0) b += num, done = true;
		else maxize(best, num);
	}
	if (not done and -best > b) b = -1;
	else if (not done) b += best;
	cout << b << '\n';
}
void input(){
	//
}
void clear(){
	//
}
