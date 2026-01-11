#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 1000005
#define MOD 1'000'000'007

ll n, q;
list<pll> historyBuy[MAX];

ll sumDividends[MAX];
ll saving[MAX];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	FOR(ll, curTi, 1, q) {
		ll type; cin >> type; 

		if (type == 2) {
			cin >> sumDividends[curTi]; 
			sumDividends[curTi] += sumDividends[curTi - 1];
			continue;
		}
		sumDividends[curTi] += sumDividends[curTi - 1];
		// FOR(int, i, 1, curTi) cerr << sumDividends[i] << " \n"[i == curTi];

		if (type == 1) {
			ll p, x; cin >> p >> x;
			if (x > 0) {
				historyBuy[p].push_back(pll(curTi, x));
			} else if (x < 0) {
				x = -x;
				while (x > 0) {
					auto [time, count] = *historyBuy[p].rbegin(); historyBuy[p].pop_back();

					ll totalD = (sumDividends[curTi] - sumDividends[time]) % MOD;
					ll del = min(x, count) ;
					saving[p] += totalD * del % MOD, 
					saving[p] %= MOD;
					// cerr << p << ' ' << del << ' ' << totalD << " => " << saving[p] << '\n';

					x -= del; count -= del;
					assert(x >= 0), assert(count >= 0);
					if (count > 0)
						historyBuy[p].push_back(pll(time, count));
				}
			}
		} else {
			assert(type == 3);

			ll p; cin >> p;
			ll totalCount = 0;
			for (auto [time, count]: historyBuy[p]) {
				ll totalD = (sumDividends[curTi] - sumDividends[time]) % MOD;
				saving[p] += totalD * (count % MOD) % MOD; 
				saving[p] %= MOD;
				// cerr << "pop " << time << ' ' << count << '|' << totalD << ' ' << totalD * count % MOD << '\n';
				totalCount += count;
			}
			historyBuy[p].clear();
			if (totalCount > 0)
				historyBuy[p].push_back(pll(curTi, totalCount));
			
			// assert(saving[p] >= 0);
			// assert(saving[p] < MOD);
			cout << saving[p] << '\n';
			saving[p] = 0;
		}
	}
}