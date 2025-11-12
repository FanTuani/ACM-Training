int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int g = exgcd(b, a % b, x, y);
    x = y;
    y = (g - a * x) / b;
    return g;
}