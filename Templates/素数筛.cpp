bool isnp[N];
vector<int> pri;  // 质数表
void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!isnp[i])
            pri.push_back(i);
        for (int p : pri) {
            if (p * i > n)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}