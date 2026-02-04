#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> 
bool minimize(T1 &a, T2 b) {
    return (b < a) ? (a = b, true) : false;
}
template<class T1, class T2> 
bool maximize(T1 &a, T2 b) {
    return (b > a) ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 1005
#define MOD

int n;
int a[MAX];
bool used[MAX];
vector<pii> answer;

void input(), clear();
main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    FOR(int, i, 1, n) cin >> a[i];

    FOR(int, i, 1, n) {
        int value = a[i];
        used[value] = true;
        FOR(int, v2, value + 1, n) if (not used[v2])
            answer.push_back({v2, value});
        REV(int, v2, n, 1) if (not used[v2])
            answer.push_back({value, v2});
    }

    cout << answer.size() << '\n';
    for (auto [x, y]: answer) cout << x << ' ' << y << '\n';
}
void input() {} 
void clear() {}