// tarjan 求割点
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int low[N], cnt, dfn[N];
vector<int> con[N], cut;
void tarjan(int a, bool root) {
    low[a] = dfn[a] = ++cnt;
    int tot = 0;
    for (int t : con[a]) {
        if (!dfn[t]) {
            tarjan(t, false);
            low[a] = min(low[a], low[t]);
            tot += low[t] >= dfn[a];
        } else {
            low[a] = min(low[a], dfn[t]);
        }
    }
    if (tot > root) {
        cut.push_back(a);
    }
}
signed main() {
    int n;
    cin >> n;
    while (scanf("%lld", &n), n) {
        for (int i = 1; i <= n; i++) {
            con[i].clear();
            low[i] = dfn[i] = 0;
        }
        cnt = 0;
        cut.clear();
        int a;
        while (scanf("%lld", &a), a) {
            while (getchar() != '\n') {
                int b;
                scanf("%lld", &b);
                con[a].push_back(b);
                con[b].push_back(a);
            }
        }
        tarjan(1, true);
        cout << cut.size() << '\n';
    }
}