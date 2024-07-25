// 带权并查集 P1196
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, fa[N], front[N], num[N];
// front[x] : x 节点所处的位置
// num[x] : 队头 x 所在队列的长度
int find(int x) {
    if (fa[x] == x)
        return x;
    int fx = find(fa[x]);
    front[x] += front[fa[x]];
    return fa[x] = fx;
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    front[fx] += num[fy];
    num[fy] += num[fx];
    num[fx] = 0;
    fa[fx] = fy;
}
int ask(int x, int y) {
    if (find(x) != find(y))
        return -1;
    return abs(front[x] - front[y]) - 1;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        num[i] = 1;
    }
    while (n--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'M') {
            merge(x, y);
        } else {
            cout << ask(x, y) << '\n';
        }
    }
}