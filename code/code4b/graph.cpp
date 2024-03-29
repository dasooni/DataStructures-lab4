/*********************************************
 * file:	~\code4b\graph.h                  *
 * remark:implementation of undirected graphs *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>  //assert

#include "graph.h"
#include "heap.h"
#include "dsets.h"
#include <algorithm>

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

// Create a graph with n vertices and no vertices
Graph::Graph(int n) : table(size_t(n) + 1), size{n}, n_edges{0} {
    assert(n >= 1);
}

Graph::Graph(const std::vector<Edge> &V, int n) : Graph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge e
// update weight if edge e is present
void Graph::insertEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edge_insertion = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        if (auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                                   [e1](const Edge &ed) { return e1.links_same_nodes(ed); });
            it == end(T[e1.head])) {
            T[e1.head].push_back(e1);  // insert new edge e
            ++n;                       // increment the counter of edges
        } else {
            it->weight = e1.weight;  // update the weight
        }
    };

    edge_insertion(e);
    edge_insertion(e.reverse());
}

// remove undirected edge e
void Graph::removeEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edgeRemoval = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                               [e1](const Edge &ed) { return e1.links_same_nodes(ed); });

        assert(it != end(T[e1.head]));
        T[e1.head].erase(it);  // remove edge e1
        --n;                   // decrement the counter of edges
    };

    edgeRemoval(e);
    edgeRemoval(e.reverse());
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {
    std::vector<int> dist(size_t(size) + 1);
    std::vector<int> path(size_t(size) + 1);
    std::vector<bool> done(size_t(size) + 1);

    for (auto i = 1; i <= size; ++i)
    {
        dist[i] = inf;
        path[i] = 0;
        done[i] = false;
    }
    

    int vertex = 1;
    int weight = 0;

    dist[vertex] = 0; //start can be any vertex, we choose the first one.
    done[vertex] = true;

    while (true)
    {
        for (auto it = table[vertex].begin(); it != table[vertex].end(); ++it) { //Update dist[u] for each v�s adjacent vertex u, if better edge(v, u)
            int u = it->tail; // u is a vertex adjacent to v

            if (done[u] == false && dist[u] > it->weight) {
                dist[u] = it->weight;
                path[u] = vertex;
            }
        }
        
        int smallestDist = inf;
        int index = 0;
        
        //Find the min in array dist
        for (auto i = 1; i < size + 1; ++i){
            //if false, check if it is the smallest dist value
            if (done[i] == false && dist[i] < smallestDist) {
                    smallestDist = dist[i];
                    index = i;
            }
        }
		
        if (smallestDist == inf) break;
        
        vertex = index;
        std::cout << "( " << path[vertex] << ", " << vertex << ", " << dist[vertex] << " )\n";
        done[vertex] = true;
		weight += dist[vertex];
        
    }
	std::cout << "\nTotal weight: " << weight << "\n";
    
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {
	//Graph constructor creates from edge vector.
    // insert edge inserts a single edge

    DSets DSets( size );
    
    int counter{ 0 };
    int weight{ 0 };
	
    std::vector<Edge> edges;
	Heap<Edge> heap2{};
	
	//heapify unique edges
	for (auto i = 1; i <= size; ++i) {
		for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            if (i < it->tail) {
                Edge e{ i, it->tail, it->weight };
				heap2.insert(e);
				std::cout << "inserting edge: " << e << "\n";
                edges.push_back(e);
            }
			
		}
	}

	//sort edges by weight
	std::sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2) { return e1.weight > e2.weight; });
	
	//for each edge in edges

    Heap<Edge> heap{edges};
	
	//while the heap is not empty
    while (counter < (size - 1) ) {
        //get the edge with the smallest weight
        Edge e = heap.deleteMin();

        if (DSets.find(e.head) != DSets.find(e.tail)) {

            std::cout << e << std::endl;
            
            //merge the sets
            DSets.join(DSets.find(e.head), DSets.find(e.tail));
			//increment the counter
			counter++;
			weight += e.weight;

        }
    }
    std::cout << "\n Total wight: " <<  weight << std::endl;
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight
                      << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}
