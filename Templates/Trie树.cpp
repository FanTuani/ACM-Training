// Trie
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, con[N][26], cnt;
bool vis[N];
void add(string a) {
    int cur = 1;
    for (int c : a) {
        c -= 'a';
        if (!con[cur][c])
            con[cur][c] = ++cnt;
        cur = con[cur][c];
    }
}
bool ask(string a) {
    int cur = 1;
    for (int c : a) {
        c -= 'a';
        if (!con[cur][c])
            return false;
        cur = con[cur][c];
    }
    return true;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    while (n--) {
        string a;
        cin >> a;
        add(a);
    }
    cin >> q;
    set<string> s;
    while (q--) {
        string a;
        cin >> a;
		if (ask(a)) {
            cout << "OK\n";
        } else {
            cout << "NO PREFIX\n";
        }
    }
}