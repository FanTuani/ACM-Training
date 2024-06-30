// 堆优化Dijkstra
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, m, s, dis[N];
bool vis[N];
struct Eg {
    int t, w;
    Eg(int t, int w) : t(t), w(w){};
    bool operator<(const Eg& oth) const { return w > oth.w; }
};
vector<Eg> con[N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        con[f].push_back(Eg(t, w));
    }
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
    }
    dis[s] = 0;
    priority_queue<Eg> q;
    q.push(Eg(s, 0));
    while (q.size()) {
        int a = q.top().t;
        q.pop();
        if (vis[a])
            continue;
        vis[a] = true;
        for (auto eg : con[a]) {
            auto [t, w] = eg;
            dis[t] = min(dis[t], dis[a] + w);
            if (!vis[t])
                q.push(Eg(t, dis[t]));
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << ' ';
    }
}