#include <iostream>
#include <vector>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> seq(n);
    for (int i = 0; i < n; ++i) {
        cin >> seq[i];
    }
    vector<int> dp(n);
    vector<int> last(n);
    dp[0] = 1;
    last[0] = -1;
    for (int i = 1; i < n; ++i) {
        int m = 0;
        int k = -1;
        for (int j = 0; j < i; ++j) {
            if (seq[i] > seq[j] && dp[j] >= m) {
                m = dp[j];
                k = j;
            }
        }
        dp[i] = m + 1;
        last[i] = k;
    }
    int m = dp[0];
    int j = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[i] >= m) {
            m = dp[i];
            j = i;
        }
    }
    cout << dp[j] << endl;
    vector<int> subseq;
    for (int i = j; i != -1; i = last[i]) {
        subseq.push_back(seq[i]);
    }
    for (auto it = subseq.rbegin(); it != subseq.rend(); ++it) {
        cout << *it << ' ';
    }
    return 0;
}