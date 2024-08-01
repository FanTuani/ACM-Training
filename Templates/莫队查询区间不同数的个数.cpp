// 莫队查询区间不同数的个数 P3901
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int a[N], n, q, bel[N];
struct Q {
    int l, r, idx;
    Q(int l, int r, int idx) : l(l), r(r), idx(idx) {};
    Q() : l(0), r(0), idx(0) {};
    bool operator<(const Q& b) const {
        if (bel[l] != bel[b.l])
            return bel[l] < bel[b.l];
        if (bel[l] % 2 == 1)
            return bel[r] > bel[b.r];
        return bel[r] < bel[b.r];
    }
};
void prework() {
    int sq = sqrt(n);
    for (int i = 0; i < sq; i++) {
        for (int j = 1; j <= sq; j++) {
            bel[i * sq + j] = i + 1;
        }
    }
    for (int i = sq * sq + 1; i <= n; i++) {
        bel[i] = sq;
    }
}
int ans = 0, buc[N], out[N];
void add(int x) {
    if (!buc[a[x]])
        ans++;
    buc[a[x]]++;
}
void del(int x) {
    buc[a[x]]--;
    if (!buc[a[x]])
        ans--;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    prework();
    vector<Q> qs;
    int cnt = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;
        qs.push_back(Q(l, r, ++cnt));
    }
    sort(qs.begin(), qs.end());
    int l = 0, r = 0;
    for (auto [L, R, idx] : qs) {
        while (l < L) {
            del(l++);
        }
        while (l > L) {
            add(--l);
        }
        while (r < R) {
            add(++r);
        }
        while (r > R) {
            del(r--);
        }
        if (ans < R - L + 1) {
            out[idx] = 0;
        } else {
            out[idx] = 1;
        }
    }
    for (int i = 1; i <= cnt; i++) {
        if (out[i])
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}