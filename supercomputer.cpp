#include <bits/stdc++.h>

using namespace std;

#define NMAX (int)1e5 + 1

ifstream fin("supercomputer.in");
ofstream fout("supercomputer.out");
vector<int> adj[NMAX];
vector<int> sets;

int toposort(int n, int set) {
    vector<int> degree(n + 1, 0);

    /* Get in-degree for all nodes */
    for (int i = 1; i <= n; ++i)
        for (auto neigh : adj[i])
            ++degree[neigh];

    deque<int> q;
    for (int i = 1; i <= n; i++) {
        /* Enqueue all nodes with in-degree 0, based off their set */
        if (!degree[i]) {
            if (sets[i] == set)
                q.push_front(i);
            else
                q.push_back(i);
        }
    }

    vector<int> toporder;

    while (!q.empty()) {
        /**
         * Pop best element: the node with no more dependencies and set
         * identical with the one of the previous popped element
         */
        int node = q.front();
        q.pop_front();
        toporder.push_back(node);

        for (auto neigh : adj[node]) {
            if (--degree[neigh] == 0) {
                /**
                 * When the in-degree of the neighbour becomes 0, decide
                 * whether to place the node right after its predecesor,
                 * based off its set
                 */
                if (sets[neigh] == sets[toporder.back()])
                    q.push_front(neigh);
                else
                    q.push_back(neigh);
            }
        }
    }

    /* Calculate the context switches between sets */
    int sw = 0;
    for (int i = 1; i < toporder.size(); ++i)
        if (sets[toporder[i]] != sets[toporder[i - 1]])
            ++sw;

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

    fout << min(toposort(n, 1), toposort(n, 2));

    return 0;
}
