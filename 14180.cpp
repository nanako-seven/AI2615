#include <iostream>
#include <vector>


using namespace std;


using Graph = vector<vector<int>>;

vector<int> topo(const Graph& g, vector<int>& inDegree) {
    vector<int> zero;
    int n = g.size();
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) {
            zero.push_back(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        int u = zero.back();
        order[u] = i;
        zero.pop_back();
        for (int v : g[u]) {
            --inDegree[v];
            if (inDegree[v] == 0) {
                zero.push_back(v);
            }
        }
    }
    return order;
}

int main() {
    int n; // 点数
    int p1; // 有向边数
    int p2; // 无向边数

    cin >> n >> p1 >> p2;
    Graph g(n);
    vector<int> inDegree(n, 0);
    for (int i = 0; i < p1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
        ++inDegree[b-1];
    }
    vector<int> order = topo(g, inDegree);
    for (int i = 0; i < p2; ++i) {
        int a, b;
        cin >> a >> b;
        if (order[a-1] < order[b-1]) {
            cout << a << ' ' << b << endl;
        } else {
            cout << b << ' ' << a << endl;
        }
    }
    return 0;
}