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

#define MAX 200'005
#define MOD

struct Task{ll len, dl;};

int n, m, q;
Task tasks[MAX];
ll eps[MAX], sumLen[MAX];
ll start[MAX];
ll t[MAX];

int answer(ll time) {
	// cerr << time << " => ";
	int lastTask = upper_bound(tasks + 1, tasks + 1 + n, time, [](ll time, Task task) {return time <= task.dl;}) - tasks - 1;
	ll used = sumLen[lastTask];
	minimize(time, start[lastTask + 1]);
	ll freetime = time - used;

	// cerr << freetime << ' ' << used << "->" << time << '\n';
	ll ans = upper_bound(eps + 1, eps + 1 + m, freetime) - eps - 1;
	return ans;
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		FOR(int, i, 1, q) {
			int ans = answer(t[i]);
			cout << ans << " \n"[i == q];
		}
		clear();
		// cerr << "=========\n";
	}
}
void input() {
	cin >> n >> m >> q;
	FOR(int, i, 1, n) cin >> tasks[i].len;
	FOR(int, i, 1, n) cin >> tasks[i].dl;
	FOR(int, i, 1, m) cin >> eps[i];
	FOR(int, i, 1, q) cin >> t[i];

	sort(tasks + 1, tasks + 1 + n, [](Task a, Task b) {return a.dl < b.dl;});
	FOR(int, i, 1, n) sumLen[i] = sumLen[i-1] + tasks[i].len;
	start[n+1] = LLONG_MAX; 
	REV(int, i, n, 1) start[i] = min(start[i+1], tasks[i].dl) - tasks[i].len;
	FOR(int, i, 1, m) eps[i] += eps[i-1];
} 
void clear() {
	FOR(int, i, 0, n) sumLen[i] = 0;
	FOR(int, i, 0, n+1) start[i] = 0;
	FOR(int, i, 0, m+1) eps[i] = 0;
}