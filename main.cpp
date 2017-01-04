#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <queue>

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

void printResults(std::map<int, int> results) {
    for (const auto &p : results) {
        std::cout << "results[" << p.first << "] = " << p.second << '\n';
    }
}

std::map<int, int> compute_brandes(graphType graph, std::set<int> nodes) {

    std::map<int, int> C;
    for(auto node : nodes) {
        C[node] = 0;
        std::cout << "ss" << node << "\n";
    }

    for(auto s : nodes) {
        std::vector<int> S;
        std::map<int, std::vector<int> > P;
        for(auto w : nodes) {
            std::vector<int> emptyVec;
            P[w] = emptyVec;
        }
        std::map<int, int> g;
        for(auto t : nodes) {
            g[t] = 0;
        }
        g[s] = 1;
        std::map<int, int> d;
        for(auto t : nodes) {
            d[t] = -1;
        }
        d[s] = 0;
        std::queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            S.push_back(v);
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

        std::map<int, int> e;
        for(auto v: nodes) {
            e[v] = 0;
        }
        while(!S.empty()) {
            int w = S.front();
            S.pop_back();
            for (auto v: P[w]) {
                e[v] += (g[v]/g[w]) * (1 + e[w]);
                if (w != s) {
                    C[w] += e[w];
                }
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
    while (infile >> a >> b)
    {
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
    std::map<int, int> results = compute_brandes(graph, nodes);
    printResults(results);
    return 0;
}