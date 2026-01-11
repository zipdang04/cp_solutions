#include "rotate.h"
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
#define randomize mt19937_64 mt(1234)

randomize;
struct random{
    static int next(ll n) {return mt() % n;}
    static int next(ll l, ll r) {return l + next(r-l+1);}
};
#define MOD 50000

int n;
vector<pair<int, int>> v;


namespace Subtask1 {
    void solve() {
        int need = v[0].fi - (MOD / 2);
        int add = need + MOD - v[1].fi;
        rotate({1}, add);
    }
}
namespace Subtask2 {
    void solve() {
        for (int i = 0; i < n; i++)
            if (i < n / 2)
                rotate({v[i].se}, MOD - v[i].fi);
            else 
                rotate({v[i].se}, MOD * 3 / 2 - v[i].fi);
    }
}
namespace Subtask3 {
    vector<bool> visited;
    inline int cal(int a, int b) {
        a %= MOD, b %= MOD; 
        int tmp = (a + MOD - b) % MOD;
        return min(tmp, MOD - tmp);
    }
    ll test(int pos, int value) {
        ll ans = 0;
        FOR(int, i, 0, n-1) FOR(int, j, i + 1, n-1)
            ans += cal(
                i != pos ? v[i].fi : value,
                j != pos ? v[j].fi : value
            );
        return ans;
    }
    void solve() {
        visited.resize(n, false);
        ll original = test(0, v[0].fi);
        // cerr << "|" << original << ' ' << n << '\n';
        FOR(int, _, 1, n) {
            // cerr << _ << endl;
            const int GOAL = (_ % 2) * (MOD / 2);
            bool done = false;
            while (not done) {
                for (int i = 0; i < n; i++) if (not visited[i]) {
                    ll tmp = test(i, GOAL);
                    ll need = GOAL + MOD - v[i].fi;
                    
                    if (tmp >= original) {
                        original = tmp;
                        rotate({v[i].se}, need);
                        v[i].fi = GOAL; 
                        visited[i] = true;
                        done = true;
                        break;
                    }
                }
                if (not done) {
                    vector<int> notdone, change;
                    FOR(int, i, 0, n-1) 
                        if (not visited[i]) 
                            change.push_back(i),
                            notdone.push_back(v[i].se);
                    int add = 1234;
                    rotate(notdone, add);
                    for (int i: change) 
                        v[i].fi = (v[i].fi + add) % MOD;
                    original = test(0, v[0].fi);
                }
            }
        }
    }
}
namespace WTF {
    void solve() {
        int tmp = n / 2;
        for (int i = 0; i < tmp; i++)
            rotate({v[i].se}, (v[i + tmp].fi + (MOD / 2) + MOD - v[i].fi) % MOD);
    }
}

void energy(int _n, std::vector<int> _v){
    n = _n; v.resize(n);
    FOR(int, i, 0, n) v[i] = {_v[i], i};
    sort(v.begin(), v.end());
    REV(int, i, n-1, 0) v[i].fi -= v[0].fi;

    // if (n == 2) {
    //     Subtask1::solve();
    //     return;
    // }
    // Subtask2::solve();
    WTF::solve();
}