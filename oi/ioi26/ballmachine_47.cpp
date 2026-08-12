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
bool maximize(T1 &a, T2 b){
    return (b > a) ? (a = b, true) : false;
}
template <class T1, class T2>
bool minimize(T1 &a, T2 b){
    return (b < a) ? (a = b, true) : false;
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
#include "ballmachine.h"

#define MAX_N 1005
#define NaN -1

int N, M;

struct Sequence {
    vector<int> seq;
    int ptr = 0;

    Sequence(vector<int> seq = {}): seq(seq), ptr(0) {}
    bool isEnd() {
        return ptr >= (int) seq.size();
    }
    int next() {
        assert((not isEnd()));
        return seq[ptr++];
    }
    int peek() {
        return isEnd() ? NaN : seq[ptr];
    }
    int peekNext() {
        int tmp = ptr + 1;
        if (tmp >= (int) seq.size()) return NaN;
        return seq[tmp];
    }
};

namespace Subtask123 {
    Sequence seq;
    int nodePtr = 0;
    int par[MAX_N];

    void dfs(int p) { // p is parent of this node
        const int curVal = seq.next();

        // is child
        if (seq.isEnd() or curVal < seq.peek()) {
            par[curVal] = p;
            return;
        }
        // has child -> ordering this node first
        const int u = nodePtr--;
        par[u] = p;

        // no branching
        if (curVal == seq.peek()) {
            dfs(u); return;
        }

        // has branch
        while (seq.peek() < curVal) {
            dfs(u);
        }
        dfs(u);
    }

    vector<int> solve() {
        N = 0;
        REV(int, i, M-1, 0) {
            while (insert(i, i)) N++;
        }

        seq = Sequence(collect());
        nodePtr = N-1;
        dfs(N-1);
        return vector<int>(par, par + N-1);
    }
}

namespace Subtask4_FAILED {
    const int BLOCK = 1;

    Sequence seq;
    int nodePtr = 0;
    int par[MAX_N];
    vector<int> order;

    void dfs(int p, int offset, vector<int> &newOrder) { // p is parent of this node
        const int curVal = seq.next();

        // is child
        if (seq.isEnd() or curVal < seq.peek()) {
            cerr << "is child | " << curVal << ' ' << offset << " => " << p << '\n';
            int newNode = curVal + offset;
            newOrder.push_back(newNode);
            par[newNode] = p;
            return;
        }
        // has child -> ordering this node first
        const int u = nodePtr--;
        newOrder.push_back(u);
        par[u] = p;

        // no branching
        if (curVal == seq.peek()) {
            dfs(u, offset, newOrder); return;
        }

        // has branch
        while (seq.peek() < curVal) {
            dfs(u, offset, newOrder);
        }
        dfs(u, offset, newOrder);
    }

    vector<int> solve() {
        // phase 0.1 -- get size
        int init_size = 0; while (insert(0, 0)) N++, init_size++;
        FOR(int, i, 1, M-1) while (insert(i, 0)) N++;
        collect();
        cerr << "N = " << N << '\n';

        // phase 0.2 -- build first
        nodePtr = N-1;
        vector<int> newOrder;
        FOR(int, i, 1, init_size-1) {
            par[nodePtr] = nodePtr+1;
            newOrder.push_back(nodePtr--);
        }
        par[0] = nodePtr+1;
        newOrder.push_back(0);
        order = newOrder;

        for (int l = 1, r = BLOCK; l < M; l += BLOCK, r += BLOCK) {
            newOrder.clear();
            minimize(r, M-1);
            cerr << "processing: " << l << ' ' << r << '\n';

            // fill in the blank
            int _tmp = 0;
            FOR(int, i, 0, l-1) while (insert(i, BLOCK)) _tmp++;
            assert(_tmp == (int)order.size());

            // fill in the rest
            REV(int, i, r, l) while (insert(i, i-l));
            seq = Sequence(collect());
            cerr << "[ "; for (int i: seq.seq) cerr << i << ' '; cerr << "]\n";

            // process
            vector<int> newOrder;
            int ptrOrder = -1;
            while (not seq.isEnd()) {
                if (seq.peek() == BLOCK) {
                    newOrder.push_back(order[++ptrOrder]);
                    // assert(order[ptrOrder] == BLOCK);
                    cerr << ptrOrder << ' ' << seq.peek() << '\n';
                    seq.next();
                    continue;
                }

                int u = order[ptrOrder];
                cerr << "dfs: " << u << '\n';
                dfs(u, l, newOrder);
            }
            order = newOrder;
            cerr << "order: "; for (int i:order) cerr << i << ' '; cerr << '\n';
        }
        return vector<int>(par, par + N-1);
    }
}
namespace Subtask4 {
    Sequence seq;
    int nodePtr = 0;
    int par[MAX_N];

    void dfs(int p) { // p is parent of this node
        const int curVal = seq.next();

        // is child
        if (seq.isEnd() or curVal < seq.peek()) {
            par[curVal] = p;
            return;
        }
        // has child -> ordering this node first
        const int u = nodePtr--;
        par[u] = p;

        // no branching
        if (curVal == seq.peek()) {
            dfs(u); return;
        }

        // has branch
        while (seq.peek() < curVal) {
            dfs(u);
        }
        dfs(u);
    }

    vector<int> solve() {
        N = 0;
        REV(int, i, M-1, 0) {
            while (insert(i, i)) N++;
        }

        seq = Sequence(collect());
        nodePtr = N-1;
        dfs(N-1);
        return vector<int>(par, par + N-1);
    }
}

std::vector<int> find_structure(int _M) {
    M = _M;

    return Subtask4::solve();
}
