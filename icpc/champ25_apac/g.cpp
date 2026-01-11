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
#define NO cout << "no" << '\n'
#define YES cout << "yes" << '\n'

int n, m;
string B, C;



main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t) {
		cin >> n >> m >> B >> C; B = " " + B, C = " " + C;

		int lB = 1, lC = 1, rB = n, rC = m;
		if (C[1] == '1') {
			int oneB = 0, oneC = 0;
			while (lB <= n and B[lB] == '1') oneB++, lB++;
			while (lC <= m and C[lC] == '1') oneC++, lC++;
			// cerr << oneB << ' ' << oneC << '\n';
			if (oneB < oneC) {NO; continue;}
		}
		if (lB > n or lC > m) {
			if (lB > n and lC > m) YES; else NO; 
			continue;
		}
		
		// at this point, defintely exists 0
		if (C[m] == '1') {
			int oneB = 0, oneC = 0;
			while (rB >= 1 and B[rB] == '1') oneB++, rB--;
			while (rC >= 1 and C[rC] == '1') oneC++, rC--;
			cerr << oneB << '.' << oneC << '\n';
			if (oneB < oneC) {NO; continue;}
		}
		if (lB > n or lC > m) {
			if (lB > n and lC > m) YES; else NO; 
			continue;
		}
		// assert(lB <= rB); assert(lC <= rC);

		// check match
		int ptr = lC; bool justMatched = false;
		for (int i = lB; i <= rB and ptr <= rC; i++) {
			// cerr << i << ' ' << ptr << ' ' << justMatched << '\n';
			if (justMatched and C[ptr - 1] == '1' and C[ptr] == '1') {
				if (B[i] != '1') {
					while (C[ptr-1] == '1') ptr--;
					justMatched = false;
					continue;
				}
			}
			if (B[i] == C[ptr])
				ptr++, justMatched = true;
			else
				justMatched = false;
		}
			// ptr += B[i] == C[ptr];
		if (ptr > rC) YES; else NO;
		// cerr << '\n'
	}
}