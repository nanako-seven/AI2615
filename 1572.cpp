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

Graph<long long> generateGraph(const vector<vector<int>>& broken) {
    int a = broken.size();
    int b = broken[0].size();
    int b_fake = b % 2 ? b : b + 1; // 假装列是奇数，这样所有白色格子都是偶数
    int n = a * b_fake;
    Graph<long long> g(n + 2, vector<long long>(n + 2, 0)); // 加上源和汇
    int s = n;
    int t = n + 1;
    int n_white = 0;
    int n_black = 0;
    for (int i = 0; i < n; i += 2) {
        int x = i / b_fake;
        int y = i % b_fake;
        if (y < b && !broken[x][y]) {
            g[s][i] = 1;
            ++n_white;
        }
    }
    for (int i = 1; i < n; i += 2) {
        int x = i / b_fake;
        int y = i % b_fake;
        if (y < b && !broken[x][y]) {
            g[i][t] = 1;
            ++n_black;
        }
    }
    if (n_white != n_black) {
        return g;
    }
    auto isValid = [&] (int x, int y) {
        return x >= 0 && x < a && y >= 0 && y < b && !broken[x][y];
    };
    auto index = [&] (int x, int y) {
        return x * b_fake + y;
    };
    auto addEdge = [&] (int i, int x, int y) {
        if (isValid(x, y)) {
            g[i][index(x, y)] = LLONG_MAX;
        }
    };
    for (int i = 0; i < n; i += 2) {
        int x = i / b_fake;
        int y = i % b_fake;
        addEdge(i, x, y+1);
        addEdge(i, x, y-1);
        addEdge(i, x+1, y);
        addEdge(i, x-1, y);
    }
    return g;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int n; // 第一个维度
        int m; // 第二个维度
        int k;
        cin >> n >> m >> k;
        vector<vector<int>> broken(n, vector<int>(m, false));
        for (int j = 0; j < k; ++j) {
            int x, y;
            cin >> x >> y;
            broken[x-1][y-1] = true;
        }
        auto g = generateGraph(broken);
        int w = g.size();
        auto f = maxFlow(g, w-2, w-1);
        if (f * 2 == n * m - k) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}