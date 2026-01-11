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

#define MAX_N 100
#define MAX_VAL 70
#define MOD 1000000007

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n, a[MAX_N + 1];
ll f[MAX_N + 1][MAX_VAL + 1];


main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    FOR(int, _, 1, t){
        memset(f, false, sizeof(f));
        cin >> n; FOR(int, i, 1, n) cin >> a[i];

        f[0][0] = 1;
        for (int i = 0, nxt = 1; nxt <= n; i++, nxt++){
            FOR(int, val, 0, MAX_VAL){
                f[i][val] %= MOD;
                f[nxt][val] += f[i][val];
                f[nxt][__gcd(val, a[nxt])] += f[i][val];
            }
            // cerr << '\n';
            // FOR(int, val, 0, 5) cerr << f[nxt][val] << " \n"[val == 5];
        }

        int answer = 0;
        FOR(int, val, 0, MAX_VAL)
            answer += 1ll * val * f[n][val] % MOD,
            answer %= MOD;
        
        cout << answer << '\n';
    }
}