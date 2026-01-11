#include "hack.h"
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

randomize;
struct rnd{
    inline static ll next(ll n) {return mt() % n;}
    inline static ll next(ll l, ll r) {return l + next(r-l+1);}
};

vector<ll> operator + (const vector<ll> a, const vector<ll> b) {
    vector<ll> ans(a.size() + b.size());
    int ptr = 0;
    for (ll i: a) ans[ptr++] = i;
    for (ll i: b) ans[ptr++] = i;
    return ans;
}

namespace Subtask1{
    constexpr int MAX = 1'000'000;
    long long collisions[MAX + 1] = {};

    void buildCollisions() {
        for (int n = 1; n <= MAX; n++) {
            int r = MAX % n, q = MAX / n;
            collisions[n]
                = 1ll * r * (q+1) * q / 2
                + 1ll * (n-r) * q * (q-1) / 2;
	    }
    }

    int getBucket(long long number) {
        int lo = 1, hi = MAX;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (collisions[mid] == number)
                return mid;
            if (collisions[mid] > number)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return 1/0;
    }
}

namespace Subtask3{
    const int FIRST = 22500;

    pair<vector<ll>, vector<ll>> split(vector<ll> arr) {
        int mid = int(arr.size()) / 2;
        vector<ll> l(arr.begin(), arr.begin() + mid);
        vector<ll> r(arr.begin() + mid, arr.end());
        return {l, r};
    }
    pair<ll, ll> find(vector<long long> arr) {
        ll d = arr[0];
        while (arr.size() > 1) {
            auto [a1, a2] = split(arr);
            vector<ll> newA = a1;
            if (newA[0] != d) newA.push_back(d);
            if (collisions(newA)) arr = a1;
            else arr = a2;
        }
        return {d, arr[0]};
    }
    pair<ll, ll> find(vector<long long> L, vector<long long> R) {
        if ((int)L.size() + (int)R.size() == 2) {
            vector<long long> all = L;
            all.insert(all.end(), R.begin(), R.end());
            return {all[0], all[1]};
        }
        auto [LL, LR] = split(L);
        auto [RL, RR] = split(R);

        if (collisions(LL + R)) {
            return find(R, LL);
        }
        else {
            return find(R, LR);
        }
    }

    bool test(ll d) {
        return collisions({1, d + 1}) != 0;
    }

    ll calD(const ll num) {
        ll tmp = num;
        vector<ll> primes;
        for (ll d = 2; d * d <= tmp; d++) {
            if (tmp % d == 0) {
                primes.push_back(d);
                while (tmp % d == 0) tmp /= d;
            }
        }
        if (tmp > 1) primes.push_back(tmp);

        tmp = num;
        for (ll p: primes)
            while (tmp % p == 0 and test(tmp / p))
                tmp /= p;
        return tmp;
    }

    int solve() {
        int cnt = 0;
        vector<ll> a, b;
        for (int i = 0; i < FIRST; i++)
            a.push_back(i + 1);
        for (int i = 1; i < FIRST; i++) {
            ll num = 500'000'000 + i * FIRST;
            b.push_back(num);
            if (num > 1'000'000'000) break;
        }

        ll num;
        auto [tmp1, tmp2] = find(b);
        if (collisions({tmp1, tmp2}))
            num = abs(tmp1 - tmp2);
        else {
            auto [d1, d2] = find(a, b);
            num = abs(d1 - d2);
        }


        ll answer = calD(num);
        return answer;
    }
}

int hack(){
    // Subtask1::buildCollisions();
    // std::vector<long long> all(Subtask1::MAX);
    // std::iota(all.begin(), all.end(), 1);
    // return Subtask1::getBucket(collisions(all));
    return Subtask3::solve();
}
