#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define first fi
#define second se

template <class T1, class T2> bool minimize(T1& a, T2 b) {return b < a ? (a=b, true) : false;}
template <class T1, class T2> bool maximize(T1& a, T2 b) {return b > a ? (a=b, true) : false;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)
#define all(v) v.begin(), v.end()

#define MAX
#define MOD

struct Frac{
    ll nume, deno;
    Frac(ll nume, ll deno = 1): nume(nume), deno(deno) {
        // ll g = __gcd(nume, deno); 
        // this -> nume /= g, 
        // this -> deno /= g;
    }
    bool operator < (Frac a) const {
        return nume * a.deno < deno * a.nume;
    }
    bool operator == (Frac a) const {
        return nume * a.deno == deno * a.nume;
    }
    bool operator > (Frac a) const {
        return nume * a.deno > deno * a.nume;
    }
};

void input();
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int tests; cin >> tests;
    FOR(int, _, 1, tests) {
        ll a, b, c, k; cin >> a >> b >> c >> k;
        if (a > b) swap(a, b);
        if (a > c) swap(a, c);
        if (b > c) swap(b, c);

        ll wA = 0;
        for (wA = 1; (wA-1) * (wA-1) * (wA-1) <= k; wA++) {
            ll col = b * (wA+1); col = col / a - (col % a == 0);
            ll hei = c * (wA+1); hei = hei / a - (hei % a == 0);
            // cerr << wA << '.' << col << ' ' << hei << '\n';
            if (__int128(wA * col) * hei >= k) break;
        }
        // assert(wA > 0);

        wA = max(wA-1, 1ll);
        Frac ans = 0;
        for (int i = 0; i <= 1; i++, wA++) {
            for (ll wB = wA; wA * (wB-1) * (wB-1) <= k; wB++) {
                ll wC = k / (wA * wB) + (k % (wA * wB) > 0);
                // cerr << wA << ' ' << wB << ' ' << wC << '\n';
                // assert(wC > 0);
                // assert(wA * wB * wC >= k);

                maximize(ans, min({
                    Frac(a, wA),
                    Frac(b, wB),
                    Frac(c, wC),
                }));
            }
        }

        // assert(__gcd(ans.nume, ans.deno) == 1);
        // assert(ans.nume != 0);
        ll g = __gcd(ans.nume, ans.deno);
        cout << ans.nume / g << ' ' << ans.deno / g << '\n';
        // cerr << "===\n";
    }
}
void input() {
    // 
}