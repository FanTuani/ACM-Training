// 长链剖分优化 dp P7768
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, w[N], sz[N], lson[N], xo[N], dep[N];
vector<int> con[N], que[N];
int q1[N], q2[N], mxd[N];
void df(int a, int f) {
    sz[a] = 1;
    xo[a] = w[a];
    mxd[a] = dep[a] = dep[f] + 1;
    for (int t : con[a]) {
        if (t == f)
            continue;
        df(t, a);
        mxd[a] = max(mxd[a], mxd[t]);
        xo[a] ^= xo[t];
        sz[a] += sz[t];
        lson[a] = mxd[t] > mxd[lson[a]] ? t : lson[a];
    }
}
vector<int> ans[N], dp[N];
void dfs(int a, int f) {
    if (lson[a]) {
        dfs(lson[a], a);
        dp[a].swap(dp[lson[a]]);
    }
    dp[a].push_back(xo[a]);
    for (int t : con[a]) {
        if (t == f or t == lson[a])
            continue;
        dfs(t, a);
        for (int i = 0; i < dp[t].size(); i++) {
            int ia = dp[a].size() - 1 - i, it = dp[t].size() - 1 - i;
            dp[a][ia - 1] ^= dp[t][it];
        }
    }
    for (int h : que[a]) {
        if (h >= mxd[a] - dep[a]) {
            ans[a].push_back(xo[a]);
        } else {
            ans[a].push_back(xo[a] ^ dp[a][dp[a].size() - 2 - h]);
        }
    }
}
void read(int& x) {
    bool neg = false;
    x = 0;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            neg = true;
        ch = getchar();
    }
    if (neg) {
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + ('0' - ch);
            ch = getchar();
        }
    } else {
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + (ch - '0');
            ch = getchar();
        }
    }
}
int pt[N];
signed main() {
    read(n);
    read(q);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }
    for (int i = 2; i <= n; i++) {
        int f;
        read(f);
        con[f].push_back(i);
        con[i].push_back(f);
    }
    df(1, 1);
    for (int i = 1; i <= q; i++) {
        int x, h;
        read(x);
        read(h);
        q1[i] = x, q2[i] = h;
        que[x].push_back(h);
    }
    dfs(1, 1);
    for (int i = 1; i <= q; i++) {
        int x = q1[i];
        printf("%.3lf\n", ans[x][pt[x]++] * 0.001);
    }
}