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

#define MAX 1000001
#define MOD 1000000007

#include "tiling.h"

int N, M;
int colL, colR, pLU, pLD, pRU, pRD;


pii doLU() {
    if (colL == colR) {
        if (pLU < pRU) pLU = pRU;
        else pRU = pLU;
        pii ans = {pLU++, colL}; pRU++;
        return ans;
    }

    pii ans = {pLU++, colL};
    if (pLU > pLD)
        colL++, pLU = 0, pLD = N-1;
    return ans;
}
pii doRU() {
    if (colL == colR) {
        if (pLU < pRU) pLU = pRU;
        else pRU = pLU;
        pii ans = {pRU++, colR}; pLU++;
        return ans;
    }

    pii ans = {pRU++, colR};
    if (pRU > pRD)
        colR--, pRU = 0, pRD = N-1;
    return ans;
}
pii doLD() {
    if (colL == colR) {
        if (pLD > pRD) pLD = pRD;
        else pRD = pLD;
        pii ans = {pLD--, colL}; pRD--;
        return ans;
    }

    pii ans = {pLD--, colL};
    if (pLU > pLD)
        colL++, pLU = 0, pLD = N-1;
    return ans;
}
pii doRD() {
    if (colL == colR) {
        if (pLD > pRD) pLD = pRD;
        else pRD = pLD;
        pii ans = {pRD--, colR}; pLD--;
        return ans;
    }

    pii ans = {pRD--, colR};
    if (pRU > pRD)
        colR--, pRU = 0, pRD = N-1;
    return ans;
}

void init(int _N, int _M) {
    N = _N; M = _M;
    colL = 0, colR = M-1, pLU = pRU = 0, pLD = pRD = N-1;
}

#define LU 0
#define RU 1
#define RD 2
#define LD 3

std::pair<int, int> receive_block(int TL, int TR, int BL, int BR) {
    int type =
        (BR == 0) ? LU : (
            (BL == 0) ? RU : (
                (TL == 0) ? RD : LD
            )
        );

    pii ans;
    switch (type) {
        case LU: ans = doLU(); break;
        case LD: ans = doLD(); break;
        case RU: ans = doRU(); break;
        case RD: ans = doRD(); break;
    }

    return {ans.fi * 2, ans.se * 2};
}
