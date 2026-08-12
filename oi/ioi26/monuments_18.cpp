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

#include "monuments.h"
#include <vector>

#define MAX 1000001
#define MOD 1000000007

namespace Common {
    ll calFree(const ll *arr, ll beg, ll end) {
        int len = end-beg+1;
        int l = (len-1) / 2, r = len-1 - l;

        ll ans = 0;
        while (l >= 0 and r <= len-1) {
            if (arr[beg + l] < 0 and arr[beg + r] > 0)
                ans += abs(abs(arr[beg + l]) - abs(arr[beg + r]));
            else
                ans += abs(arr[beg + l]) + ((l == r) ? 0 : abs(arr[beg + r]));
            l--, r++;
        }
        return ans;
    }
    ll calFree(vector<ll> arr) {
        const int n = arr.size();
        int l = (n-1) / 2, r = n-1 - l;

        ll ans = 0;
        while (l >= 0 and r <= n-1) {
            if (arr[l] < 0 and arr[r] > 0) ans += abs(abs(arr[l]) - abs(arr[r]));
            else ans += abs(arr[l]) + ((l == r) ? 0 : abs(arr[r]));
            l--, r++;
        }
        return ans;
    }
}

int n, m;
ll X[MAX]; vector<int> P;

namespace Sub1{
    ll solve() {
        for (int l = 0, r = n-1; l <= r; l++, r--)
            if (X[l] + X[r] != 0) return -1;
        return 0;
    }
}

namespace Sub2 {
    ll solve() {
        int l = (n-1) / 2, r = n-1 - l;
        ll ans = 0;
        while (l >= 0 and r <= n-1) {
            if (X[l] < 0 and X[r] > 0) ans += abs(abs(X[l]) - abs(X[r]));
            else ans += abs(X[l]) + ((l == r) ? 0 : abs(X[r]));
            l--, r++;
        }
        return ans;
    }
}

namespace Sub3 {
    ll solve() {
        return Common::calFree(X, 0, n-1);
    }
}
namespace Sub45 {
    ll FIXED; vector<ll> fixedNeed;
    ll remain[100] = {};
    ll check(const int mask) {
        int ptrRemain = 0, ptrNeed = 0;
        ll answer = 0;
        FOR(int, i, 0, n-1) {
            // ancient one
            if (testBit(FIXED, i)) continue;
            // try to make up
            if (testBit(mask, i)) {
                answer += abs(X[i] - fixedNeed[ptrNeed++]);
                continue;
            }
            // otherwise
            remain[ptrRemain++] = X[i];
        }
        assert(ptrNeed == m);
        answer += Common::calFree(remain, 0, ptrRemain-1);
        return answer;
    }
    ll solve() {
        FIXED = 0;
        for (int i: P) {
            FIXED |= 1 << i;
            fixedNeed.push_back(-X[i]);
        }
        reverse(fixedNeed.begin(), fixedNeed.end());
        for (ll i: fixedNeed) cerr << i << " "; cerr << '\n';

        ll answer = LLONG_MAX;
        FOR(int, mask, 0, (1ll << n) - 1) {
            if ((mask & FIXED) > 0 or cntBit(mask) != m) continue;
            cerr << bitset<5>(mask) << ' ' << bitset<5>(mask & FIXED) << ' ' << cntBit(mask) << '\n';
            minimize(answer, check(mask));
        }
        if (answer == LLONG_MAX) answer = -1;
        return answer;
    }
}

long long get_cost(std::vector<int> _X, std::vector<int> _P) {
    n = _X.size();
    vector<bool> isP(n, false); for (int i: _P) isP[i] = true;
    vector<int> realX, realP;

    vector<bool> removing(n, false);
    FOR(int, i, 0, n-1) if (isP[i] and _X[i] == 0) removing[i] = true;
    FOR(int, i, 0, n-1) FOR(int, j, i+1, n-1)
        if (
            (not removing[i]) and (not removing[j]) 
            and isP[i] and isP[j] 
            and _X[i] + _X[j] == 0
        )
            removing[i] = removing[j] = true;
            

    int ptr = 0;
    FOR(int, i, 0, n-1) {
        if (removing[i]) continue;

        realX.push_back(_X[i]);
        if (isP[i]) realP.push_back(ptr);
        ptr++;
    }

    for (int i: realX) cerr << i << '.'; cerr << '\n';
    for (int i: realP) cerr << i << '.'; cerr << '\n';

    n = realX.size(); m = realP.size();
    FOR(int, i, 0, n-1) X[i] = realX[i];
    P = realP;

    return Sub45::solve();
}
