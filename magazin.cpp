#include <bits/stdc++.h>

using namespace std;

#define NMAX (int)1e5 + 1

ifstream fin("magazin.in");
ofstream fout("magazin.out");
vector<int> adj[NMAX];
vector<int> nodesSubTree;
vector<bool> visited;
vector<int> traversal;
map<int, int> pos;

void dfs(int node) {
    /**
     * Count the number of the nodes in the current subtree;
     * ignore the parent node
     */
    nodesSubTree[node] = 0;
    visited[node] = true;
    /* Save the node in the traversal array */
    traversal.push_back(node);
    /* Save the position of the node in the traversal array */
    pos[node] = traversal.size() - 1;

    for (auto &neigh : adj[node]) {
        if (!visited[neigh]) {
            dfs(neigh);

            /**
             * Add number of nodes in children subtrees
             * to the parent nodesSubTree value
             */
            nodesSubTree[node] += 1 + nodesSubTree[neigh];
        }
    }
}

void task(int q) {
    nodesSubTree = vector<int>(NMAX);
    visited = vector<bool>(NMAX, false);
    traversal = vector<int>();

    dfs(1);

    int d, e;
    for (int i = 0; i < q; ++i) {
        fin >> d >> e;

        /* If there are plenty of nodes in the requested subtree */
        if (nodesSubTree[d] >= e)
            /* Print the value from the traversal array */
            fout << traversal[pos[d] + e] << "\n";
        else
            fout << -1 << "\n";
    }
}

int main() {
    int n, q;
    fin >> n >> q;

    int x;
    for (int i = 2; i <= n; ++i) {
        fin >> x;
        adj[x].push_back(i);
    }

    task(q);

    return 0;
}
