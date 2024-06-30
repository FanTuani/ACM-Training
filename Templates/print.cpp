// __int128 read / print
#include <cstdio>
inline __int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
inline void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
// ST表
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, a[N], lg[N], f[N][32];
void prework() {
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
    }
    for (int i = 1; i < 31; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            f[j][i] = max(f[j][i - 1], f[j + (1 << i - 1)][i - 1]);
        }
    }
}
int query(int l, int r) {
    int len = lg[r - l + 1];
    return max(f[l][len], f[r - (1 << len) + 1][len]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    prework();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
}
// 分块+二分求区间高于某值数量
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, a[N], len[N], st[N], ed[N], bel[N], mark[N], d[N];
void prework() {
    int sq = sqrt(n);
    int dwlen = n / sq;
    for (int i = 1; i <= sq; i++) {
        st[i] = dwlen * (i - 1) + 1;
        ed[i] = i == sq ? n : dwlen * i;
        len[i] = ed[i] - st[i] + 1;
        for (int j = st[i]; j <= ed[i]; j++) {
            a[j] = d[j];
            bel[j] = i;
        }
    }
    for (int i = 1; i <= sq; i++) {
        sort(a + st[i], a + ed[i] + 1);
    }
}
void add(int l, int r, int x) {
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            d[i] += x;
        }
        for (int i = st[bel[l]]; i <= ed[bel[l]]; i++) {
            a[i] = d[i];
        }
        sort(a + st[bel[l]], a + ed[bel[l]] + 1);
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            d[i] += x;
        }
        for (int i = st[bel[l]]; i <= ed[bel[l]]; i++) {
            a[i] = d[i];
        }
        sort(a + st[bel[l]], a + ed[bel[l]] + 1);
        for (int i = st[bel[r]]; i <= r; i++) {
            d[i] += x;
        }
        for (int i = st[bel[r]]; i <= ed[bel[r]]; i++) {
            a[i] = d[i];
        }
        sort(a + st[bel[r]], a + ed[bel[r]] + 1);
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            mark[i] += x;
        }
    }
}
int bs(int l, int r, int x) {  // num of >=x
    while (l <= r) {
        int mid = l + r + 1 >> 1;
        if (a[mid] >= x)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return ed[bel[l]] - r;
}
int query(int l, int r, int x) {
    int ans = 0;
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            if (d[i] + mark[bel[i]] >= x)
                ans++;
        }
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            if (d[i] + mark[bel[i]] >= x)
                ans++;
        }
        for (int i = st[bel[r]]; i <= r; i++) {
            if (d[i] + mark[bel[i]] >= x)
                ans++;
        }
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            ans += bs(st[i], ed[i], x - mark[i]);
        }
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    prework();
    while (q--) {
        char op;
        int l, r, x;
        cin >> op >> l >> r >> x;
        if (op == 'M') {
            add(l, r, x);
        } else {
            cout << query(l, r, x) << '\n';
        }
    }
}
// 分块区间改查
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, a[N], bel[N], sum[N], mark[N], st[N], ed[N], len[N];
void prework() {
    int sq = sqrt(n);    // number of intervals
    int dwlen = n / sq;  // standard interval lenth
    for (int i = 1; i <= sq; i++) {
        st[i] = dwlen * (i - 1) + 1;
        ed[i] = i == sq ? n : dwlen * i;  // the last interval is longer
        len[i] = ed[i] - st[i] + 1;
        for (int j = st[i]; j <= ed[i]; j++) {
            bel[j] = i;
        }
    }
}
void add(int l, int r, int k) {
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            a[i] += k;
            sum[bel[i]] += k;
        }
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            a[i] += k;
            sum[bel[i]] += k;
        }
        for (int i = st[bel[r]]; i <= r; i++) {
            a[i] += k;
            sum[bel[i]] += k;
        }
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            mark[i] += k;
        }
    }
}
int query(int l, int r) {
    int ans = 0;
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            ans += a[i] + mark[bel[i]];
        }
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            ans += a[i] + mark[bel[i]];
        }
        for (int i = st[bel[r]]; i <= r; i++) {
            ans += a[i] + mark[bel[i]];
        }
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            ans += len[i] * mark[i] + sum[i];
        }
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    prework();
    int sq = sqrt(n);
    for (int i = 1; i <= sq; i++) {
        for (int j = st[i]; j <= ed[i]; j++) {
            sum[i] += a[j];
        }
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            add(l, r, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        }
    }
}
// 判重离散化+树状数组求逆序对数
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, a[N], tr[N];
struct P {
    int num, idx;
} b[N];
bool cmp(P q, P w) {
    return q.num < w.num;
}
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
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i].num;
        b[i].idx = i;
    }
    sort(b + 1, b + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        if (b[i].num != b[i - 1].num)
            a[b[i].idx] = i;
        else
            a[b[i].idx] = a[b[i - 1].idx];  // if not unique
    }  // lsh
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        ans += ask(a[i] - 1);
        add(a[i], 1);
    }
    cout << ans;
}
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
// 归并排序求逆序对数
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int T, ans, t[N], a[N];
int rev(int l, int r) {
    if (l == r)
        return 0;
    int mid = l + r >> 1;
    int ans = rev(l, mid) + rev(mid + 1, r);
    int pl = l, pr = mid + 1, idx = l;
    while (pl <= mid and pr <= r) {
        if (a[pl] < a[pr])
            t[idx++] = a[pl++];
        else
            t[idx++] = a[pr++], ans += mid - pl + 1;
    }
    while (pl <= mid)
        t[idx++] = a[pl++];
    while (pr <= r)
        t[idx++] = a[pr++];
    for (int i = l; i <= r; i++)
        a[i] = t[i];
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        cout << rev(1, n) << '\n';
    }
}
// 线段树
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, a[N], tree[4 * N], mark[4 * N];
void build(int l = 1, int r = n, int pos = 1) {
    if (l == r) {
        tree[pos] = a[l];
    } else {
        int mid = (l + r) / 2;
        build(l, mid, pos * 2), build(mid + 1, r, pos * 2 + 1);
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
    }
}
void push_down(int pos, int cl, int cr) {
    int mid = (cl + cr) / 2;
    tree[pos * 2] += (mid - cl + 1) * mark[pos];
    tree[pos * 2 + 1] += (cr - mid) * mark[pos];
    mark[pos * 2] += mark[pos];
    mark[pos * 2 + 1] += mark[pos];
    mark[pos] = 0;
}
void add(int l, int r, int ad, int pos = 1, int cl = 1, int cr = n) {
    if (cl > r or cr < l) {
        return;
    } else if (cl >= l and cr <= r) {
        tree[pos] += (cr - cl + 1) * ad;
        if (cr > cl)
            mark[pos] += ad;
    } else {
        push_down(pos, cl, cr);
        int mid = (cl + cr) / 2;
        add(l, r, ad, pos * 2, cl, mid);
        add(l, r, ad, pos * 2 + 1, mid + 1, cr);
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
    }
}
int query(int l, int r, int pos = 1, int cl = 1, int cr = n) {
    if (cl > r or cr < l) {
        return 0;
    } else if (cl >= l and cr <= r) {
        return tree[pos];
    } else {
        push_down(pos, cl, cr);
        int mid = (cl + cr) / 2;
        return query(l, r, pos * 2, cl, mid) +
               query(l, r, pos * 2 + 1, mid + 1, cr);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build();
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            add(l, r, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        }
    }
}
// 线段树+树剖维护路径子树和
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, root, mod, t[4 * N], mk[4 * N], top[N], hson[N], dep[N], dn[N], a[N],
    fa[N], sz[N], b[N], mxdn[N], cnt;

