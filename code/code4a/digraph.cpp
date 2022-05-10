/*********************************************
 * file:	~\code4a\digraph.cpp              *
 * remark: implementation of directed graphs  *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>


#include "digraph.h"
#include <queue>

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

Digraph::Digraph(int n)
    : table(size_t(n) + 1)
    , size{n}
    , n_edges{0}
    , dist(size_t(n) + 1)
    , path(size_t(n) + 1)
    , done(size_t(n) + 1) {
    assert(n >= 1);

    // Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<Edge>& V, int n) : Digraph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge e = (u, v, w)
// update weight w if edge (u, v) is present
void Digraph::insertEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    // Check if edge e already exists
    if (auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                               [e](const Edge& ed) { return e.links_same_nodes(ed); });
        it == end(table[e.head])) {
        table[e.head].push_back(e);  // insert new edge e
        ++n_edges;
    } else {
        it->weight = e.weight;  // update the weight
    }
}

// remove directed edge e
void Digraph::removeEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                           [e](const Edge& ed) { return e.links_same_nodes(ed); });

    assert(it != end(table[e.head]));
    table[e.head].erase(it);
    --n_edges;
}

// construct unweighted single source shortest path-tree for start vertex s
void Digraph::uwsssp(int s) const {
    assert(s >= 1 && s <= size);

    // Queue used for BFS traversal
    std::queue<int> Q;

    for (auto i = 1; i <= size; i++)
    {
        dist[i] = inf;
        path[i] = 0;
    }
   
    dist[s] = 0;
    Q.push(s);

    while (!Q.empty())
    {
        int vertex = Q.front();
        Q.pop();

        for (auto it = table[vertex].begin(); it != table[vertex].end(); it++)
        {
            int u = it->tail;

            if (dist[u] == inf) {
                dist[u] = dist[vertex] + 1;
                path[u] = vertex;
                Q.push(u);
            }
        }
    }
}

// construct positive weighted single source shortest path-tree for start vertex s
// Dijkstras algorithm
void Digraph::pwsssp(int s) const {
    assert(s >= 1 && s <= size);

    // *** TODO ***
    for (auto i = 1; i <= size; i++)
    {
        dist[i] = inf;
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    done[s] = true;
    int vertex = s;

    while (true)
    {
        for (auto it = table[vertex].begin(); it != table[vertex].end(); it++)
        {
            int u = it->tail;

           // std::cout << u << " ";

            if (done[u] == false && dist[u] > dist[vertex] + it->weight) {
                dist[u] = dist[vertex] + it->weight;
                path[u] = vertex;
            }
        }
        
        int smallestDist = inf;
        int index = 0;
        for (auto i = 1; i < done.size(); i++)
        {
            //if false, check if it is the smallest dist value
            if (done[i] == false) {
                if (dist[i] < smallestDist) {
                    index = i;
                    smallestDist = dist[i];
                }
            }
        }
        vertex = index;
        if (smallestDist == inf) break;
        done[vertex] = true;

    }
}


// print graph
void Digraph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                  \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; ++v) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << "----------------------\n";
    std::cout << "vertex    dist    path\n";
    std::cout << "----------------------\n";

    for (int v = 1; v <= size; ++v) {
        std::cout << std::setw(4) << v << " :" << std::setw(8)
                  << ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
                  << path[v] << "\n";
    }
    std::cout << "----------------------\n";
}


void Digraph::recursivePrint(int t) const {

    if (path[t] == 0) {
        std::cout << " " << t << " ";
    }
    else{
        recursivePrint(path[t]);
        std::cout << t << " ";
        
    }
}

// print shortest path from s to t and the corresponding path length
// Hint: consider using recursion

void Digraph::printPath(int t) const {
    assert(t >= 1 && t <= size);

    if(t > size || t < 1) {
        std::cout << "#error!" << " ";
        return;
    }

    recursivePrint(t);
    std::cout << "(" << dist[t] << ")";
}
