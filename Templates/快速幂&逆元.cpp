int ksm(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
            b--;
        }
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}
int inv(int a, int mod) { // a / b == a * inv(b)
    return ksm(a, mod - 2, mod);
}