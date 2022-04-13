// 这段代码部分参考了 https://blog.csdn.net/flyzer/article/details/97126393

#include <iostream>
#include <cmath>

using namespace std;

constexpr int MAX_N = 1000000;
const double PI = acos(-1);

class Complex {
public:
    Complex() noexcept: Complex(0, 0) {}

    Complex(double re_, double im_) {
        re = re_;
        im = im_;
    }

    Complex operator+(const Complex& c) const {
        return {c.re + re, c.im + im};
    }

    Complex operator-(const Complex& c) const {
        return {re - c.re, im - c.im};
    }

    Complex operator*(const Complex& c) const {
        return {c.re * re - c.im * im, c.re * im + c.im * re};
    }

    double re;
    double im;
};


void fft(Complex a[], int n, int b, const int c[]) {
    for (int i = 0; i < n; ++i) {
        if (i < c[i]) {
            swap(a[i], a[c[i]]);
        }
    }
    for (int i = 1; i < n; i *= 2) {
        Complex wn(cos(PI / i), b * sin(PI / i));
        for (int j = 0; j < n; j += i * 2) {
            Complex w(1, 0);
            for (int k = 0; k < i; ++k) {
                Complex x = a[j + k];
                Complex y = w * a[j + k + i];
                a[j + k] = x + y;
                a[j + k + i] = x - y;
                w = w * wn;
            }
        }
    }
}


Complex a[MAX_N];
Complex b[MAX_N];
int c[MAX_N];


int main() {
    int n;
    int m;
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        int p;
        cin >> p;
        a[i] = Complex(p, 0);
    }
    for (int i = 0; i <= m; ++i) {
        int p;
        cin >> p;
        b[i] = Complex(p, 0);
    }
    m += n;
    int p = 0;
    for (n = 1; n <= m; n *= 2) {
        ++p;
    }
    for (int i = 0; i < n; ++i) {
        c[i] = (c[i / 2] / 2) | ((i & 1) << (p - 1));
    }
    fft(a, n, 1, c);
    fft(b, n, 1, c);
    for (int i = 0; i <= n; ++i) {
        a[i] = a[i] * b[i];
    }
    fft(a, n, -1, c);
    for (int i = 0; i <= m; ++i) {
        cout << lround(a[i].re / n) << ' ';
    }
    return 0;
}

