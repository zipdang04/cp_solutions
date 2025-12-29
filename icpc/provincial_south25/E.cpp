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

#define MAX 2000001
#define MOD 1000000007


const vector<int> PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

int n;
int a[MAX];

inline bool check(int num1, int num2) {
	return num1 % num2 == 0
		or num2 % num1 == 0
		or __gcd(num1, num2) == 1;
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		int ptr = 1;
		int answer = 0;
		int add = 0;
		while (ptr < n) {
			if (check(a[ptr], a[ptr + 1])) {
				ptr += 2; answer++;
				continue;
			}
			ptr += 2; answer += 2; 
			add++; 
			// else
			// bool oke = false;
			// for (int p: PRIMES) {
			// 	int newA1 = a[ptr] + p;
			// 	bool oke1 = check(newA1, a[ptr + 1]);
			// 	bool oke2 = check(a[n], p);
			// 	if (oke1 and oke2) {
			// 		a[ptr] += p; a[++n] = p;
			// 		answer++;
			// 		oke = true; break;
			// 	}
			// }
			// assert(oke);
			// cerr << ptr << '/'; FOR(int, i, 1, n) cerr << a[i] << " \n"[i == n];
		}
		if (ptr == n) add++;
		answer += add / 2;
		if (add % 2) answer += 2;

		// if (ptr == n) answer += 2;
		cout << answer << '\n';
	}
}
void input() {
	cin >> n;
	FOR(int, i, 1, n) cin >> a[i];
}