// 最小生成树 kruskal
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, m, fa[N];
struct Eg {
    int f, t, w;
    Eg() : f(0), t(0), w(0) {};
    Eg(int f, int t, int w) : f(f), t(t), w(w) {};
    bool operator<(const Eg& b) const { return w < b.w; }
} eg[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int kru() {
    sort(eg + 1, eg + 1 + m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    int ans = 0, cnt = 0;
    for (int i = 1; i <= m; i++) {
        auto [f, t, w] = eg[i];
        int ff = find(f), ft = find(t);
        if (ff == ft)
            continue;
        fa[ff] = ft;
        ans += w;
        cnt++;
    }
    return cnt < n - 1 ? -1 : ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        eg[i] = Eg(f, t, w);
    }
    int res = kru();
    if (res == -1)
        cout << "orz";
    else
        cout << res;
}