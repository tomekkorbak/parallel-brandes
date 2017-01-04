from collections import deque


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
    return list(nodes), graph


def read_results(file_path):
    return dict((int(line.split()[0]), int(line.split()[1]))
                for line in open(file_path).readlines())


def brandes(V, A):
    "Compute betweenness centrality in an unweighted graph."
    # Brandes algorithm
    # see http://www.cs.ucc.ie/~rb4/resources/Brandes.pdf
    C = dict((v, 0) for v in V)
    for s in V:
        S = []
        P = dict((w, []) for w in V)
        g = dict((t, 0) for t in V)
        g[s] = 1
        d = dict((t, -1) for t in V)
        d[s] = 0
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
                    g[w] += g[v]
                    P[w].append(v)
        e = dict((v, 0) for v in V)
        while S:
            w = S.pop()
            for v in P[w]:
                e[v] += (g[v]/g[w]) * (1 + e[w])
                if w != s:
                    C[w] += e[w]
    return C


files = [
    ('dane-1.txt', 'wynik-1.txt'),
    ('dane-2.txt', 'wynik-2.txt'),
]
for data_file, results_file in files:
    nodes, graph = make_graph(data_file)
    results = read_results(results_file)
    print results
    print brandes(nodes, graph)
    print brandes(nodes, graph) == results