void build(int l, int r, int pos = 1);
void push_down(int pos, int cl, int cr);
void add(int l, int r, int x, int pos = 1, int cl = 1, int cr = n);
int query(int l, int r, int pos = 1, int cl = 1, int cr = n);
vector<int> con[N];
void dfs(int a, int f) {
    fa[a] = f;
    sz[a] = 1;
    dep[a] = dep[f] + 1;
    int mx = 0;
    for (auto t : con[a]) {
        if (t == f)
            continue;
        dfs(t, a);
        sz[a] += sz[t];
        if (sz[t] > mx) {
            mx = sz[t];
            hson[a] = t;
        }
    }
}
void df(int a) {
    dn[a] = ++cnt;
    if (hson[a]) {
        top[hson[a]] = top[a];
        df(hson[a]);
    }
    for (auto t : con[a]) {
        if (top[t])
            continue;
        top[t] = t;
        df(t);
    }
    mxdn[a] = cnt;
}
void upd_path(int a, int b, int x) {
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]]) {
            add(dn[a], dn[top[a]], x);
            a = fa[top[a]];
        } else {
            add(dn[b], dn[top[b]], x);
            b = fa[top[b]];
        }
    }
    add(dn[a], dn[b], x);
}
int query_path(int a, int b) {
    int ans = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]]) {
            ans += query(dn[a], dn[top[a]]);
            a = fa[top[a]];
        } else {
            ans += query(dn[b], dn[top[b]]);
            b = fa[top[b]];
        }
    }
    return ans + query(dn[a], dn[b]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q >> root >> mod;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        con[f].push_back(t);
        con[t].push_back(f);
    }
    dfs(root, root);
    top[root] = root;
    df(root);
    for (int i = 1; i <= n; i++) {
        a[dn[i]] = b[i];
    }
    build(1, n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int f, t, x;
            cin >> f >> t >> x;
            upd_path(f, t, x);
        } else if (op == 2) {
            int f, t;
            cin >> f >> t;
            cout << query_path(f, t) % mod << '\n';
        } else if (op == 3) {
            int s, x;
            cin >> s >> x;
            add(dn[s], mxdn[s], x);
        } else {
            int s;
            cin >> s;
            cout << query(dn[s], mxdn[s]) % mod << '\n';
        }
    }
}

