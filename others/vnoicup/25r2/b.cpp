#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
template <class T> using PQMax = priority_queue<T>;
template <class T> using PQMin = priority_queue<T, vector<T>, greater<T>>;
template <class T1, class T2>
void maximize(T1 &a, T2 b){
	if (b > a) a = b;
}
template <class T1, class T2>
void minimize(T1 &a, T2 b){
	if (b < a) a = b;
}
template <class T>
void read(T &number)
{
	bool negative = false;
	register int c;
	number = 0;
	c = getchar();
	while (c != '-' && !isalnum(c)) c = getchar();
	if (c=='-'){
		negative = true;
		c = getchar();
	}
	for (; (c>47 && c<58); c=getchar())
		number = number *10 + c - 48;
	if (negative)
		number *= -1;
}
template <class T, class ...Ts>
void read(T &a, Ts& ... args){
	read(a);
	read(args...);
}

/*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define REV(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define log2(n) (31 - __builtin_clz(n))
#define log2ll(n) (63 - __builtin_clzll(n))
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

#define MAX 50
#define MOD 1000000007

ll n, m;
map<int, int> pwN, pwM;
ll step[MAX];
ll power(ll a, ll n) {
	ll ans = 1;
	FOR(int, i, 1, n) ans *= a;
	return ans;
}

void build(int num, map<int, int> &pw) {
	for (ll d = 2; d * d <= num; d++)
		while (num % d == 0) num /= d, pw[d]++;
	if (num > 1) pw[num] = 1;
}
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int _t; cin >> _t;
	FOR(int, _, 1, _t) {
		memset(step, false, sizeof(step));
		FOR(int, i, 1, 40) step[i] = 1;
		pwN.clear(), pwM.clear();

		cin >> n >> m;
		build(n, pwN), build(m, pwM);
		
		bool oke = true;
		// cerr << n << ' ' << m << '\n';
		for (auto [p, pw]: pwN) 
			if (pwM[p] == 0) oke = false;
		if (not oke) {cout << "-1\n"; continue;}
		for (auto [p, pw]: pwM) {
			// cerr << p << ' ' << pwN[p] << "=>" << pw << '\n';
			if (pwN[p] == 0 or pwN[p] > pw) { oke = false; break; }
			int from = pwN[p], to = pw;
			for (int i = 1; from < to; i++)
			if (from * 2 <= to) {
				step[i] *= power(p, from);
				from *= 2;
			} else {
				step[i] *= power(p, to - from);
				from += to - from;
			}
		}

		if (not oke) {cout << "-1\n"; continue;}
		int ans = 0;
		while (step[ans + 1] > 1) ans++;
		cout << ans << ' ';
		if (ans == 0) cout << '\n';
		else
			FOR(int, i, 1, ans) cout << step[i] << " \n"[i == ans];
	}
}