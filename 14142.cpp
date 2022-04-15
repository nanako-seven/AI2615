#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <utility>

using namespace std;


// 数据结构课上自己写的并查集
class DisjointSet {
private:
    vector<int> parent;
public:
    explicit DisjointSet(int size_) : parent(size_, -1) {}
    void merge(int x1, int x2) {
        auto r1 = find(x1);
        auto r2 = find(x2);
        if (r1 == r2) {
            return;
        }
        if (parent[r1] > parent[r2]) {
            parent[r2] += parent[r1];
            parent[r1] = r2;
        } else {
            parent[r1] += parent[r2];
            parent[r2] = r1;
        }
    }
    int find(int x) {
        if (parent[x] < 0) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
};

struct S {
    explicit S(int a=0, int b=0, int c=0) {
        u = a;
        v = b;
        weight = c;
    }
    int u;
    int v;
    int weight;
};

struct T {
    explicit T(int a=0, int b=0) {
        to = a;
        weight = b;
    }
    int to;
    int weight;
};

const int SIZE = 1000000;

// Tarjan算法的实现参考了 https://zhuanlan.zhihu.com/p/101923309
class Tarjan {
private:
    int size;
    vector<int> head;
    vector<int> ver;
    vector<int> nxt;
    vector<int> dfn;
    vector<int> low;
    int tot = 1;
    int num = 0;
    deque<bool> bridge;

    void tarjan_(int x, int in_edge) {
        dfn[x] = low[x] = ++num;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if (!dfn[y]) {
                tarjan_(y, i);
                low[x] = min(low[x], low[y]);
                if (low[y] > dfn[x]) {
                    bridge[i] = bridge[i ^ 1] = true;
                }
            }
            else if (i != (in_edge ^ 1)) {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }
    static int get(const vector<vector<T>>& v, int m, int n) {
        for (const auto& i : v[m]) {
            if (i.to == n) {
                return i.weight;
            }
        }
    }
public:
//    explicit Tarjan(int size_) : head(size_ + 10, 0), ver(size_ * 2 + 10, 0),
//                                 nxt(size_ * 2 + 10, 0), dfn(size_ + 10, 0), low(size_ + 10, 0),
//                                 bridge(size_ * 2 + 10, false), size(size_) {}
    explicit Tarjan(int size_) : head(SIZE, 0), ver(SIZE, 0),
                                 nxt(SIZE, 0), dfn(SIZE, 0), low(SIZE, 0),
                                 bridge(SIZE, false), size(size_) {}
    void add(int x, int y) {
        ver[++tot] = y;
        nxt[tot] = head[x];
        head[x] = tot;
    }

    // weights1: 电缆；weights2: 无线
    long long tarjan(const vector<vector<T>>& weights1, const vector<vector<T>>& weights2) {
        for (int i = 1; i <= size; i++) {
            if (!dfn[i]) {
                tarjan_(i, 0);
            }
        }
        long long s = 0;
        for (int i = 2; i < tot; i += 2) {
            if (bridge[i]) {
                int a = ver[i];
                int b = ver[i ^ 1];
                int m, n;
                if (a < b) {
                    m = a;
                    n = b;
                } else {
                    m = b;
                    n = a;
                }
                s -= get(weights1, m, n);
                s += get(weights2, m, n);
            }
        }
        return s;
    }
};



bool operator<(const S& a, const S& b) {
    return a.weight < b.weight;
}

long long kruskal(vector<S> &edges, int nodes) {
    long long s = 0;
    DisjointSet ds(nodes + 10);
    sort(edges.begin(), edges.end());
    int n = 0;
    for (const auto& i : edges) {
        if (ds.find(i.u) != ds.find(i.v)) {
            ++n;
            s += i.weight;
            if (n == nodes - 1) {
                break;
            }
            ds.merge(i.u, i.v);
        }
    }
    return s;
}


int main() {
    vector<S> edges;
    int n, m;
    cin >> n >> m;
    vector<vector<T>> weights1(n + 1);
    vector<vector<T>> weights2(n + 1);
    Tarjan t(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        t.add(a, b);
        t.add(b, a);
        if (a > b) {
            swap(a, b);
        }
        weights1[a].emplace_back(b, c);
        weights2[a].emplace_back(b, d);
        edges.emplace_back(a, b, c);
    }
    long long s = kruskal(edges, n);
    s += t.tarjan(weights1, weights2);
    cout << s;
    return 0;
}


