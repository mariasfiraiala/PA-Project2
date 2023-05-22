#include <bits/stdc++.h>

using namespace std;

#define NMAX 100001

ifstream fin("supercomputer.in");
ofstream fout("supercomputer.out");
vector<int> adj[NMAX];
vector<int> sets;

int toposort(int n, int set) {
    vector<int> degree(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (auto neigh : adj[i])
            ++degree[neigh];
    }

    deque<int> q;
    for (int i = 1; i <= n; i++)
        if (!degree[i]) {
            if (sets[i] == set)
                q.push_front(i);
            else
                q.push_back(i);
        }

    vector<int> toporder;

    while (!q.empty()) {
        int node = q.front();
        q.pop_front();
        toporder.push_back(node);

        for (auto neigh : adj[node]) {
            if (--degree[neigh] == 0) {
                if (sets[neigh] == sets[toporder.back()])
                    q.push_front(neigh);
                else
                    q.push_back(neigh);
            }
        }
    }

    // cerr << "topo size: " << toporder.size() << "\n";

    int sw = 0;
    for (int i = 1; i < toporder.size(); ++i)
        if (sets[toporder[i]] != sets[toporder[i - 1]])
            ++sw;

    // for (int i = 0; i < toporder.size(); ++i) {
    //     cerr << sets[toporder[i]] << " " << toporder[i] << "\n";
    // }

    // cerr << sw << "\n\n";

    return sw;
}

int main() {
    int n, m;
    fin >> n >> m;

    sets = vector<int>(n + 1);
    for (int i = 1; i <= n; ++i) {
        fin >> sets[i];
    }

    int x, y;
    for (int i = 0; i < m; ++i) {
        fin >> x >> y;
        adj[x].push_back(y);
    }

    // for (int i = 1; i <= n; ++i) {
    //     cerr << "node " << i << " ";
    //     for (auto node : adj[i])
    //         cerr << node << " ";
    //     cerr << "\n";
    // }

    fout << min(toposort(n, 1), toposort(n, 2));
    return 0;
}
