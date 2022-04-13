#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    explicit Edge(int a=0, int b=0, int c=0) : from(a), to(b), weight(c) {}
    int from;
    int to;
    int weight;
};

using Graph = vector<Edge>;

// 有负环返回true
bool bellmanFord(const Graph& g, int n) {
    vector<int> dis(n, 0x3f000000);
    dis[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (const auto& e : g) {
            if (dis[e.to] > dis[e.from] + e.weight) {
                dis[e.to] = dis[e.from] + e.weight;
            }
        }
    }
    for (const auto& e : g) {
        if (dis[e.to] > dis[e.from] + e.weight) {
            return true;
        }
    }
    return false;
}

int main() {
    int n; // 点数
    int m; // 边数
    cin >> n >> m;
    Graph g(m);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g.emplace_back(a-1, b-1, c);
    }
    if (bellmanFord(g, n)) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}