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

void printE(std::map<int, double> e) {
    for (const auto &p : e) {
        std::cout << "" << p.first << ": " << p.second << '\n';
    }
}

void writeResults(std::map<int, double> results, char* file_path) {
    std::ofstream file;
    file.open(file_path);
    for (const auto &p : results) {
        file << p.first << " " << p.second << std::endl;
    }
    file.close();
}


void computeSubarray(std::vector<int>& nodes, int start, int end, graphType& graph, std::map<int, double>& C) {
    std::cout << "Executing cS start " << start << " end " << end;
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
                if (s== 5) {
                    std::cout << " v " << v << " w " << w << " e[v] " << e[v] << " g[v] " << g[v] << " g[w] " << g[w] << " e[w] " << e[w] << std::endl;

                }
            }
            if (w != s) {
                C[w] += e[w];
            }
        }
    }
}

std::map<int, double> computeBrandes(graphType graph, std::set<int> nodes, int numThreads) {

    std::map<int, double> C; // BC
    for(auto node : nodes) {
        C[node] = 0.0;
    }

    std::vector<int> nodes_vec( nodes.begin(), nodes.end() );
    size_t length = nodes_vec.size() / numThreads;
    size_t remain = nodes_vec.size() % numThreads;
    size_t i = 0;
    int start, end;
    while(i < nodes_vec.size()) {
        int extraNodes = 0;
        if(remain > 0) {
            extraNodes = 1;
            remain--;
        }
        start = i;
        end = start + length + extraNodes;
        computeSubarray(&nodes_vec, start, end, &graph, &C);
        start = end;
    }


    return C;
}


int main(int argc, char* argv[]) {
    std::ifstream infile(argv[2]);
    std::set<int> nodes;
    graphType graph;
    int a, b;
    while (infile >> a >> b) {
        nodes.insert(a); nodes.insert(b);
        graphType::iterator it = graph.find(a);
        if (it == graph.end()) {
            std::vector<int> adjList;
            adjList.push_back(b);
            graph.insert(graphType::value_type(a, adjList));
        }
        else {
            graph[a].push_back(b);
        }
    }
    std::map<int, double> results = computeBrandes(graph, nodes, atoi(argv[1]));
//    if (argv[4] == "-v") {
//    printGraph(graph, nodes);
//        printResults(results);
//    }
    writeResults(results, argv[3]);
    return 0;
}