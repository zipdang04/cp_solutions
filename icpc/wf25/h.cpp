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

ll m, n;
int p[MAX], g = 0;
int THRESHOLD;

bitset<(int)5e6> f;
void build() {
	f[0] = true; int consec = 1;
	int ptr = 0;
	while (consec < THRESHOLD) {
		ptr++;
		FOR(int, i, 1, n) if (p[i] <= ptr) if (f[ptr - p[i]]) f[ptr] = true;
		if (f[ptr]) consec++; else consec = 0;
	}
	THRESHOLD = ptr;
}

#define MAX_LEN 18
ll p10[MAX_LEN + 1], mod10[MAX_LEN + 1];
int dp[9][MAX_LEN + 1][1001] = {};
void buildDP() {
	memset(dp, -0x3f, sizeof(dp));
	p10[0] = mod10[0] = 1;
	FOR(int, i, 1, MAX_LEN)
	FOR(int, i, 1, MAX_LEN)
		p10[i] = p10[i-1] * 10,
		mod10[i] = mod10[i-1] * 10 % g;
	
	FOR(int, D, 0, 8) {
		FOR(int, _d, 0, 9) {
			int d = _d == 9 ? 6 : _d;
			maximize(dp[D][0][_d % g], (d == D));
		}
		for (int i = 0, nxt = 1; nxt <= MAX_LEN; i++, nxt++) FOR(int, mod, 0, g-1) 
		if (dp[D][i][mod] >= 0){
			FOR(int, _d, 0, 9) {
				int d = _d == 9 ? 6 : _d;
				int newVal = dp[D][i][mod] + (d == D);
				int newMod = (mod + _d * mod10[nxt]) % g; // d * 10^nxt + past
				maximize(dp[D][nxt][newMod], newVal);
			}
		}
	}

	// FOR(int, D, 0, 8) {
	// 	FOR(int, len, 0, MAX_LEN) FOR(int, mod, 0, g-1)
	// 		cerr << dp[D][len][mod] << " \n"[mod == g-1];
	// 	cerr << '\n';
	// }
	// cerr << '\n';
}

int need[9] = {1};
int digits[MAX_LEN + 1];
inline int updateSingle(ll number) { // return length
	short tmp[9] = {}; int length = 0;
	while (number > 0) {
		int c = number % 10; number /= 10;
		if (c == 9) c = 6;
		tmp[c]++; length++;
	}
	FOR(int, d, 0, 8) maximize(need[d], tmp[d]);
	return length;
}
void buildDigits() {
	ll number = m;
	FOR(int, i, 0, MAX_LEN) digits[i] = number % 10, number /= 10;
}
void process() {
	// cerr << THRESHOLD << '\n';
	// stage 1: 0 -> THRESHOLD
	FOR(int, i, 1, THRESHOLD) if (f[i]) {
		ll number = 1ll * i * g;
		if (number > m) return;
		updateSingle(number);
	}
	// cerr << "stage1done" << endl;
	// stage 2: THRESHOLD + 1 -> samesize;
	ll start = THRESHOLD * g; int length = max(4, updateSingle(start));
	while (true) {
		start += g; if (start > m) return;
		int numLength = updateSingle(start);
		if (numLength > length) {length = numLength; break;}
	}
	// cerr << start << '\n';

	// cerr << "stage2done" << endl;
	// stage 3: size+1 -> mLength (-1)
	int mLength = updateSingle(m);
	// cerr << m << ' ' << mLength << '\n';
	while (length < mLength) {
		FOR(int, firstDigit, 1, 9) {
			int tmp[9] = {}; 
			int remainMod = (g - firstDigit * mod10[length-1] % g) % g;
			// cerr << length << ' ' << firstDigit << ' ' << remainMod << '\n';
			// FOR(int, d, 0, 8) cerr << tmp[d] << " \n"[d == 8];
			bool oke = true;
			FOR(int, d, 0, 8) {
				const int& value = dp[d][length - 2][remainMod];
				if (value < 0) {oke = false; break;}
				tmp[d] += value;
			}
			if (not oke) continue;
			// FOR(int, d, 0, 8) cerr << tmp[d] << " \n"[d == 8];
			tmp[firstDigit == 9 ? 6 : firstDigit]++;
			FOR(int, d, 0, 8)
				maximize(need[d], tmp[d]);
		}
		length++;
	}
	assert(length == mLength);
	// cerr << "stage3done" << endl;
	// FOR(int, i, 0, 8) cerr << need[i] << " \n"[i == 8];

	// stage 4: 10^(mLength-1)
	buildDigits();
	int sumPrv = 0;
	vector<int> tmp(9, 0);
	REV(int, pos, length-1, 0) {
		int beg = (pos == length-1);
		int end = digits[pos] - 1;
		// cerr << pos << ' ' << beg << ' ' << end << '\n';
		FOR(int, d, beg, end) {
			int curMod = sumPrv + d * mod10[pos] % g;
			int remainMod = (g - curMod % g) % g;
			// cerr << "-> d " << curMod << ' ' << remainMod << '|';
			vector<int> cur = tmp; cur[d == 9 ? 6 : d]++;
			bool oke = true;
			if (pos > 0) 
				FOR(int, d2, 0, 8) {
					const int &value = dp[d2][pos-1][remainMod];
					if (value < 0) {oke = false; break;}
					cur[d2] += value;
				}
			else if (remainMod > 0) continue;
			if (not oke) continue;
			
			// FOR(int, d2, 0, 8) cerr << cur[d2] << " \n"[d2 == 8];
			FOR(int, d2, 0, 8) maximize(need[d2], cur[d2]);
		}

		int d = digits[pos];
		tmp[d == 9 ? 6 : d]++; sumPrv = sumPrv + d * mod10[pos]; sumPrv %= g;
		// FOR(int, i, 0, 8) cerr << tmp[i] << " \n"[i == 8];
	}
}
// TODO: check m < g

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	// cerr << "input" << endl;
	build(); 
	// cerr << "build" << endl;
	buildDP();
	// cerr << "buildDP" << endl;
	process();

	FOR(int, i, 0, 8)  if (need[i]) cout << i << ' ' << need[i] << '\n';
}
void input() {
	cin >> m >> n;
	updateSingle(m);
	FOR(int, i, 1, n) cin >> p[i];
	FOR(int, i, 1, n) g = __gcd(p[i], g);
	FOR(int, i, 1, n) p[i] /= g; m = (m / g) * g; updateSingle(m);
	sort(p + 1, p + 1 + n); THRESHOLD = p[n];
}