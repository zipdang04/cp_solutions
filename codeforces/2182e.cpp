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
#define MOD 1000000007

struct Friend {int x, z;};
const int OO = 1e9;

int n, m; ll k;
int a[MAX]; Friend friends[MAX];
int req[MAX];

PQMax<int> pq;
PQMin<int> remain;
int calculate() {
	int ptr = 1, answer = 0;
	FOR(int, wrap, 1, m) {
		while (ptr <= n and friends[ptr].x <= a[wrap])
			pq.push(friends[ptr++].z);
		// cerr << wrap << ' ' << ptr << ' ' << friends[ptr].x << ' ' << a[wrap] << '\n';
		if (not pq.empty()) answer++, pq.pop();
	}
	while (not pq.empty()) { remain.push(pq.top()); pq.pop(); }
	while (ptr <= n) remain.push(friends[ptr++].z);
	// cerr << k << ' ' << remain.size() << '\n';
	// if (not remain.empty()) cerr << ":" << remain.top() << '\n';
	while (not remain.empty() and remain.top() <= k) {
		k -= remain.top(); remain.pop(); answer++;
	}
	return answer;
}
// void buildReq() {
// 	int ptr = 1;
// 	FOR(int, i, 1, n) {
// 		while (ptr <= m and a[ptr] < friends[i].x) ptr++;
// 		if (ptr > m) ptr = OO;
// 		req[i] = ptr;
// 	}
// }

// pll f[MAX][2];
// void dp() {
// 	f[1][0] = {friends[1].z, 0};
// 	if (req[1] != OO) f[1][1] = {0, req[1]};

// }

void input();
void clear();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		int ans = calculate();
		cout << ans << '\n';
		clear();
		// cerr << "==========\n";
	}
}
void input() {
	cin >> n >> m >> k;
	FOR(int, i, 1, m) cin >> a[i];
	// FOR(int, i, 1, m) cerr << a[i] << " \n"[i == m];

	int x, y, z;
	FOR(int, i, 1, n) {
		cin >> x >> y >> z;
		k -= y, z -= y;
		friends[i] = {x, z};
		// cerr << i << ' ' << x << '.' << z << '\n';
	}
	// cerr << "> " << k << "\n";

	sort(a + 1, a + 1 + m);
	sort(friends + 1, friends + 1 + n, [](Friend a, Friend b) {
		return (a.x != b.x) ? (a.x < b.x) : (a.z > b.z);
	});
}
void clear() {
	while (not pq.empty()) pq.pop();
	while (not remain.empty()) remain.pop();
}
