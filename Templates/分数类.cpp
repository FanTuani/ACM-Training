#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;

struct P {
    int fm{0}, fz{0};
    P() : fm(0), fz(0) {};
    P(int fm, int fz) : fm(fm), fz(fz) {};
    bool operator<(const P& b) const {
        int lcm = fm * b.fm / __gcd(fm, b.fm);
        return fz * lcm / fm < b.fz * lcm / b.fm;
    }
    P operator+(const P& b) {
        int q = fz * b.fm + fm * b.fz;
        int w = fm * b.fm;
        int g = __gcd(q, w);
        q /= g, w /= g;
        return P(w, q);
    }
} dp[N];