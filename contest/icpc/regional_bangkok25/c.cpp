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

#define MAX 300'005

bool isNega[MAX];
bool test(int N, int target) {
	int sum = 1;
	REV(int, value, N, 2) {
		if (sum > target) 
			sum -= value, isNega[value] = true;
		else 
			sum += value, isNega[value] = false;	// always overwrite
	}
	assert((sum == target or sum-target == 2));
	// cerr << N << ' ' << target << '\n';
	// cerr << "diff: " << sum - target << '\n';
	if (sum-target == 2)
		FOR(int, i, 2, N-1) if (isNega[i] and not isNega[i+1]){
			sum -= 2; isNega[i] = false, isNega[i+1] = true;
			break;
		}
	if (sum-target == 2)
		FOR(int, i, 2, N-2) FOR(int, j, i+1, N-i) {
			int k = i+j+1;
			if (k <= N and isNega[i] and isNega[j] and not isNega[k]) {
				sum -= 2;
				isNega[i] = isNega[j] = false;
				isNega[k] = true;
				break;
			}
			k = i+j-1;
			if (not isNega[i] and not isNega[j] and isNega[k]) {
				sum -= 2;
				isNega[i] = isNega[j] = true;
				isNega[k] = false;
				break;
			}
		}
	// cerr << "diff: " << sum - target << '\n';
	// cerr << "1"; FOR(int, i, 2, N) cerr << (isNega[i] ? '-' : '+') << i; cerr << '\n';
	return sum == target;
}
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int t; cin >> t;
	FOR(int, _, 1, t) {
		int target; cin >> target;
		int N = max(0, (int)sqrt(abs(target) * 2) - 10);
		while (true) {
			N++;
			int largest = N * (N+1) / 2;
			if ((largest - target) % 2 == 1) continue;
			largest = target >= 0 ? largest : (-largest+2);
			if (abs(target) > abs(largest)) continue;
			// cerr << target << ' ' << N << '\n';
			if (test(N, target)) break;
			// if (abs(target) > 100) assert(false);
			// assert(false);
		}

		cout << N << " \n1";
		FOR(int, i, 2, N) cout << (isNega[i] ? '-' : '+') << i;
		cout << '\n';
	}
}