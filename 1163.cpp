#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

const long long MOD = 1e9 + 7;


int m, n, k, n_pow;
bool broken[200][6];
long long dp1[64][64];
long long dp2[64][64];

int column_to_index(const vector<int>& col) {
    int j = 0;
    for (int i = n - 1; i >= 0; --i) {
        j <<= 1;
        j += col[i];
    }
    return j;
}

vector<int> index_to_column(int i) {
    vector<int> col;
    for (int j = 0; j < n; ++j) {
        col.push_back(i % 2);
        i >>= 1;
    }
    return col;
}

void _valid_methods(vector<int>& v, const vector<int>& ok, int i, vector<int>& temp) {
    if (i == n) {
        v.push_back(column_to_index(temp));
        return;
    }
    temp[i] = 0;
    _valid_methods(v, ok, i+1, temp);
    if (ok[i]) {
        temp[i] = 1;
        _valid_methods(v, ok, i+1, temp);
    }
}

vector<int> valid_methods(int m3, const vector<int>& col1, const vector<int>& col2) {
    vector<int> col3_ok(n, 1);
    for (int i = 0; i < n; ++i) {
        if (col1[i]) {
            if (i - 1 >= 0) {
                col3_ok[i - 1] = 0;
            }
            if (i + 1 < n) {
                col3_ok[i + 1] = 0;
            }
        }
        if (col2[i]) {
            if (i - 2 >= 0) {
                col3_ok[i - 2] = 0;
            }
            if (i + 2 < n) {
                col3_ok[i + 2] = 0;
            }
        }
        if (broken[m3][i]) {
            col3_ok[i] = 0;
        }
    }
    vector<int> v;
    vector<int> temp(n);
    _valid_methods(v, col3_ok, 0, temp);
    return v;
}

int main() {
    cin >> m >> n >> k;
    n_pow = pow(2, n);
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        broken[a-1][b-1] = true;
    }
    dp1[0][0] = 1;
    for (int m3 = 0; m3 < m; ++m3) {
        for (int i = 0; i < n_pow; ++i) {
            for (int j = 0; j < n_pow; ++j) {
                    dp2[i][j] = 0;
            }
        }
        for (int i = 0; i < n_pow; ++i) {
            for (int j = 0; j < n_pow; ++j) {
                vector<int> col1 = index_to_column(i);
                vector<int> col2 = index_to_column(j);
                vector<int> v = valid_methods(m3, col1, col2);
                for (int k : v) {
                    dp2[j][k] += dp1[i][j];
                    dp2[j][k] %= MOD;
                }
            }
        }
        for (int i = 0; i < n_pow; ++i) {
            for (int j = 0; j < n_pow; ++j) {
                dp1[i][j] = dp2[i][j];
            }
        }
    }
    long long s = 0;
    for (int i = 0; i < n_pow; ++i) {
        for (int j = 0; j < n_pow; ++j) {
            s += dp1[i][j];
            s %= MOD;
        }
    }
    cout << s;
    return 0;
}