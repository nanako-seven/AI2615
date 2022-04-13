#include <iostream>
#include <vector>

using namespace std;

using Graph = vector<vector<int>>;

vector<int> visited1;
vector<int> visited2;
vector<int> visited3;
vector<int> finishOrder;
Graph g1; // 原图
Graph g2; // 反向图
int numNodes;
int id;

// 返回按完成时间从小到大排序的顶点编号
void dfs1(int u) {
    visited1[u] = 1;
    for (int v : g1[u]) {
        if (!visited1[v]) {
            dfs1(v);
        }
    }
    finishOrder.push_back(u);
}

void dfs2(int u) {
    visited2[u] = id;
    ++numNodes;
    for (int v : g2[u]) {
        if (!visited2[v]) {
            dfs2(v);
        }
    }
}

bool dfs3(int u) {
    visited3[u] = 1;
    for (int v : g1[u]) {
        if (visited2[v] != id) {
            return true;
        } else {
            if (!visited3[v]) {
                if (dfs3(v)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int calc() {
    int count = 0;
    for (;;) {
        bool flag = true;
        for (int i = 0; i < visited1.size(); ++i) {
            if (visited1[i] == 0) {
                dfs1(i);
                flag = false;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    id = 1;
    while (!finishOrder.empty()) {
        int u = finishOrder.back();
        finishOrder.pop_back();
        if (visited2[u]) {
            continue;
        }
        numNodes = 0;
        dfs2(u);
        for (int& i : visited3) {
            i = 0;
        }
        if (dfs3(u)) {
            count += numNodes;
        }
        ++id;
    }
    return count;
}

int main() {
    int n; // 顶点数
    int m; // 边数
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        visited1.push_back(0);
        visited2.push_back(0);
        visited3.push_back(0);
        g1.emplace_back();
        g2.emplace_back();
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g1[a-1].push_back(b-1);
        g2[b-1].push_back(a-1);
    }
    cout << calc();
    return 0;
}