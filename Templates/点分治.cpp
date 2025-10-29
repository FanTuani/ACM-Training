// 点分治
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e4 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, k, ctr, sz[N], del[N], cnt[N], tmp[N], pt, ans;
vector<int> con[N];
void df(int a, int f) { // 求子树的重心
    sz[a] = 1;
    int mxs = 0;
    for (int t : con[a]) {
        if (t == f or del[t])
            continue;
        df(t, a);
        if (ctr)
            return;
        sz[a] += sz[t];
        mxs = max(mxs, sz[t]);
    }
    mxs = max(mxs, n - sz[a]); // 勿忘
    if (mxs <= n / 2) {
        ctr = a;
        sz[f] = n - sz[a];
    }
}
void dfs(int a, int f, int dep) { // 求答案
    if (dep > k)
        return;
    ans += cnt[k - dep];
    tmp[pt++] = dep;
    for (int t : con[a]) {
        if (t == f or del[t])
            continue;
        dfs(t, a, dep + 1);
    }
}
void run(int a) {
    // 对包含 a 的路径求答案
    // 注意在此清空求答案的临时数组
    // 每次 run 相当于单独求一棵树的答案
    del[a] = true;
    cnt[0] = 1;
    for (int t : con[a]) {
        if (del[t])
            continue;
        dfs(t, a, 1);
        for (int i = 0; i < pt; i++) {
            cnt[tmp[i]]++;
        }
        pt = 0;
    }
    for (int i = 1; i <= k; i++) {
        cnt[i] = 0;
    }
    // 对不包含 a 的路径求答案
    // 删去 a 点，对子树递归处理
    for (int t : con[a]) {
        if (del[t])
            continue;
        ctr = 0;
        n = sz[t]; // n 会改变，检查在其它地方的使用
        df(t, a);
        run(ctr); // 参数是 ctr
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        con[t].push_back(f);
        con[f].push_back(t);
    }
    df(1, 1);
    run(ctr);
    cout << ans;
}