#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<>> heap;
    long long ans = 0;
    int n;
    cin >> n;
    int k;
    cin >> k;
    heap.push(k);
    for (int i = 1; i < n; ++i) {
        cin >> k;
        if (heap.top() < k) {
            ans += k - heap.top();
            heap.pop();
            heap.push(k);
            heap.push(k);
        } else {
            heap.push(k);
        }
    }
    cout << ans;
    return 0;
}