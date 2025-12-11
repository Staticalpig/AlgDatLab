#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>


enum node_adjacency_types {
    FRIEND,
    ADVERSARY,
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

    void add_edge(Node *neighbor) {
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

    void add_edge(const int from, const int to) const {
        const auto size = nodes.size();
        if (from < 0 || from >= size || nodes.at(from) == nullptr) return;
        if (to < 0 || to >= size || nodes.at(to) == nullptr) return;


        nodes.at(from)->add_edge(nodes.at(to));
    }


  void BFS(const int init_node) const {
        if (nodes.empty()) return;
        if (init_node < 0 || init_node >= static_cast<int>(nodes.size()) || nodes.at(init_node) == nullptr) return;

        Node *start_node = nodes.at(init_node);

        std::unordered_set<int> visited;
        std::unordered_map<int, node_adjacency_types> adjacency_map;

        std::queue<Node *> q;

        q.push(start_node);
        visited.insert(start_node->name);

        adjacency_map[start_node->name] = INIT;

        std::cout << "\nBFS Traversal Order: ";

        while (!q.empty()) {
            const Node *current_node = q.front();
            q.pop();

            std::cout << current_node->name << " ";

            const node_adjacency_types current_type = adjacency_map[current_node->name];

            for (Node *neighbor: current_node->neighbors) {
                if (!visited.contains(neighbor->name)) {
                    visited.insert(neighbor->name);

                    adjacency_map[neighbor->name] = (current_type == FRIEND) ? ADVERSARY : FRIEND;

                    // Make the first layer FRIEND(s)
                    if (current_type == INIT) {
                        adjacency_map[neighbor->name] = FRIEND;
                    }

                    q.push(neighbor);
                }
            }
        }


        for (const auto &[node_name, node_type]: adjacency_map) {
            std::cout << "\nNode " << node_name << " is a " << node_adjacency_type_to_string(node_type);
        }
    }


    void print_graph() const {
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


    graph.add_edge(0, 1);

    graph.add_edge(1, 2);
    graph.add_edge(1, 3);

    graph.add_edge(2, 1);
    graph.add_edge(2, 3);

    graph.add_edge(3, 4);

    graph.add_edge(4, 5);

    graph.add_edge(0, 6);

    graph.print_graph();

    graph.BFS(0);


    return 0;
}
