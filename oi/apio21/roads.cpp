#include "roads.h"
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

// /*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
// */

#define MAX 100005
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

bool flag1 = true, flag2 = true, flag5 = true, flag6 = true;

int n;
vg graph[MAX];
vector<ll> wg;
#pragma region sub2
ll f2[MAX][2];
ll sub2(){
	FOR(int, i, 1, n - 1){
		f2[i][1] = f2[i - 1][0];
		f2[i][0] = min(f2[i - 1][0], f2[i - 1][1]) + wg[i];
	}
	return min(f2[n - 1][0], f2[n - 1][1]);
}
#pragma endregion

#pragma region sub34
ll sumAll = 0;
ll f[2003][2][2003];
void dp(int node, int parent){
	for (Node child: graph[node])
		if (child.node != parent)
			dp(child.node, node);
	FOR(int, k, 1, n - 1){
		ll &ans0 = f[node][0][k], &ans1 = f[node][1][k];
		ll cur = 0;
		vl tmp;
		for (Node child: graph[node]){
			if (child.node == parent) continue;
			cur += f[child.node][0][k];
			tmp.push_back((f[child.node][1][k] + child.len) - f[child.node][0][k]);
		}
		ans0 = ans1 = cur;

		sort(tmp.begin(), tmp.end(), greater<ll>());
		ll k0 = min(k, (int)tmp.size());
		ll k1 = min(k - 1, (int)tmp.size());
		FOR(int, i, 0, k0 - 1)
			if (tmp[i] > 0) ans0 += tmp[i];
		FOR(int, i, 0, k1 - 1)
			if (tmp[i] > 0) ans1 += tmp[i];
	}
}
#pragma endregion

std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
											 std::vector<int> V,
											 std::vector<int> W) {
	n = N; wg = vl(n, 0);
	FOR(int, i, 0, n - 2){
		int u = U[i], v = V[i], w = W[i];
		flag1 &= u == 0; flag2 &= u == i && v == i + 1;
		flag5 &= w == 1; flag6 &= w <= 10;

		u++, v++; sumAll += w;
		wg[i + 1] = w;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}

	if (flag1){
		vl ans(n - 1);
		FOR(int, i, 0, n - 2)
			ans[i] = W[i];
		sort(ans.begin(), ans.end(), greater<ll>());

		ans.push_back(0);
		FORR(int, i, n - 2, 0)
			ans[i] += ans[i + 1];
		return ans;
	}
	else if (flag2){
		vl ans(n, 0);
		FOR(int, i, 1, n - 1) ans[0] += wg[i];
		ans[1] = sub2();
		return ans;
	}
	else if (n <= 2000){
		dp(1, 0);
		vl ans(n);
		FOR(int, i, 0, n - 1) ans[i] = sumAll - f[1][0][i];
		return ans;
	}
	else if (flag5){
		assert(false);
	}
	else if (flag6){
		assert(false);
		//
	}
	else {
		assert(false);
		//
		return std::vector<long long>(N, 0);
	}

}
