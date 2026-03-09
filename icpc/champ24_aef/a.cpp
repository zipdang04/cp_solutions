#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2>
bool minimize(T1 &a, T2 b) {
    return (b < a) ? (a=b, true) : false;
}
template<class T1, class T2>
bool maximize(T1 &a, T2 b) {
    return (b > a) ? (a=b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 300'005
#define MOD

bool check(pii one, pii two, pii thr) {
    return max({one.fi, two.fi, thr.fi}) <= min({one.se, two.se, thr.se});
}
int n, realN;
pair<pii, int> girls[MAX];

class SegTree{
private:
    int len;
    inline static int it[MAX * 4] = {};
    #define cal(i, j) ((girls[i].fi.se < girls[j].fi.se) ? i : j)
    void buildTree(int idx, int lo, int hi) {
        if (lo == hi) {it[idx] = girls[lo].fi.fi; return;}

        int y = idx << 1, mid = (lo + hi) / 2;
        buildTree(y, lo, mid);
        buildTree(y+1, mid+1, hi);
        it[idx] = min(it[y], it[y+1]);
    }
    void del(int idx, int lo, int hi, int pos)  {
        if (lo == hi) {
            assert(lo == pos);
            it[idx] = INT_MAX;
            return;
        }

        int y = idx << 1, mid = (lo + hi) / 2;
        if (pos <= mid) del(y, lo, mid, pos);
        else del(y+1, mid+1, hi, pos);
        it[idx] = min(it[y], it[y+1]);
    }
    int get(int idx, int lo, int hi, int posL, int posR, int threshold) {
        if (hi < posL or posR < lo or it[idx] > threshold) return INT_MAX;
		if (lo == hi) return lo;
        // if (posL <= lo and hi <= posR) return it[idx];
        int y = idx << 1, mid = (lo + hi) / 2;
		
		int res = get(y, lo, mid, posL, posR, threshold);
		if (res != INT_MAX) return res;
		return get(y+1, mid+1, hi, posL, posR, threshold);
        // return cal(
        //     get(y, lo, mid, posL, posR),
        //     get(y+1, mid+1, hi, posL, posR)
        // );
    }
public:
    SegTree(){}
    SegTree(int len): len(len) {buildTree(1, 1, len);}
    void del(int pos) {del(1, 1, len, pos);}
    int get(int posL, int posR, int threshold) {return get(1, 1, len, posL, posR, threshold);}
} seg;

bool used[MAX];
tuple<int, int, int> answer[MAX]; int ptrAns = 0;

void input(), clear();
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int tests; cin >> tests;
    FOR(int, _,1, tests) {
        input();
        seg = SegTree(realN);
        bool oke = true;
        FOR(int, i, 1, realN) if (not used[i]) {
            int thres = girls[i].fi.se;
    
            int p1 = seg.get(i+1, realN, thres);
            if (p1 == INT_MAX) {oke = false; break;}
            seg.del(p1);
            
            int p2 = seg.get(i+1, realN, thres);
            if (p2 == INT_MAX) {oke = false; break;}
            seg.del(p2);
    
            used[p1] = used[p2] = true;
            if (not check(girls[i].fi, girls[p1].fi, girls[p2].fi)) {oke = false; break;}
            answer[++ptrAns] = {girls[i].se, girls[p1].se, girls[p2].se};
        }
        if (not oke) {cout << "No\n";}
        else {
            cout << "Yes\n";
            FOR(int, i, 1, n) {
                auto [a, b, c] = answer[i];
                cout << a << ' ' << b << ' ' << c << '\n';
            }
        }

        clear();
    }
}
void input() {
    cin >> n; realN = 3*n;
    FOR(int, i, 1, realN) {
        int a, b; cin >> a >> b;
        girls[i] = {{a, b}, i};
    }
    sort(girls + 1, girls + 1 + realN, [](pair<pii, int> a, pair<pii, int> b) {
		return pii(a.fi.se, a.fi.fi) < pii(b.fi.se, b.fi.fi);
	});
    girls[0] = {{INT_MAX, INT_MAX}, 0}; 
}
void clear() {
    FOR(int, i, 1, realN) used[i] = false;
    ptrAns = 0;
}