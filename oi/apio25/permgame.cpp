#include "permgame.h"
#include <bits/stdc++.h>
using namespace std;

namespace Subtask2{
    void solve(vector<int> &p) {
        int n = p.size();
        for (int i = 0; i < n; i++) if (p[i] != i) {
            for (int j = i + 1; j < n; j++) if (p[j] == i) {
                Bob({i, j});
                swap(p[i], p[j]);
            }
        }
    }
};

int Alice(int m, int e, vector<int> u, vector<int> v, int n, vector<int> p) {
    if (m == 2)
        Subtask2::solve(p);
        return p.size();
    if (e > m) {
        int ans = 0;
        for (int i = 0; i < n; i++) ans += p[i] == i;
        return ans;
    }
}

// đọc đề còn không hiểu nữa :)
