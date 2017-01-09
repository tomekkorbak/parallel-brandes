from collections import deque, OrderedDict

# from networkx.algorithms.centrality.betweenness import betweenness_centrality
# import networkx as nx

import sys
if sys.version_info < (3, 0):
    sys.stdout.write("Sorry, requires Python 3.x, not Python 2.x\n")
    sys.exit(1)

def make_graph(file_path):
    nodes = set()
    graph = {}
    with open(file_path) as file:
        for line in file.readlines():
            node1, node2 = map(int, line.split())
            nodes.update([node1, node2])
            if node1 in graph.keys():
                graph[node1].append(node2)
            else:
                graph[node1] = [node2]
            if node2 not in graph.keys():
                graph[node2] = []
    return list(nodes), graph


def read_results(file_path):
    return dict((int(line.split()[0]), int(line.split()[1]))
                for line in open(file_path).readlines())

def write_results(file_path, results):
    with open(file_path, 'w') as file:
        for node, betweenness in results.items():
            file.write('{} {}\n'.format(node, betweenness))



def brandes(V, A):
    "Compute betweenness centrality in an unweighted graph."
    # Brandes algorithm
    # see http://www.cs.ucc.ie/~rb4/resources/Brandes.pdf
    C = dict((v,0) for v in V)
    for s in V:
        S = []
        P = dict((w,[]) for w in V)
        g = dict((t, 0) for t in V); g[s] = 1
        d = dict((t,-1) for t in V); d[s] = 0
        Q = deque([])
        Q.append(s)
        while Q:
            v = Q.popleft()
            S.append(v)
            for w in A[v]:
                if d[w] < 0:
                    Q.append(w)
                    d[w] = d[v] + 1
                if d[w] == d[v] + 1:
                    g[w] = g[w] + g[v]
                    P[w].append(v)
        e = dict((v, 0) for v in V)
        while S:
            w = S.pop()
            for v in P[w]:
                e[v] = e[v] + (g[v]/g[w]) * (1.0 + e[w])
                if s==5:
                    print('v', v, 'w', w, 'e[v]', e[v], 'g[v]', g[v], 'g[w]', g[w], 'e[w]', e[w])
            if w != s:
                C[w] = C[w] + e[w]
                
    return C


files = [
    # ('input1.txt', 's1.txt'),
    # ('input2.txt', 's2.txt'),
    # ('input3.txt', 'output3.txt'),
    # ('input4.txt', 'output4.txt'),
    # ('input5.txt', 'output5.txt'),
    ('input6.txt', 'output6.txt'),
]
for data_file, results_file in files:
    nodes, graph = make_graph(data_file)
    # results = read_results(results_file)
    #print results
    results = brandes(nodes, graph)


    # graph = nx.Graph(graph, is_directed=True)
    # results = dict(betweenness_centrality(graph, normalized=False))

    results = OrderedDict(sorted(results.items()))
    # for node, children in results.items():
    #     print(node, ': ', children)
    # print(results)
    write_results(results_file, results)
    
    # graph = nx.Graph(graph, is_directed=True)
    # results = betweenness_centrality(graph, normalized=False)
    # print brandes(nodes, graph) == results
