#include <iostream>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

int main() {
    int n, p;
    cin >> n >> p >> p;
    priority_queue<int, vector<int>, greater<>> heap;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        heap.push(k);
    }
    long long s = 0;
    while (heap.size() > 1) {
        int a = heap.top();
        heap.pop();
        int b = heap.top();
        heap.pop();
        s += (a + b) * p;
        heap.push(a + b);
    }
    s = ceil((double) s / 100);
    cout << s;
    return 0;
}