#include "hexagon.h"

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
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;

template<class T>
void minimize(T &a, T b){
	if (b < a) a = b;
}
template<class T>
void maximize(T &a, T b){
	if (b > a) a = b;
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

#define MAX 4003
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const pll direc[6] = {{1, 0}, {1, 1}, {0, 1}, {-1, 0}, {-1, -1}, {0, -1}};
pll operator + (pll a, pll b){return {a.fi + b.fi, a.se + b.se};}

ll sub1(ll n){
	return (n * (n + 1) / 2) % MOD;
}
ll sub2(ll n){
	ll n1 = n + 1, n2 = n + 2;
	if (n % 3 == 0) n /= 3;
	else if (n1 % 3 == 0) n1 /= 3;
	else n2 /= 3;
	n *= n1, n %= MOD;
	n *= n2, n %= MOD;
	return n;
}

int inside[MAX][MAX];
#define get(arr, x, y) arr[x + 2000][y + 2000]

void bfs(){
	const int NaN = -1;
	pll pos = {-2000, -2000};
	queue<pll> q;

	get(inside, pos.fi, pos.se) = NaN; q.push(pos);
	while (!q.empty()){
		pll pos = q.front(); q.pop();
		for (pll d: direc){
			pll nxt = pos + d;
			if (nxt.fi < -2000 || nxt.fi > 2000) continue;
			if (nxt.se < -2000 || nxt.se > 2000) continue;
			if (get(inside, nxt.fi, nxt.se)) continue;
			get(inside, nxt.fi, nxt.se) = NaN; q.push(nxt);
		}
	}

}

void bfs2(){
	queue<pll> q;

	get(inside, 0, 0) = 1; q.push({0, 0});
	while (!q.empty())
	{
		pll pos = q.front(); q.pop();
		int dist = get(inside, pos.fi, pos.se);
		for (pll d: direc){
			pll nxt = pos + d;
			if (get(inside, nxt.fi, nxt.se)) continue;
			get(inside, nxt.fi, nxt.se) = dist + 1; q.push(nxt);
		}
	}

	//
}

vector<int> d, l;
void getPoint(){

}

int draw_territory(int N, int A, int B,
				   std::vector<int> D, std::vector<int> L) {
	FOR(int, i, 0, N - 1) D[i]--;
	d = D, l = L;

	if (N == 3){
		N = L[0];
		return ((sub1(N + 1) * A % MOD) + (sub2(N) * B % MOD)) % MOD;
	}
	ll total = 0; for (int num: L) total += num;
	if (total <= 2000){
		get(inside, 0, 0) = 1;
		pll pos = {0, 0};
		FOR(int, _, 0, N - 1){
			pll di = direc[D[_]]; int cnt = L[_];
			FOR(int, i, 1, cnt){
				pos = pos + di;
				get(inside, pos.fi, pos.se) = 1;
			}
		}
		bfs();
		FOR(int, i, -2000, 2000)
		FOR(int, j, -2000, 2000)
			if (get(inside, i, j) == 1) get(inside, i, j) = 0;
		bfs2();
		ll ans = 0;
		FOR(int, i, -2000, 2000)
		FOR(int, j, -2000, 2000)
			if (get(inside, i, j) != -1)
				ans += (A + 1ll * B * (get(inside, i, j) - 1) % MOD) % MOD,
				ans %= MOD;
		return ans;
	}

	return 0;
}
