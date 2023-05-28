Copyright 2023 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)

# Gigel, Always Busy - Project2

### `supercomputer.cpp`

#### Description

The task can be boiled down to computing Kahn's topological sort order with a twist: every two consecutive nodes in the final array must differ as little as possible when it comes to their assigned set (a binary flag):

1. Having two different values for the set flag, we compute the topological sort twice, once for when we start with nodes with the set flag 1, and one for when we start with nodes with the set flag 2.

1. This way, we make sure that we compute the number of "context switches" for all cases and we decide the minimum value as accurately as possible.

1. The modified topological sort algorithm:

   * uses a `deque` data structure in order to insert "good" nodes at the front, and "bad" nodes at the back, thus maintaining the ruling set as much as possible.

   * always pops from the front the node that gets in the topological sort order, in order to use the aforementioned invariant.

#### Complexity

| Complexity | Task |
|------------|------|
| Time | O(V + E) |
| Space | O(V) |

### `ferate.cpp`

#### Description

The task gets reduced to determining the strongly connected components of the graph and calculating how many of them (the SCCs) have the in-degree equal to 0:

1. The idea comes from the observation that in order to reach all nodes from a given source we must first compute the SCCs of the graph.
That is due to the fact that in a SCC all nodes are reachable from all nodes and we mustn't be concerned about the connectivity **inside** it.

1. The next observation regards what SCCs **MUST** be connected with the source, as some of them can be reached through other SCCs, if they have a connection with the root node (directly or through other SCCs).
Obviously, the ones that have the in-degree 0 are the problematic components, and the algorithm calculates just that.
If the in-degree 0 component gets connected to the source, the other ones will eventually have a path anyway, since they are reachable from _somewhere_.

1. We've, now, reached the conclusion that we need the SCCs and we need how many SCCs have the in-degree 0.
The next steps are:

   * calculate the SCCs with Tarjan.

   * for each node, determine what SCC they are part of.

   * traverse the adjacency list and verify what nodes are part of different SCCs; increase the number of the in-degree for the concerned SCC if that's the case.

   * mark the in-degree of the source SCC as 1; we aren't intrested by what happens inside this component.

   * return the number of SCCs with in-degree 0.

> **Note**: The Tarjan implementation is highly inspired by the [PA lab demo](https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-07#tarjan_scc) and its official solution.

#### Complexity

| Complexity | Task |
|------------|------|
| Time | O(V + E) |
| Space | O(V) |

### `teleportare.cpp`

#### Description

An initial implementation (and the only one I was able to come up with) uses Dijkstra with a slight modification: mark each tunnel (and its subsequent edge) as a normal edge with cost of 1 second and use it in the Dijkstra algorithm only if the tunnel is open at the needed moment of time.

1. The distance (and therefore, the time spent traveling) until a certain point is given by the value of the distance array for the current node.

1. If we reach a tunnel, we check whether the time is a multiple of the period of the tunnel.

1. Otherwise, we take the edge as we would normally do for Dijkstra.

1. Obviously, this doesn't work when we need to spend some time in order to enter the tunnel, but oh well...

1. Finally, we return the last value of the distance array, as it represents the minimum path between the first and last node.

> **Note**: The Dijkstra implementation is highly inspired by the [PA lab demo](https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-08#dijsktra_-_pseudocod) and its official solution.

#### Complexity

| Complexity | Task |
|------------|------|
| Time | O(E * logV) |
| Space | O(V + k) |

### `magazin.cpp`

#### Description

The task is based off the idea that for each node of the tree it's enough if we know its position in the DFS traversal and the number of the nodes it the subtree that starts with it.

This is due to the observation that in order to compute the nth node starting from a random value in the traversal path, we must first check if the wanted node is part of the subtree in which the random value is root.

The flow of the program is:

   * Get the DFS path and the number of nodes in every subtree of the tree.

   * For every query, check whether the number of nodes in the subtree starting with the given source has more nodes than the number requested.

   * Get the node in the traversal array corresponding to the starting node + the given offset.

#### Complexity

| Complexity | Task |
|------------|------|
| Time | O(V + E) |
| Space | O(V) |
