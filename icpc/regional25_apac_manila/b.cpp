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

#define MAX_K 26
#define MAX_Q 100'005

int k, n, q;
char get(int pos) {
	pos--;
	char c = (pos / k + pos % k) % k + 'A';
	return c;
}

set<pii> events;
int start[MAX_Q];
map<int, vector<int>> add;

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> k >> n >> q;
	FOR(int, i, 1, q) {
		int pos, a, b; cin >> pos >> a >> b;
		events.insert({i, pos});
		//
	}
}
void input(){
	//
}
void clear(){
	//
}
