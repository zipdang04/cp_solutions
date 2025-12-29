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

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n, W = INT_MAX, H = INT_MAX, D = INT_MAX;
	cin >> n;
	FOR(int, _, 1, n) {
		int w, h, d; cin >> w >> h >> d;
		if (w > h) swap(w, h);
		if (w > d) swap(w, d);
		if (h > d) swap(h, d);
		minimize(W, w);
		minimize(H, h);
		minimize(D, d);
	}

	cout << 1ll * W * H * D;
}
void input() {}
void clear() {}
