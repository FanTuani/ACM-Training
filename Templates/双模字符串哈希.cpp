// 双模字符串哈希
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;

struct DoubleHash {
    int P[2] = {131, 13331};
    int mod[2] = {(int)(1e9 + 7), (int)(1e9 + 9)};
    int h[N][2], p[N][2];
    int len;

    void init(string s) {
        s = ' ' + s;
        len = s.size();
        for (int x = 0; x <= 1; x++) {
            p[0][x] = 1;
            for (int i = 1; i < len; i++) {
                p[i][x] = p[i - 1][x] * P[x] % mod[x];
                h[i][x] = (h[i - 1][x] * P[x] % mod[x] + s[i]) % mod[x];
            }
        }
    }
    int get(int l, int r, int x) {
        int tmp = h[r][x] - h[l - 1][x] * p[r - l + 1][x] % mod[x];
        return (tmp % mod[x] + mod[x]) % mod[x];
    }
} hashi;
vector<pair<int, int> > a;

signed main() { // 字符串去重求总数 P3370
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    set<int> s;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        hashi.init(s);
        a.push_back({hashi.get(1, s.size(), 0), hashi.get(1, s.size(), 1)});
    }
    sort(a.begin(), a.end());
    for (int i = 1; i < a.size(); i++) {
        auto [n1, n2] = a[i];
        auto [p1, p2] = a[i - 1];
        if (n1 == p1 and n2 == p2) {
            n--;
        }
    }
    cout << n;
}