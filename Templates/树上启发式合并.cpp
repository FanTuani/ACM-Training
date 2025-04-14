// 树上启发式合并 洛谷 U41492 统计子树不同颜色数
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q, c[N], top[N], sz[N], hson[N], ans[N], buc[N], fa[N], diff;
vector<int> con[N];
void df(int a, int f) {
    sz[a] = 1;
    fa[a] = f;
    for (int t : con[a]) {
        if (t == f)
            continue;
        df(t, a);
        sz[a] += sz[t];
        hson[a] = sz[t] > sz[hson[a]] ? t : hson[a];
    }
}
void dt(int a, int f) { // no need
    for (int t : con[a]) {
        if (t == f)
            continue;
        top[t] = t == hson[a] ? top[a] : t;
        dt(t, a);
    }
}
void addSub(int a) {
    diff += buc[c[a]] == 0;
    buc[c[a]]++;
    for (int t : con[a]) {
        if (t == fa[a])
            continue;
        addSub(t);
    }
}
void delSub(int a) {
    diff -= buc[c[a]] == 1;
    buc[c[a]]--;
    for (int t : con[a]) {
        if (t == fa[a])
            continue;
        delSub(t);
    }
}
void dfs(int a, bool keep) {
    for (int t : con[a]) {
        if (t == fa[a] or t == hson[a])
            continue;
        dfs(t, false);
    }
    if (hson[a])
        dfs(hson[a], true);
    for (int t : con[a]) {
        if (t == fa[a] or t == hson[a])
            continue;
        addSub(t);
    }
    diff += buc[c[a]] == 0;
    buc[c[a]]++;
    ans[a] = diff;
    if (!keep) {
        delSub(a);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        con[f].push_back(t);
        con[t].push_back(f);
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    df(1, 1);
    top[1] = 1;
    dt(1, 1);
    dfs(1, 1);
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        cout << ans[t] << '\n';
    }
}