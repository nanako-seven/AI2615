#include <iostream>

using namespace std;

const int MAX_N = 1000000 + 10;

struct S {
    int val;
    int n;
};

S temp[MAX_N];

void merge(S a[], int n, int m) {
    int i = 0;
    int j = m;
    while (i < m) {
        if (j == n || a[i].val < a[j].val)  {
            a[i].n += j - m;
            ++i;
        } else {
            ++j;
        }
    }
    i = m - 1;
    j = n - 1;
    while (j >= m) {
        if (i == -1 || a[i].val < a[j].val)  {
            a[j].n += m - i - 1;
            --j;
        } else {
            --i;
        }
    }

    i = 0;
    j = m;
    int k = 0;
    while (k < n) {
        if (i == m) {
            temp[k] = a[j];
            ++j;
        } else if (j == n) {
            temp[k] = a[i];
            ++i;
        } else if (a[i].val > a[j].val) {
            temp[k] = a[j];
            ++j;
        } else {
            temp[k] = a[i];
            ++i;
        }
        ++k;
    }
    for (i = 0; i < n; ++i) {
        a[i] = temp[i];
    }
}

S input[MAX_N];

void countSwap(S a[], int n) {
    if (n <= 1) {
        return;
    }
    int mid = n / 2;
    countSwap(a, mid);
    countSwap(a + mid, n - mid);
    merge(a, n, mid);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        input[i].val = m;
        input[i].n = 0;
    }
    countSwap(input, n);
    for (int i = 0; i < n; ++i) {
        cout << input[i].n << ' ';
    }
    return 0;
}