void build(int l, int r, int pos) {
    if (l == r) {
        t[pos] = a[l];
    } else {
        int mid = l + r >> 1;
        build(l, mid, pos * 2), build(mid + 1, r, pos * 2 + 1);
        t[pos] = t[pos * 2] + t[pos * 2 + 1];
    }
}
void push_down(int pos, int cl, int cr) {
    int mid = cl + cr >> 1;
    mk[pos * 2] += mk[pos];
    mk[pos * 2 + 1] += mk[pos];
    t[pos * 2] += (mid - cl + 1) * mk[pos];
    t[pos * 2 + 1] += (cr - mid) * mk[pos];
    mk[pos] = 0;
}
void add(int l, int r, int x, int pos, int cl, int cr) {
    if (l > r)
        swap(l, r);
    if (cr < l or cl > r) {
        return;
    } else if (cl >= l and cr <= r) {
        t[pos] += (cr - cl + 1) * x;
        if (cr > cl)
            mk[pos] += x;
    } else {
        int mid = cl + cr >> 1;
        push_down(pos, cl, cr);
        add(l, r, x, pos * 2, cl, mid), add(l, r, x, pos * 2 + 1, mid + 1, cr);
        t[pos] = t[pos * 2] + t[pos * 2 + 1];
    }
}
int query(int l, int r, int pos, int cl, int cr) {
    if (l > r)
        swap(l, r);
    if (cr < l or cl > r) {
        return 0;
    } else if (cl >= l and cr <= r) {
        return t[pos];
    } else {
        int mid = cl + cr >> 1;
        push_down(pos, cl, cr);
        return query(l, r, pos * 2, cl, mid) +
               query(l, r, pos * 2 + 1, mid + 1, cr);
    }
}
// 重链剖分求LCA
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10, INF = 0x3f3f3f3f3f3f3f;
vector<int> con[N];
int dep[N], hson[N], fa[N], sz[N], top[N];
void dfs(int a, int f) {
    fa[a] = f;
    sz[a] = 1;
    dep[a] = dep[f] + 1;
    int mx = 0;
    for (int t : con[a]) {
        if (t == f)
            continue;
        dfs(t, a);
        sz[a] += sz[t];
        if (sz[t] > mx) {
            mx = sz[t];
            hson[a] = t;
        }
    }
}
void df(int a) {
    for (int t : con[a]) {
        if (t == fa[a])
            continue;
        if (t == hson[a])  // top[t] = hson[a] == t ? top[a] : t;
            top[t] = top[a];
        else
            top[t] = t;
        df(t);
    }
}
int lca(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]])
            a = fa[top[a]];
        else
            b = fa[top[b]];
    }
    if (dep[a] > dep[b])
        return b;
    else
        return a;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q, s;
    cin >> n >> q >> s;
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        con[f].push_back(t);
        con[t].push_back(f);
    }
    dfs(s, s);
    top[s] = s;
    df(s);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
}
// 质数筛
bool isnp[MAXN];
vector<int> primes;  // 质数表
void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!isnp[i])
            primes.push_back(i);
        for (int p : primes) {
            if (p * i > n)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}
// 三分
while (r - l > eps) {
    mid = (l + r) / 2;
    double fl = f(mid - eps), fr = f(mid + eps);
    if (fl < fr)
        l = mid;  // 这里不写成mid -
                  // eps，防止死循环；可能会错过极值，但在误差范围以内所以没关系
    else
        r = mid;
}
// 拓扑排序
// deg是入度，在存图的时候需要录入数据
// A是排序后的数组
int deg[MAXN], A[MAXN];
bool toposort(int n) {
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        A[cnt++] = t;
        for (auto to : edges[t]) {
            deg[to]--;
            if (deg[to] == 0)  // 出现了新的入度为0的点
                q.push(to);
        }
    }
    return cnt == n;
}
// Tricks
// # n个数两两之积的和

// (和的平方 - 平方之和) / 2

// # 位运算变形

// - a+b == a^b + 2*(a&b)
// - a+b == a|b + a&b
// - a^b == a|b - a&b
  
// # 异或运算的性质

// 1. 交换律

// 2. 结合律（即`(a^b)^c == a^(b^c)`）

// 3. `x^x=0`，`x^0=x`

// 4. **自反性 `A xor B xor B = A xor 0 = A`**

// # log2(1e9) < 30