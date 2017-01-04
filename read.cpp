#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <set>


typedef std::map<int, std::vector<int> > graphType;

void printGraph(graphType graph, std::set<int> nodes) {

    std::vector<int> nodes_vec(nodes.size());
    std::copy(nodes.begin(), nodes.end(), nodes_vec.begin());
    for(int i = 0; i < nodes_vec.size(); i++) {
        int node = nodes_vec[i];
        std::cout << node << ": ";
        std::vector<int> children = graph[node];
        for (int j = 0; j < children.size(); j++) {
            std::cout << children[j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::ifstream infile("test/dane-2.txt");
    std::set<int> nodes;
    graphType graph;
    int a, b;
    while (infile >> a >> b)
    {
        nodes.insert(a); nodes.insert(b);
        graphType::iterator it = graph.find(a);
        if (it == graph.end()) {
            std::vector<int> adjList;
            adjList.push_back(b);
//            std::cout << "Adding " << b << " under the new key " << a << std::endl;
            graph.insert(graphType::value_type(a, adjList));
        }
        else {
            graph[a].push_back(b);
//            std::cout << "Adding " << b << " under the existing key " << a << std::endl;
        }
    }
    printGraph(graph, nodes);
    return 0;
}