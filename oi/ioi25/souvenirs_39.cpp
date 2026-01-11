#include "souvenirs.h"
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

#define MAX 105
#define MOD 1000000007

int N; ll P0;
ll prices[MAX];
int times[MAX];

pair<vector<int>, long long> callTransaction(ll m) {
    cerr << "call " << m << '\n';
    auto [bought, remain] = transaction(m);
    for (int pos: bought) times[pos]++;
    return {bought, m - remain};
}

int getSubtask() {
    if (N == 2) return 1;
    if (N == 3) return 4;

    return 0;
}
void fillTillSufficient() {
    for (int i = 2; i < N; i++) {
        while (times[i] < i) callTransaction(prices[i]);
    }
}

namespace Subtask1 {
    void solve() {
        callTransaction(P0 - 1);
    }
}

namespace Subtask4 {
    void solve() {
        auto [bought, total] = callTransaction(P0 - 1);
        if (bought.size() == 1) {
            ll P1 = total;
            callTransaction(P1 - 1);
            callTransaction(P1 - 1);
        } else {
            callTransaction((total - 1) / 2);
        }
    }
}

namespace Subtask23 {
    void solve() {
        bool last = false;
        for (int i = 1; i < N; i++) {
            ll prev = prices[i-1];
            auto [bought, total] = callTransaction(prev - 1);
            if (bought.size() == 1)
                prices[i] = total;
            else {
                prices[i] = total - 1;
            }
        }

        // for (ll i: prices) cerr << i << ' '; cerr << '\n';
        fillTillSufficient();
    }
}

// namespace Subtask5 {
//     void solve() {
//         for (int i = 1; i < N; i++) {
//             ll money = prices[i-1] - 1;
//             auto [bought, total] = callTransaction(money);
//             cerr << total << '\n';

//             if (bought.size() == 1) {
//                 prices[i] = total;
//             } else {
//                 ll money = (total - 1) / 2, smaller;
//                 std::tie(bought, smaller) = callTransaction(money);

//                 ll bigger = total - smaller;
//                 prices[i] = bigger;
//                 continue;
//             }
//         }
//         // cerr << "done" << endl;
//         fillTillSufficient();
//     }
// }

void clear();
void buy_souvenirs(int _N, long long _P0) {
    N = _N, P0 = _P0;
    prices[0] = P0;

    int subtask = getSubtask();
    Subtask23::solve();
    switch (subtask)
    {
        case 1: Subtask1::solve(); break;
        case 4: Subtask4::solve(); break;
        default: Subtask23::solve(); break;
    }
}
void clear() {
    //
}
