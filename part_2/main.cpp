#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>


enum node_adjacency_types {
    FRIEND,
    ADVERSARY
};

std::string node_adjacency_type_to_string(const node_adjacency_types type) {
    switch (type) {
        case FRIEND:
            return "FRIEND";
        case ADVERSARY:
            return "ADVERSARY";
        default:
            return "UNKNOWN";
    }
}

class Node {
public:
    int name;
    std::vector<Node*> neighbors;

    explicit Node (const int name) : name(name) {}

    void addEdge(Node* neighbor) {
        neighbors.push_back(neighbor);
    }
};

class Graph {
private:
    std::vector<Node*> nodes;
public:
    ~Graph() {
        for (const auto node : nodes) {
            delete node;
        }
    }

    Node* addNode(const int name) {
        const auto newNode = new Node(name);
        nodes.push_back(newNode);
        return newNode; // So we can add edges later
    }

    void BFS(Node* startNode) const {
        if (nodes.empty()) return;
        if (startNode == nullptr) return;


        std::unordered_set<int> visited;
        std::unordered_map<int, node_adjacency_types> adjacency_map;

        std::queue<Node*> q;

        q.push(startNode);
        visited.insert(startNode->name);

        std::cout << "\nBFS Traversal Order: ";

        while (!q.empty()) {
            const Node* currentNode = q.front();
            q.pop();

            std::cout << currentNode->name << " ";

            const node_adjacency_types currentType = adjacency_map[currentNode->name];

            node_adjacency_types nextType;
            if (currentType == FRIEND) {
                nextType = ADVERSARY;
            } else {
                nextType = FRIEND;
            }

            for (Node* neighbor : currentNode->neighbors) {
                if (!visited.contains(neighbor->name)) {
                    visited.insert(neighbor->name);
                    adjacency_map[neighbor->name] = nextType;
                    q.push(neighbor);
                }
            }
        }


        for (const auto&[node_name, node_type] : adjacency_map) {
            std::cout << "\nNode " << node_name << " is a " << node_adjacency_type_to_string(node_type);
        }

    }



    void printGraph() const {
        for (const auto node : nodes) {
            std::cout << "Node " << node->name << " has neighbors: ";
            if (node->neighbors.empty()) {
                std::cout << "...None";
            }
            for (const auto neighbor : node->neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

};

int main() {

    Graph graph;

    Node* node0 = graph.addNode(0);
    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(2);
    Node* node3 = graph.addNode(3);


    node0->addEdge(node1);
    node1->addEdge(node2);
    node1->addEdge(node3);

    node2->addEdge(node1);
    node2->addEdge(node3);


    graph.printGraph();

    graph.BFS(node0);


    return 0;
}