#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <stack>

typedef std::map<int, std::vector<int> > graphType;

void printGraph(graphType graph, std::set<int> nodes) {

    std::vector<int> nodes_vec(nodes.size());
    std::copy(nodes.begin(), nodes.end(), nodes_vec.begin());
    for(int i = 0; i < nodes_vec.size(); i++) {
        int node = nodes_vec[i];
        std::cout << node << ": ";
        std::vector<int> children = graph[node];
        for (int j = 0; j < children.size(); j++) {
            std::cout << children[j] << ", ";
        }
        std::cout << std::endl;
    }
}

void printResults(std::map<int, double> results) {
    for (const auto &p : results) {
        std::cout << "results[" << p.first << "] = " << p.second << '\n';
    }
}

std::map<int, double> compute_brandes(graphType graph, std::set<int> nodes) {

    std::map<int, double> C; // BC
    for(auto node : nodes) {
        C[node] = 0.0;
    }

    for(auto s : nodes) {
        std::stack<int> S;
        std::map<int, std::vector<int> > P;
        std::map<int, double> g;
        std::map<int, int> d;
        std::map<int, double> e;
        for(auto w : nodes) {
            std::vector<int> emptyVec;
            P[w] = emptyVec;
            g[w] = 0;
            d[w] = -1;
            e[w] = 0;
        }
        g[s] = 1.0;
        d[s] = 0;
        std::queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            S.push(v);
            for(auto w : graph[v]) {
                if (d[w] < 0) {
                    Q.push(w);
                    d[w] = d[v] +1;
                }
                if (d[w] == d[v] + 1) {
                    g[w] += g[v];
                    P[w].push_back(v);
                }
            }
        }
        while(!S.empty()) {
            int w = S.top();
            S.pop();
            for (auto v: P[w]) {
                e[v] += (g[v]/g[w]) * (1.0 + e[w]);
            }
            if (w != s) {
                C[w] += e[w];
            }
        }

    }
    return C;
}


int main() {
    std::ifstream infile("test/dane-2.txt");
    std::set<int> nodes;
    graphType graph;
    int a, b;
    while (infile >> a >> b) {
        nodes.insert(a); nodes.insert(b);
        graphType::iterator it = graph.find(a);
        if (it == graph.end()) {
            std::vector<int> adjList;
            adjList.push_back(b);
            // Adding new key a and appending b onto it
            graph.insert(graphType::value_type(a, adjList));
        }
        else {
            // Adding b under the existing key a
            graph[a].push_back(b);
        }
    }
    printGraph(graph, nodes);
    std::map<int, double> results = compute_brandes(graph, nodes);
    printResults(results);
    return 0;
}