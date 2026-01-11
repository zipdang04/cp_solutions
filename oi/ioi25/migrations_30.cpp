#include "migrations.h"

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

#define MAX 10'005
#define BIT 14
#define MOD 1000000007

int n, p[MAX];

namespace Research {
    int lvl[MAX + 1] = {};
    struct LCA {
        int rmq[BIT + 1][MAX + 1] = {};
        void build(int node) {
            rmq[0][node] = p[node];
            FOR(int, bit, 1, BIT)
                rmq[bit][node] = rmq[bit-1][rmq[bit-1][node]];
        }

        int jump(int u, int dist) {
            for (int bit = 0; dist > 0; bit++, dist >>= 1)
                if (dist & 1)
                    u = rmq[bit][u];
            return u;
        }
        int getLCA(int u, int v) {
            if (lvl[u] > lvl[v]) swap(u, v);
            v = jump(v, lvl[v] - lvl[u]);
            if (u == v) return u;

            FOR(int, bit, 1, BIT)
                if (rmq[bit][u] != rmq[bit][v])
                    u = rmq[bit][u], v = rmq[bit][v];
            return p[u];
        }
        int calDist(int u, int v) {
            int p = getLCA(u, v);
            return lvl[u] + lvl[v] - lvl[p] * 2;
        }
    } lca;

    int one = 0, two = 1, dist = 1;
    int addNode(int node, int parent) {
        p[node] = parent; lvl[node] = lvl[parent] + 1;
        lca.build(node);
        if (node <= 1) return 0;

        // either one or two

        if (lvl[node] > lvl[two]) {
            two = node; return true;
        }
        return false;
    }

    #define START 9981
    int oldOne, oldTwo;
    bool still = false;
    int calMessage(int turn, int state) {
        if (turn < START) return 0;

        if (turn == START) {
            oldOne = one, oldTwo = two;
        }
        if (START <= turn and turn <= START + 5) {
            int num = oldTwo;
            REV(int, i, START+4, turn) num /= 5;
            num %= 5;
            return num;
        }

        if (turn == START + 6) {
            if (oldTwo == two) return 0;
            if (two - START + 1 <= 3) return two - START + 1;
            still = true; return 4;
        }

        if (still and turn == START + 7) {
            return two - (START + 3);
        }

        return state;
    }
}
int send_message(int N, int i, int Pi) {
    int state = Research::addNode(i, Pi);
    if (i == 1) { n = N; return 0; }
    int message = Research::calMessage(i, state);
    // if (i >= START) cerr << i << ' ' << message << '\n';
    return message;
}

namespace Museum {
    int one = 0, two = 0, still = 0;
    void build(int turn, int message) {
        // cerr << turn << ' ' << message << '\n';
        if (turn < START) return;
        switch (turn) {
            case START:
            case START + 1:
            case START + 2:
            case START + 3:
            case START + 4:
            case START + 5:
                two = two * 5 + message;
                return;
            case START + 6: {
                // cerr << "START + 4 " <<  bitset<6>(message) << '\n';
                if (message == 0) return;
                if (message <= 3) {
                    two = START + message - 1; return;
                }
                still = true;
            } return;
            case START + 7: {
                if (still) {two = START + 3 + message; return;}
                if (message == 0);
                else two = turn;
            }
            default:
                if (message == 0);
                else two = turn;
        }
    }
}

std::pair<int, int> longest_path(std::vector<int> S) {
    n = 1 + (int) S.size();
    FOR(int, i, 1, n-1)
        Museum::build(i, S[i]);
    return {Museum::one, Museum::two};
}
