#include <iostream>
#include <vector>
#include <deque>


using namespace std;

struct S {
    explicit S(int a=0, int b=0) : to(a), weight(b) {}
    int to;
    int weight;
};

using Graph = vector<vector<S>>;

int shortestDis(const Graph& g, int s, int t) {
    deque<bool> visited(g.size(), false);
    deque<int> queue;
    vector<int> dis(g.size(), 0x3f000000);
    dis[s] = 0;
    visited[s] = true;
    queue.push_back(s);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (const auto& i : g[u]) {
            int v = i.to;
            int w = i.weight;
            if (!visited[v] || dis[v] > dis[u] + w) {
                visited[v] = true;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                }
                if (w) {
                    queue.push_back(v);
                } else {
                    queue.push_front(v);
                }
            }
        }
    }
    return dis[t];
}

int main() {
    int n; // 点数
    int m; // 边数
    int s, t; // s -> t

    cin >> n >> m >> s >> t;

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a-1].emplace_back(b-1, c);
        g[b-1].emplace_back(a-1, c);
    }
    cout << shortestDis(g, s-1, t-1);
    return 0;
}