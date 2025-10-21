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

randomize;

int pos[MAX];

void haha(int *arr, const int n, int l, int next) {
	if (n-l <= 3) return;
	// int pivot = (arr[l] + arr[l+1] + arr[l+2]) / 3;
	// int next = upper_bound(arr+l, arr+n, pivot) - arr;
	// haha(arr, n, next);
	// cerr << l << ' ' << n << ' ' << pivot << ' ' << next << '\n';
	
	int l1 = l+1, l2 = l+2;
	int pos1 = pos[l1], pos2 = pos[l2];
	if (pos1 > pos2) swap(pos1, pos2), swap(l1, l2);
	int val1 = arr[n-1], val2 = arr[(l+n-1)/2];
	// cerr << l << ' ' << next << '/' << l1 << ' ' << l2 << ' ' << pos1 << ' ' << pos2 << ' ' << val1 << ' ' << val2 << ' ' << n-1 << ' ' << (l+n-1)/2 << '\n';
	swap(arr[pos1], arr[n-1]); swap(pos[l1], pos[val1]);
	swap(arr[pos2], arr[(l+n-1)/2]); swap(pos[l2], pos[val2]);
}

int n;
int a[MAX];
int arr[MAX];
vector<int> ohno;
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; 
	FOR(int, i, 0, n-1) cin >> a[i];
	FOR(int, i, 0, n-1) arr[i] = pos[i] = i;
	sort(a, a + n);
	// FOR(int, i, 0, n-1) {
	// 	int l = mt() % n;
	// 	int r = mt() % n;
	// 	swap(arr[l], arr[r]);
	// }
	int l = 0;
	while (l+2 < n) {
		ohno.push_back(l);
		int pivot = (1ll*arr[l] + 1ll*arr[l+1] + 1ll*arr[l+2]) / 3;
		l = upper_bound(arr+l, arr+n, pivot) - arr;
	}
	for (auto it = ohno.rbegin() + 1; it < ohno.rend(); it++) {
		haha(arr, n, *it, *(it-1));
		// // FOR(int, i, 0, n-1) cerr << pos[i] << ' '; cerr << '\n';
		// unordered_set<int> hihi;
		// FOR(int, i, 0, n-1) hihi.insert(pos[i]);
		// assert(hihi.size() == n);
	}
	FOR(int, i, 0, n-1) cout << a[arr[i]] << ' ';
}