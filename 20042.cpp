#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <climits>

using namespace std;

struct S {
    explicit S(int a=0, int b=0) : to(a), weight(b) {}
    int to;
    int weight;
};

struct T {
    explicit T(int a=0, long long b=0) : to(a), dis(b) {}
    int to;
    long long dis;
};

// 把小于号定义成大于，因为C++的优先队列是最大堆
bool operator<(const T& a, const T& b) {
    return a.dis > b.dis;
}

using Graph = vector<vector<S>>;

const long long INF = LLONG_MAX / 2;

long long dijkstra(const Graph& g, int s, int t) {
    int n = (int)g.size();
    deque<bool> ok(n, false); // 这个点的距离确定了吗？
    vector<long long> dis(n, INF); // 目前的最短距离
    priority_queue<T> queue;
    dis[s] = 0;
    ok[s] = true;
    int node = s;
    for (;;) {
        for (const auto& i : g[node]) {
            if (dis[node] + i.weight < dis[i.to]) {
                dis[i.to] = dis[node] + i.weight;
                queue.emplace(i.to, dis[node] + i.weight);
            }
        }
        for (;;) {
            int to = queue.top().to;
            queue.pop();
            if (!ok[to]) {
                node = to;
                break;
            }
        }
        ok[node] = true;
        if (node == t) {
            return dis[node];
        }
    }
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph g(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
    }
    long long dis = dijkstra(g, s, t);
    cout << dis;
    return 0;
}

