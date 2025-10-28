// 组合数
int mod = 998244353;

int cres[67][67];
int C(int n, int m) {
    if (m == 0 || m == n)
        return 1;
    if (cres[n][m])
        return cres[n][m] % mod;
    return cres[n][m] = (C(n - 1, m) + C(n - 1, m - 1)) % mod;
}