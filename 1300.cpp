#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int f(int a[], int n) {
    int i = 0;
    int j = n-1;
    int pivot = a[0];
    while (i < j) {
        while (i < j && a[j] >= pivot) {
            --j;
        }
        if (i < j) {
            a[i] = a[j];
            ++i;
        }
        while (i < j && a[i] < pivot) {
            ++i;
        }
        if (i < j) {
            a[j] = a[i];
            --j;
        }
    }
    a[i] = pivot;
    return i;
}

int kMin(int a[], int n, int k) {
    for (;;) {
        int r = rand() % n;
        swap(a[r], a[0]);
        int m = f(a, n);
        if (m > k) {
            n = m;
        } else if (m < k) {
            n -= m + 1;
            a += m + 1;
            k -= m + 1;
        } else {
            return a[m];
        }
    }
}

const int N = 4e7 + 1;
int n, k;
int a[N];

void read_input_data() {
    int m;
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    unsigned int z = a[m];
    for (int i = m + 1; i <= n; i++) {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}

int main() {
    srand(time(nullptr));
    read_input_data();
    cout << kMin(a + 1, n, k - 1);
    return 0;
}