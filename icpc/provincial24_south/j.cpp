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

#define MAX 100005
#define MODMOD 1000000007

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

randomize;
const ll MOD[2] = {int(1e9+2277), int(1e9+5277)};

struct Hash{
    int m[2] = {};
    Hash(){m[0] = m[1] = 0;}
    Hash(int m0, int m1){m[0] = m0 % MOD[0]; m[1] = m1 % MOD[1];}
    Hash(int x){m[0] = x % MOD[0]; m[1] = x % MOD[1];}
};
Hash operator + (Hash a, Hash b) {
    FOR(int, i, 0, 1)
        a.m[i] = (a.m[i] + b.m[i]) % MOD[i];
    return a;
}
Hash operator - (Hash a, Hash b) {
    FOR(int, i, 0, 1)
        a.m[i] = (a.m[i] + MOD[i] - b.m[i]) % MOD[i];
    return a;
}
Hash operator * (Hash a, Hash b) {
    FOR(int, i, 0, 1)
        a.m[i] = (1ll * a.m[i] * b.m[i]) % MOD[i];
    return a;
}
bool operator < (Hash a, Hash b) {
    FOR(int, i, 0, 1)
        if (a.m[i] != b.m[i]) return a.m[i] < b.m[i];
    return false;
}
bool operator == (Hash a, Hash b) {
    FOR(int, i, 0, 1)
        if (a.m[i] != b.m[i]) return false;
    return true;
}

int n;
char s[MAX];
int diff;
map<char, int> m;

Hash BASE[MAX];
void createBase(int diff) {
    FOR(int, pos, 1, diff - 1){
        FOR(int, i, 0, 1)
            while (BASE[pos].m[i] < 10000000)
                BASE[pos].m[i] = mt() % MOD[i];
        BASE[diff] = BASE[diff] - BASE[pos];
    }
}
Hash values[MAX];
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> (s + 1);
    FOR(int, i, 1, n) {
        if (m[s[i]] == 0) {
            m[s[i]] = ++diff;
        }
    }
    createBase(diff);

    FOR(int, i, 1, n) {
        values[i] = values[i - 1] + BASE[m[s[i]]];
    }
    sort(values, values + 1 + n);
    // FOR(int, i, 0, n) cerr << values[i].m[0] << ' ' << values[i].m[1] << '\n';
    ll answer = 0, consec = 1;
    FOR(int, i, 1, n)
        if (values[i] == values[i - 1]) {
            answer += consec;
            consec++;
        } else {
            consec = 1;
        }
    cout << answer % MODMOD;
}