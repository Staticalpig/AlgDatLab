#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>


enum node_adjacency_types {
    FRIEND,
    ADVERSARY,
    UNKNOWN,
    INIT
};

std::string node_adjacency_type_to_string(const node_adjacency_types type) {
    switch (type) {
        case FRIEND:
            return "FRIEND";
        case ADVERSARY:
            return "ADVERSARY";
        case INIT:
            return "INIT";
        case UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

class Node {
public:
    int name;
    std::vector<Node *> neighbors;

    explicit Node(const int name) : name(name) {
    }

    void addEdge(Node *neighbor) {
        neighbors.push_back(neighbor);
    }
};

class Graph {
private:
    std::vector<Node *> nodes;

public:
    explicit Graph(const int initial_size = 0) {
        for (int i = 0; i < initial_size; ++i) {
            nodes.push_back(new Node(i));
        }
    }

    ~Graph() {
        for (const auto node: nodes) {
            delete node;
        }
    }

    void addEdge(const int from, const int to) const {
        const auto size = nodes.size();
        if (from < 0 || from >= size || nodes.at(from) == nullptr) return;
        if (to < 0 || to >= size || nodes.at(to) == nullptr) return;


        nodes.at(from)->addEdge(nodes.at(to));
    }


    void BFS(const int initNode) const {
        if (nodes.empty()) return;
        if (initNode < 0 || initNode >= nodes.size() || nodes.at(initNode) == nullptr) return;

        Node *startNode = nodes.at(initNode);

        std::unordered_set<int> visited;
        std::unordered_map<int, node_adjacency_types> adjacency_map;

        std::queue<Node *> q;

        q.push(startNode);
        visited.insert(startNode->name);

        std::cout << "\nBFS Traversal Order: ";

        bool hasPastFirstLayer = false;
        while (!q.empty()) {
            const Node *currentNode = q.front();
            q.pop();

            std::cout << currentNode->name << " ";

            if (!hasPastFirstLayer) {
                adjacency_map[currentNode->name] = INIT;
            }

            for (Node *neighbor: currentNode->neighbors) {
                if (!visited.contains(neighbor->name)) {
                    visited.insert(neighbor->name);

                    if (adjacency_map.empty()) {
                        adjacency_map[currentNode->name] = INIT;
                    } else {
                        adjacency_map[neighbor->name] =
                                hasPastFirstLayer
                                    ? (adjacency_map[currentNode->name] == FRIEND ? ADVERSARY : FRIEND)
                                    : UNKNOWN;
                    }


                    q.push(neighbor);
                }
            }

            hasPastFirstLayer = true;
        }


        for (const auto &[node_name, node_type]: adjacency_map) {
            std::cout << "\nNode " << node_name << " is a " << node_adjacency_type_to_string(node_type);
        }
    }


    void printGraph() const {
        for (const auto node: nodes) {
            std::cout << "Node " << node->name << " has neighbors: ";
            if (node->neighbors.empty()) {
                std::cout << "...None";
            }
            for (const auto neighbor: node->neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    const Graph graph(7);


    graph.addEdge(0, 1);

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);

    graph.addEdge(2, 1);
    graph.addEdge(2, 3);

    graph.addEdge(3, 4);

    graph.addEdge(4, 5);

    graph.addEdge(0, 6);

    graph.printGraph();

    graph.BFS(0);


    return 0;
}
