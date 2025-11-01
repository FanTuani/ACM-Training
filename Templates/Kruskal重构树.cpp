// Kruskal 重构树 P1967
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, m;
struct Eg {
    int f, t, w;
    Eg(int f, int t, int w) : f(f), t(t), w(w) {};
};
vector<Eg> eg;
vector<int> con[N];
bool cmp(Eg q, Eg w) {
    return q.w > w.w;
}
int fa[N], ans[N], dep[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void kru() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    sort(eg.begin(), eg.end(), cmp);
    for (auto [f, t, w] : eg) {
        int fx = find(f), tx = find(t);
        if (fx != tx) {
            fa[fx] = fa[tx] = ++n;
            fa[n] = n;
            con[n].push_back(fx);
            con[n].push_back(tx);
            ans[n] = w;
        }
    }
}
int dp[N][32];
void dfs(int a, int f) {
    dp[a][0] = f;
    dep[a] = dep[f] + 1;
    for (int t : con[a]) {
        if (t == f)
            continue;
        dfs(t, a);
    }
}
void prework() {
    for (int j = 1; j < 30; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
}
int lca(int a, int b) {
    if (find(a) != find(b))
        return 0;
    if (dep[a] < dep[b])
        swap(a, b);
    int k = dep[a] - dep[b];
    for (int j = 0; j < 30; j++) {
        if (k >> j & 1ll) {
            a = dp[a][j];
        }
    }
    for (int j = 29; j >= 0; j--) {
        if (dp[a][j] != dp[b][j]) {
            a = dp[a][j], b = dp[b][j];
        }
    }
    return dp[a][0];
}
bool vis[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        eg.push_back({f, t, w});
    }
    kru();
    for (int i = 1; i <= n; i++) {
        if (vis[find(i)])
            continue;
        vis[find(i)] = true;
        dfs(find(i), find(i));
    }
    prework();
    ans[0] = -1;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << ans[lca(a, b)] << '\n';
    }
}