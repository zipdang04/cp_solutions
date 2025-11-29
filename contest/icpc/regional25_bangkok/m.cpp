#include <bits/stdc++.h>
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set
= tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<class T1, class T2> void minimize(T1& a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1& a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)
#define EFOR(type, i, a, b) for (type i = (a); i < (b); i++)
#define EREV(type, i, a, b) for (type i = (a); i > (b); i--)

#define MAX 200'005

ordered_set<int> allPos;
int n, p[MAX], _pos[MAX];
int ans[MAX];

main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n; FOR(int, i, 1, n) cin >> p[i];
	FOR(int, i, 1, n) _pos[p[i]] = i;

	FOR(int, i, 1, n) allPos.insert(i);
	int head = 1, size = n;
	REV(int, value, n, 1) {
		assert(allPos.size() == value);
		size = allPos.size();
		int pos = _pos[value];
		int k = allPos.order_of_key(pos) + 1;
		ans[value] = size - (k - head);
		if (ans[value] > size) ans[value] -= size;

		int prevHeadPos = *allPos.find_by_order(k % size); // already add one
		allPos.erase(pos);
		head = allPos.order_of_key(prevHeadPos) + 1;
	}

	FOR(int, i, 1, n) cout << ans[i] << " \n"[i == n];
}