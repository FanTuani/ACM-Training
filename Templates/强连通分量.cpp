// 强连通分量
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int dfn[N], low[N], cnt, scc[N], cscc;
bool instk[N], scvis[N];
vector<int> con[N], sc[N];
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
            sc[cscc].push_back(top);
        } while (top != a);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int j = 1; j <= m; j++) {
        int f, t;
        cin >> f >> t;
        con[f].push_back(t);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }
    cout << cscc << '\n';
    for (int i = 1; i <= n; i++) {
        if (scvis[scc[i]])
            continue;
        scvis[scc[i]] = true;
        sort(sc[scc[i]].begin(), sc[scc[i]].end());
        for (int t : sc[scc[i]]) {
            cout << t << ' ';
        }
        cout << '\n';
    }
}