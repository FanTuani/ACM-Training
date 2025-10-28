// 树状数组
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, m, tr[N];
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int x) {
    while (pos <= n) {
        tr[pos] += x;
        pos += lowbit(pos);
    }
}
int ask(int pos) {
    int ans = 0;
    while (pos) {
        ans += tr[pos];
        pos -= lowbit(pos);
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        add(i, t);
    }
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, k;
            cin >> x >> k;
            add(x, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << ask(r) - ask(l - 1) << '\n';
        }
    }
}