#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


template <typename T>
using Graph = vector<vector<T>>;

vector<int> bfs(const Graph<long long>& g, int s, int t) {
    int n = g.size();
    vector<int> last(n, -1);
    vector<int> visited(n, false);
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t) {
            break;
        }
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (visited[v]) {
                continue;
            }
            if (g[u][v]) {
                q.push(v);
                last[v] = u;
            }
        }
    }
    return last;
}

long long maxFlow(const Graph<long long>& g, int s, int t) {
    long long ans = 0;
    Graph<long long> r(g);
    for (;;) {
        vector<int> path = bfs(r, s, t);
        // 如果找不到增广路径
        if (path[t] == -1) {
            break;
        }
        int v = t;
        long long m = LLONG_MAX;
        for (;;) {
            int u = path[v];
            if (u == -1) {
                break;
            }
            m = r[u][v] < m ? r[u][v] : m;
            v = u;
        }
        v = t;
        for (;;) {
            int u = path[v];
            if (u == -1) {
                break;
            }
            r[u][v] -= m;
            r[v][u] += m;
            v = u;
        }
        ans += m;
    }
    return ans;
}


int main() {
    int m; // 猪圈数量
    int n; // 顾客数量
    cin >> m >> n;
    auto i_hogpen = [&](int i){
        return i;
    };
    auto i_customer = [&](int i){
        return i + m;
    };
    int s = m + n; // 源
    int t = s + 1; // 汇
    Graph<long long> g(m+n+2, vector<long long>(m+n+2, 0));
    for (int i = 0; i < m; ++i) {
        cin >> g[s][i_hogpen(i)];
    }
    vector<int> lastPurchase(m, -1);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        // 这里用并查集会更快
        for (int j = 0; j < a; ++j) {
            int k;
            cin >> k;
            --k;
            if (lastPurchase[k] != -1) {
                g[i_customer(lastPurchase[k])][i_customer(i)] = LLONG_MAX;
            } else {
                g[i_hogpen(k)][i_customer(i)] = LLONG_MAX;
            }
            lastPurchase[k] = i;
        }
        cin >> g[i_customer(i)][t];
    }
    cout << maxFlow(g, s, t);
    return 0;
}