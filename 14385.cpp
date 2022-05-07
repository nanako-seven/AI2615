#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int x; // 增删的代价
    int y; // 修改的代价
    string s1;
    string s2;
    cin >> x >> y;
    cin >> s1 >> s2;
    int n1 = s1.size();
    int n2 = s2.size();
    vector<vector<int>> dp(n1 + 1);
    for (auto& i : dp) {
        i.assign(n2 + 1, 0);
    }
    for (int i = 0; i < n2 + 1; ++i) {
        dp[0][i] = i * x;
    }
    for (int i = 0; i < n1 + 1; ++i) {
        dp[i][0] = i * x;
    }
    for (int i = 1; i < n1 + 1; ++i) {
        for (int j = 1; j < n2 + 1; ++j) {
            int a = dp[i-1][j] + x;
            int b = dp[i][j-1] + x;
            int c = dp[i-1][j-1] + ((s1[i-1] == s2[j-1]) ? 0 : y);
            dp[i][j] = min({a, b, c});
        }
    }
    cout << dp[n1][n2];
    return 0;
}