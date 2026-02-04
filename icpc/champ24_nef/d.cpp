#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> 
bool minimize(T1 &a, T2 b) {
	return (b < a) ? (a = b, true) : false;
}
template<class T1, class T2> 
bool maximize(T1 &a, T2 b) {
	return (b > a) ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(n) __builtin_popcountll(n)
#define testBit(n, bit) (((n) >> (bit)) & 1)

#define MAX 100'005
#define MOD

#define SET true
#define UNSET false

int n, m;
vector<int> graph[MAX];
bool type[MAX], res[MAX];
int degIn[MAX];

queue<int> s0, u0;
int s1, u1;
int remain[MAX];
vector<int> order;
void add(int v) {
	// cerr << "add: " << v << ' ';
	assert(remain[v] == 0);
	bool t = type[v], r = res[v];
	// cerr << (t ? 's' : 'r') << r << '\n';
	if (r == false) {
		if (t == SET) s0.push(v);
		else u0.push(v);
	} else {
		if (t == SET) s1 = v;
		else u1 = v;
	}
}
void remove(int u) {
	// cerr << "remove: " << u << '\n';
	assert(u > 0);
	assert(remain[u]-- == 0);
	order.push_back(u);
	for (int v: graph[u])
		if (--remain[v] == 0) add(v);
}
int popFrom(queue<int> &q) {
	if (q.empty()) return false;
	int u = q.front(); q.pop();
	remove(u); return u;
}
bool check(bool curState = false) {
	// cerr << "check\n";
	int flipCnt = 0;
	while (true) {
		int u = (curState == SET) ? popFrom(s0) : popFrom(u0);
		if (u > 0) {continue;}

		// cerr << "switch\n";
		if (curState == SET) {
			if (u1 == 0) break;
			u = u1; u1 = 0;
		} else {
			if (s1 == 0) break;
			u = s1; s1 = 0;
		}
		// cerr << "to " << !curState << " by " << u << '\n';
		remove(u); curState = !curState;
		if (++flipCnt > 2) return false;
	}
	// cerr << "finished\n";
	// // for (int u: order) cerr << u << ' '; cerr << '\n';
	return (int)order.size() == n;
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	FOR(int, i, 1, n) remain[i] = degIn[i];
	FOR(int, i, 1, n) if (degIn[i] == 0) add(i);
	if (not check(false)) cout << "-1\n";
	else {
		for (int u: order) cout << u << ' ';
		cout << '\n';
	}
}
void input() {
	cin >> n;
	string t, r; 
	FOR(int, i, 1, n) {
		cin >> t >> r;
		type[i] = t == "set";
		res[i] = r == "true";
	}
	cin >> m;
	int u, v;
	FOR(int, i, 1, m) {
		cin >> u >> v;
		graph[u].push_back(v);
		degIn[v]++;
	}
} 
void clear() {
	// 
}