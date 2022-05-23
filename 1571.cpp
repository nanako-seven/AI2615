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
    int n = g.size();
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
    int n; // 顶点个数
    int m; // 有向边数量
    int s; // 源
    int t; // 汇
    cin >> n >> m >> s >> t;
    --s;
    --t;
    Graph<long long> g(n, vector<long long>(n, 0));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u-1][v-1] += w;
    }
    cout << maxFlow(g, s, t);
    return 0;
}