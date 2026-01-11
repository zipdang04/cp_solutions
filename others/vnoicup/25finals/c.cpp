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

bool notPrime[MAX + 1]; 
int primes[MAX + 1], cntP;
void sieve() {
	for (int i = 2; i <= MAX; i++) if (not notPrime[i]) {
		primes[++cntP] = i;
		for (ll j = 1ll * i * i; j <= MAX; j += i)
			notPrime[j] = true;
	}
}

int n;
int a[MAX];
bool marked[MAX + 1];
void marking(int p) {
	for (int i = p * 2; i <= n; i += p)
		marked[i] = true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	sieve();
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> n; FOR(int, i, 2, n) cin >> a[i];
		FOR(int, i, 2, n) marked[i] = false;

		queue<int> passed;
		int ptr = 2; ll ans = 0;
		vector<int> newA;
		FOR(int, i, 2, n) {
			// cerr << _ << ' ' << i << '\n';
			int value = a[i];
			if (not notPrime[value]) {
				if (not passed.empty() and passed.front() == i){
					passed.pop(); continue;
				}
				marking(value); newA.push_back(value);
				continue;
			}
			// cerr << "value " << value << ' ' << marked[value] << '\n';
			if (marked[value]) {
				newA.push_back(value); continue;
			}
			// cerr << "need\n";
			maximize(ptr, i + 1);
			while (true) {
				while (notPrime[a[ptr]]) ptr++;
				int prime = a[ptr]; 
				marking(prime); passed.push(ptr++);newA.push_back(prime);
				// cerr << "//" << prime << ' ' << ptr << ' ' << newA.size() << '\n';
				ans += (ptr-1) - ((int)newA.size() + 1);
				if (value % prime == 0) break;
			}
			newA.push_back(value);
		}
		// // for (int x: newA) cerr << x << ' '; cerr << '\n';
		cout << ans << '\n';
	}
}