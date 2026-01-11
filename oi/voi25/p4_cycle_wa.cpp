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

#define MAX 240005
#define MOD 1000000007

int n, m, l;
int p[MAX], q[MAX];
ll sumP[MAX], sumQ[MAX];

ll fP[MAX], fQ[MAX];
ll calCost(ll *sum, ll beg, ll end, ll value) {
	// todo: reprocess this shit
	ll mid = (beg + end) / 2; value -= mid;
	return value * (mid - beg + 1) - (sum[mid] - sum[beg - 1])
		 + (sum[end] - sum[mid]) - value * (end -  mid);
}
//		      p/q     sum       m/l     fP/fQ				
void cal(int *pos, ll *sum, int len, ll *f){
	FOR(int, i, 1, n * 2) f[i] = -1;

	int beg = 1, end = len, mid = (beg + end) / 2;
	int value = pos[mid];
	while (end <= len * 2) {
		// process
		f[value] = calCost(sum, beg, end, value) + mid - beg;
		// cerr << value << '|' << beg << '-' << end << ':' << f[value] << ' ';
		
		// change
		value++;
		if (value == pos[mid + 1]) {
			beg++, mid++, end++;
		}
	}
	// cerr << '\n';
	FOR(int, i, 1, n) if (f[i] < 0) f[i] = f[i + n];
}

void input();
void clear();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef HIEU
	freopen("cycle.inp", "r", stdin);
	freopen("cycle.out", "w", stdout);
	#endif
	int tests; cin >> tests;
	FOR(int, __, 1, tests) {
		input();
		cal(p, sumP, m, fP);
		cal(q, sumQ, l, fQ);
		
		int cntQAllowed = (n - m) - l + 1;
		ll answer = LLONG_MAX;
		FOR(int, posP, 1, n) {
			ll current = LLONG_MAX;
			FOR(int, posQ, posP + m,  posP + m + cntQAllowed - 1)
				minimize(current, fQ[posQ]);
			current += fP[posP];
			minimize(answer, current);
		}
		cout << answer << '\n';

		clear();
	}
}
void input(){
	cin >> n >> m >> l;
	FOR(int, i, 1, m) cin >> p[i];
	FOR(int, i, 1, l) cin >> q[i];
	sort(p + 1, p + 1 +m);
	sort(q + 1, q + 1 +l);
	FOR(int, i, m + 1, m + m) p[i] = p[i - m] + n;
	FOR(int, i, l + 1, l + l) q[i] = q[i - l] + n;

	FOR(int, i, 1, 2 * m) sumP[i] = sumP[i - 1] + p[i] - i;
	FOR(int, i, 1, 2 * l) sumQ[i] = sumQ[i - 1] + q[i] - i;
}
void clear(){

}