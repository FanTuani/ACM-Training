// 质因数分解 记录质因数出现次数
#include <bits/stdc++.h>
using namespace std;
map<int, int> mp;
int calc(int x) {
    int x;
    cin >> x;
    for (int fac = 2; fac * fac <= x; fac++) {
        while (x % fac == 0) {
            x /= fac;
            mp[fac]++;
        }
    }
    if (x > 1) {
        mp[x]++;
    }
}