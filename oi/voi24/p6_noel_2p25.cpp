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
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

struct Query{
    ll l, r, x, y;
};

int m, q;
int c[MAX];
Query queries[MAX];

int lastR[MAX];
namespace PreProcess {
    int dpp[MAX];

    void preprocess() {
        int r = m;
        FORD(int, l, m, 1) {
            dpp[c[l]]++;
            while (dpp[c[l]] >= 2)
                --dpp[c[r--]];
            lastR[l] = r;
        }
    }
}

namespace sub2 {
    bool check() {
        FOR(int, i, 1, q)
            if (queries[i].x != 1 || queries[i].y != 1)
                return false;
        return true;
    }

    #define BIT 17
    int rmq[BIT + 1][MAX];
    void buildRMQ() {
        FOR(int, i, 1, m) rmq[0][i] = lastR[i] + 1; // jump to next segment
        FOR(int, bit, 1, BIT) FOR(int, i, 1, m)
            rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
    }
    int cal(int start, int limit) {
        int answer = 0;
        FORD(int, bit, BIT, 0) {
            int next = rmq[bit][start];
            if (next == 0 || next > limit) continue;
            start = next; answer |= 1 << bit;
        }
        return answer + 1; // including the first segment
    }
    void solve() {
        buildRMQ();
        FOR(int, i, 1, q) {
            int l = queries[i].l, r = queries[i].r;
            cout << cal(l, r) << '\n';
        }
    }
}

namespace sub1 {
    bool check() {
        return m <= 12 and q <= 1024;
    }
    
    bool operator > (const vector<int> &a, const vector<int> &b) {
        const int lenA = a.size(), lenB = b.size();
        for (int i = 0; i < lenA && i < lenB; i++)
            if (a[i] != b[i]) return a[i] > b[i];
        return lenA > lenB;
    }
    vector<vector<int>> allConfigs;
    vector<int> currentConfig;
    void dqql(int pos, int limit, int start) {
        if (pos > limit) {
            currentConfig.push_back(pos - start);
            allConfigs.push_back(currentConfig);
            currentConfig.pop_back();
            return;
        }
        // case 1
        if (pos <= lastR[start]) {
            dqql(pos + 1, limit, start);
        }
        // case 2
        currentConfig.push_back(pos - start),
        dqql(pos + 1, limit, pos);
        currentConfig.pop_back();
    }
    int solveQuery(int l, int r, int x, int y) {
        allConfigs.clear();
        dqql(l, r, l);
        sort(allConfigs.begin(), allConfigs.end(), greater<vector<int>>());
        vector<int> configX = allConfigs[x - 1],
                    configY = allConfigs[y - 1];
        int answer = 0;
        for (int i = 0; i < configX.size() && i < configY.size(); i++)
            if (configX[i] == configY[i]) answer++;
            else break;
        return answer;
    }
    void solve() {
        FOR(int, i, 1, q) {
            int l = queries[i].l,
                r = queries[i].r,
                x = queries[i].x,
                y = queries[i].y;
            cout << solveQuery(l, r, x, y) << '\n';
        }
    }
}

void input();
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifndef HIEU
    freopen("noel.inp", "r", stdin);
    freopen("noel.out", "w", stdout);
    #endif

    input();
    PreProcess::preprocess();
    if (sub1::check()) return sub1::solve(), 0;
    if (sub2::check()) return sub2::solve(), 0;
}
void input() {
    cin >> m >> q;
    FOR(int, i,1 , m) cin >> c[i];
    FOR(int, i, 1, q) {
        ll l, r, x, y; cin >> l >> r >> x >> y;
        queries[i] = {l, r, x, y};
    }
}