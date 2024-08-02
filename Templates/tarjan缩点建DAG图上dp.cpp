// tarjan缩点建DAG图上dp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int dfn[N], low[N], cnt, scc[N], cscc, w[N], cow[N], dp[N], in[N];
bool instk[N];
vector<int> con[N], co[N];
stack<int> stk;
void tarjan(int a) {
    low[a] = dfn[a] = ++cnt;
    stk.push(a);
    instk[a] = true;
    for (int t : con[a]) {
        if (!dfn[t]) {
            tarjan(t);
            low[a] = min(low[a], low[t]);
        } else if (instk[t]) {
            low[a] = min(low[a], dfn[t]);
        }
    }
    if (low[a] == dfn[a]) {
        cscc++;
        int top;
        do {
            top = stk.top();
            stk.pop();
            instk[top] = false;
            scc[top] = cscc;
            cow[cscc] += w[top];  // 累加点权
        } while (top != a);
    }
}
void topo() {
    queue<int> q;
    for (int i = 1; i <= cscc; i++) {
        if (in[i] == 0) {
            dp[i] = cow[i];
            q.push(i);
        }
    }
    while (q.size()) {
        int a = q.front();
        q.pop();
        for (int t : co[a]) {
            if (--in[t] == 0) {
                q.push(t);
                dp[t] = max(dp[t], dp[a] + cow[t]); // DAG 上 dp
            }
        }
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int j = 1; j <= m; j++) {
        int f, t;
        cin >> f >> t;
        con[f].push_back(t);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }
    // 缩点
    for (int i = 1; i <= n; i++) {
        for (int t : con[i]) {
            if (scc[i] != scc[t]) {
                co[scc[i]].push_back(scc[t]);
                in[scc[t]]++;
            }
        }
    }
    topo();
    int ans = 0;
    for (int i = 1; i <= cscc; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans;
}