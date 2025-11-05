// 三分 P1883
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10, INF = 0x3f3f3f3f3f3f3f;
const double eps = 1e-15;
int n;
double a[N], b[N], c[N];
double f(double x) {
    double mx = -1e9;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, a[i] * x * x + b[i] * x + c[i]);
    }
    return mx;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    double l = 0, r = 1000, mid;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (f(mid - eps) > f(mid + eps)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << fixed << setprecision(4) << f(l) << '\n';
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}