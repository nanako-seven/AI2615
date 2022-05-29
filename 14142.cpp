#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

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

// Tarjan算法的实现参考了 https://zhuanlan.zhihu.com/p/101923309 的思路
class Tarjan {
private:
    int size;
    vector<int> head;
    vector<int> node;
    vector<int> next;
    vector<int> mark1;
    vector<int> mark2;
    int max_node = 1;
    int mark = 0;
    deque<bool> bridge;

    static int another_node(int i) {
        return i ^ 1;
    }

    void tarjan_(int u, int e_in) {
        ++mark;
        mark1[u] = mark;
        mark2[u] = mark;
        for (int i = head[u]; i; i = next[i]) {
            int v = node[i];
            if (!mark1[v]) {
                tarjan_(v, i);
                if (mark2[v] < mark2[u]) {
                    mark2[u] = mark2[v];
                }
                if (mark2[v] > mark1[u]) {
                    bridge[i] = true;
                    bridge[another_node(i)] = true;
                }
            }
            if (i != another_node(e_in)) {
                if (mark2[v] < mark2[u]) {
                    mark2[u] = mark2[v];
                }
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
//    explicit Tarjan(int size_) : head(size_ + 10, 0), node(size_ * 2 + 10, 0),
//                                 next(size_ * 2 + 10, 0), mark1(size_ + 10, 0), mark2(size_ + 10, 0),
//                                 bridge(size_ * 2 + 10, false), size(size_) {}
    explicit Tarjan(int size_) : head(SIZE, 0), node(SIZE, 0),
                                 next(SIZE, 0), mark1(SIZE, 0), mark2(SIZE, 0),
                                 bridge(SIZE, false), size(size_) {}
    void add(int x, int y) {
        node[++max_node] = y;
        next[max_node] = head[x];
        head[x] = max_node;
    }

    // weights1: 电缆；weights2: 无线
    long long tarjan(const vector<vector<T>>& weights1, const vector<vector<T>>& weights2) {
        for (int i = 1; i <= size; i++) {
            if (!mark1[i]) {
                tarjan_(i, 0);
            }
        }
        long long s = 0;
        for (int i = 2; i < max_node; i += 2) {
            if (bridge[i]) {
                int a = node[i];
                int b = node[i ^ 1];
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


