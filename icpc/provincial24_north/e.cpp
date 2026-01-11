#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/*
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef unsigned long long ull;
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
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

#pragma GCC target ("avx2")
#pragma GCC optimization ("unroll-loops")

#define MAX 100005
#define SQRT 320
struct Query{int l, r, i;};
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
inline bool cmp(Query a, Query b) {
    // return hilbertOrder(a.l, a.r, 17, 0) < hilbertOrder(b.l, b.r, 17, 0);
    a.l /= SQRT, b.l /= SQRT;
    return (a.l != b.l) ? (a.l < b.l) : (
        (a.l % 2 == 1) ? (a.r > b.r) : (a.r < b.r)
    );
}

int MOD;
int n, q; 
string s;
ll sum[MAX];
Query queries[MAX];

ll f[MAX];
void p25(bitset<10> eligibleDigits){
    FOR(int, i, 1, n) {
        if (eligibleDigits[s[i]])
            f[i] = n + 1 - i, sum[i] = 1;
        f[i] += f[i - 1]; sum[i] += sum[i - 1];
    }
    FOR(int, _, 1, q) {
        int l = queries[_].l, r = queries[_].r;
        ll answer = f[r] - f[l - 1] - (n - r) * (sum[r] - sum[l - 1]);
        cout << answer << '\n';
    }
}

// unordered_map<int, int> _cnt;
struct chash{
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator() (ll x) const {return __builtin_bswap64(x*C);}
};
gp_hash_table<ll, int, chash> _cnt({}, {}, {}, {}, {1 <<16});
struct Calculate{
    ll answer = 0;
    Calculate() {
        answer = 0;
    }
    void add(int number) {
        answer += _cnt[number]++;
    }
    void del(int number) {
        answer -= --_cnt[number];
    }
} calculate;

struct FastMod{
    ull b, m;
    FastMod() {}
    FastMod(ull b): b(b), m(-1ULL/b){}
    inline ull reduce(ull a){
        ull tmp = a - (ull)((__uint128_t(m) * a) >> 64) * b;
        return tmp - b * (tmp >= b);
    }
} fast;

ll answer[MAX];

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> MOD >> s >> q;
    fast = FastMod(MOD);
    
    reverse(s.begin(), s.end());
    n = s.length(); 
    s = " " + s;
    FOR(int, i, 1, n) s[i] -= '0';

    FOR(int, i, 1, q) {
        int l, r; cin >> l >> r;
        l = n + 1 - l; r = n + 1 - r;
        swap(l, r);
        queries[i] = {l, r, i};
    }

    if (MOD == 2) { p25(0b0101010101); return 0; } 
    if (MOD == 5) { p25(0b0000100001); return 0; }

    for (ll i = 1, p10 = 1; i <= n; i++, p10 = fast.reduce(p10 * 10)){
        sum[i] = fast.reduce(sum[i - 1] + p10 * s[i]);
    }
    FOR(int, i, 1, q) queries[i].l--;
    sort(queries + 1, queries + 1 + q, cmp);
    // FOR(int, i, 1, q) cerr << queries[i].l << ' ' << queries[i].r << "|\n"[i == q];
    
    int l = queries[1].l, r = queries[1].r;
    FOR(int, i, l, r) calculate.add(sum[i]);
    answer[queries[1].i] = calculate.answer;

    FOR(int, _, 2, q) {
        const int newL = queries[_].l, newR = queries[_].r, newI = queries[_].i;
        while (newL < l) calculate.add(sum[--l]);
        while (newR > r) calculate.add(sum[++r]);
        while (l < newL) calculate.del(sum[l++]);
        while (r > newR) calculate.del(sum[r--]);
        answer[newI] = calculate.answer;
    }
    
    FOR(int, i, 1, q) cout << answer[i] << '\n';
}