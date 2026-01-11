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

#define MAX 1000001
#define MOD 1000000007

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

ll power(ll a, ll b) {
    ll ans = 1;
    FOR(int, i, 1, b) ans *= a;
    return ans;
}

#define BIT 20
const int ALL = (1 << BIT) - 1;
ll n, k;
int a[MAX];
ll cnt[1 << BIT];
ll dp[BIT + 1][1 << BIT];

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    FOR(int, i, 1, n) {cin >> a[i]; cnt[a[i]]++;}
    REV(int, revMask, ALL, 0) {
        int mask = ALL & (~revMask);
        dp[0][mask] = cnt[revMask];
        for (int i = 0, nxt = 1; nxt <= BIT; i++, nxt++) {
            dp[nxt][mask] = dp[nxt - 1][mask];
            if (testBit(mask, i) == true)
                dp[nxt][mask] += dp[i][flipBit(mask, i)];
        }
        cnt[revMask] = dp[BIT][mask];
    }

    ll total = 0;
    FOR(int, mask, 0, ALL) {
        total += ((cntBit(mask) % 2 == 0) ? 1 : -1) * power(cnt[mask], 4);
    }
    if (k > total) {cout << "-1\n"; return 0;}

    int CURRENT_MASK = ALL;
    REV(int, pwr, 4, 1) {
        memset(dp, false, sizeof(dp));
        FOR(int, mask, 0, ALL) 
            dp[0][ALL & (~mask)] = power(cnt[mask], pwr - 1) * ((cntBit(mask) % 2 == 0) ? 1 : -1);
        for (int i = 0, nxt = 1; nxt <= BIT; i++, nxt++) 
        FOR(int, mask, 0, ALL){
            dp[nxt][mask] = dp[i][mask];
            if (testBit(mask, i) == true)
                dp[nxt][mask] += dp[i][flipBit(mask, i)];
        }
        FOR(int, mask, 0, ALL) 
            dp[0][mask] = abs(dp[BIT][ALL & (~mask)]);
        for (int i = 0, nxt = 1; nxt <= BIT; i++, nxt++) {
            memset(dp[nxt], false, sizeof(dp[nxt]));
            FOR(int, mask, 0, ALL){
                dp[nxt][mask] = dp[i][mask];
                if (testBit(mask, i) == true)
                    dp[nxt][mask] += dp[i][flipBit(mask, i)];
            }
        }
        ll *calculation = dp[BIT];

        FOR(int, i, 1, n)  {
            ll tmp = calculation[ALL & ~(CURRENT_MASK & a[i])];
            if (tmp < k) k -= tmp;
            else {
                CURRENT_MASK &= a[i];
                cout << i << ' ';
                break;
            }
        }
    }
}