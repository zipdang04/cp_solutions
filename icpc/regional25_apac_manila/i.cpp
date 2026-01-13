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

#define MAX 1000001
#define MOD 1000696967

int n;
string s;

ll forw[MAX], back[MAX], ones[MAX];
int build(int d) {
	FOR(int, i, 0, n) ones[i] = 1;
	int ptr = 0; ll sum = 0;
	FOR(int, i, 1, n) {
		if (s[i] == d) {
			forw[ptr++] = sum+1;
			sum = 0; continue;
		}

		sum++;
		if (s[i] > d) (sum *= 10) %= MOD, (ones[ptr] *= 10) %= MOD;
	}
	forw[ptr] = sum+1;

	const int sz = ptr; sum = 0;
	REV(int, i, n, 1) {
		if (s[i] == d) {
			back[ptr--] = sum+1;
			sum = 0; continue;
		}
		sum++;
		if (s[i] > d) (sum *= 10) %= MOD;
	}
	assert(ptr == 0);
	back[ptr] = sum+1;
	return sz;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> s; n = s.length(); s = " " + s; FOR(int, i, 1, n) s[i] -= '0';
	ll answer = 0;
	REV(int, d, 9, 1) {
		const int sz = build(d);
		ll prv = forw[0] * d % MOD, acc = forw[0];
		FOR(int, i, 1, sz) {
			(answer += prv * back[i] % MOD) %= MOD;
			(acc = acc * ones[i] % MOD + forw[i]) %= MOD;
			(prv = prv * 10 % MOD * ones[i] % MOD + d * acc % MOD) %= MOD;
		}
	}
	cout << answer << '\n';
}

//
// 1111
