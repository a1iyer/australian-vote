/*
 * dijkstra1.cpp
 * Anoop Iyer, 2015
 * C++ class assignment for breadth-first search (Dijkstra's algorithm).
 */

#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <queue>

namespace Dijkstra {

/*
 * Step 1: class and function declarations
 */

class Node {
private:
    unsigned int node_id = 0;
    bool traversed = false;
    Node * prev = NULL;
    std::vector<Node *> adjacent_nodes;
    std::vector<unsigned int> distance;
public:
    unsigned int shortest_distance = UINT_MAX;
    Node () { }
    void init (int id) { node_id = id; }
    void add_edge (Node * n, unsigned int w);
    unsigned int visit (Node * p, unsigned int w);
    void print ();
    void start (unsigned int t);
    bool visit_neighbors (unsigned int t);
    bool connected (void);
};

class greater {
public:
    bool operator() (const Node * lhs, const Node * rhs) {
        return (lhs->shortest_distance > rhs->shortest_distance);
    }
};

/*
 * Step 2: global objects in this namespace
 */

bool verbose = false;
std::deque<unsigned int> fq;
std::priority_queue< Dijkstra::Node*, 
                     std::vector<Dijkstra::Node*>,
                     Dijkstra::greater > node_queue;


/*
 * Step 3: Implementation of class methods and other functions
 */

void Node::add_edge (Node * n, unsigned int w)
{
    adjacent_nodes.push_back(n);
    distance.push_back(w);
}

void Node::print ()
{
    if (verbose) {
        std::cout << "Node " << node_id << '\n';
        for (unsigned int i = 0; i < distance.size(); i++) {
            std::cout << "  : " << adjacent_nodes[i]->node_id << "," << distance[i] << '\n';
        }
    }
}

void Node::start (unsigned int target)
{
    shortest_distance = 0;
    traversed = true;
    visit_neighbors (target);
    /*
     * should be a sequence of
     *   visit_neighbors(), and
     *   node_queue.pop()
     * until we reach the target.
     */
    bool done = false;
    while (done == false && node_queue.size() > 0) {
        Node * n = node_queue.top ();
        node_queue.pop ();
        done = n->visit_neighbors (target);
    }
}

bool Node::visit_neighbors (unsigned int t)
{
    if (verbose) {
        std::cout << "In visit_neighbors Node " << node_id << '\n';
    }
    traversed = true;
    if (node_id == t) {
        /*
         * Done! Construct a queue with the path back to the origin.
         */
        if (verbose) {
            std::cout << "Done: reached node " << t << '\n';
        }
        Node * p;
        for (p = this; p != NULL; p = p->prev) {
            fq.push_back (p->node_id);
        }
        return true;
    }

    if (verbose) {
        std::cout << adjacent_nodes.size() << " adjacent nodes\n";
    }
    for (unsigned int i = 0; i < distance.size(); i++) {
        if (verbose) {
            std::cout << "Adjacent node: " << adjacent_nodes[i]->node_id << '\n';
        }
        if (adjacent_nodes[i]->traversed == false) {
            adjacent_nodes[i]->visit (this, distance[i]);
            node_queue.push (adjacent_nodes[i]);
            if (verbose) {
                std::cout << "Queueing node " << adjacent_nodes[i]->node_id << '\n';
            }
        }
    }
    return false;
}

unsigned int Node::visit (Node * p, unsigned int w)
{
    if (shortest_distance >= w + p->shortest_distance) {
        shortest_distance = w + p->shortest_distance;
        prev = p;
    }
    if (verbose) {
        std::cout << "Visiting " << node_id << " from " << p->node_id << '\n';
        std::cout << "SD = " << shortest_distance << '\n';
    }
    return shortest_distance;
}

bool Node::connected (void)
{
    return (adjacent_nodes.size() != 0);
}

}; // namespace Dijkstra

int main (int ac, char * av[])
{
    unsigned int num_nodes;
    unsigned int num_edges;
    Dijkstra::Node * node;

    /*
     * Create: read in node and edge count, and create the objects.
     */
    std::cin >> num_nodes;
    std::cin >> num_edges;
    node = new Dijkstra::Node[num_nodes];

    for (unsigned int i = 0; i < num_nodes; i++) {
        node[i].init (i + 1);
    }

    for (unsigned int i = 0; i < num_edges; i++) {
        unsigned int nod1;
        unsigned int nod2;
        unsigned int dist;
        std::cin >> nod1;
        std::cin >> nod2;
        std::cin >> dist;

        node[nod1 - 1].add_edge (&node[nod2 - 1], dist);
        node[nod2 - 1].add_edge (&node[nod1 - 1], dist);
    }

    /*
     * Debug: examine the nodes and edges before starting traversal.
     */
    if (Dijkstra::verbose) {
        std::cout << "Nodes = " << num_nodes << '\n';
        std::cout << "Edges = " << num_edges << '\n';
        for (unsigned int i = 0; i < num_nodes; i++) {
            node[i].print();
        }
        std::cout << "End of node listing\n";
    }

    /*
     * If the target node has no edges, fail trivially; else traverse.
     */
    if (!node[num_nodes - 1].connected()) {
        std::cout << "-1\n";
    } else {
        node[0].start(num_nodes);
        if (Dijkstra::fq.size() > 0) {
            for (auto i = Dijkstra::fq.rbegin(); i != Dijkstra::fq.rend(); i++) {
                std::cout << *i << ' ';
            }
            std::cout << '\n';
        } else {
            std::cout << "-1\n";
        }
    }

    delete[] node;

    return 0;
}
