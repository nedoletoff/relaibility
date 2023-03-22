import networkx as nx
import matplotlib.pyplot as plt


def decomposition(p):
    return p + pow(p, 3) + pow(p, 5)
    # return 2 * pow(p, 2) + 2 * pow(p, 3) + pow(p, 4) - pow(p, 5)


def find_all_paths(graph, start_t, end_t, path=None):
    if path is None:
        path = []
    path = path + [start_t]
    if start_t == end_t:
        return [path]
    if not graph.has_node(start_t):
        return []
    paths = []
    for node in graph[start_t]:
        if node not in path:
            newpaths = find_all_paths(graph, node, end_t, path)
            for newpath in newpaths:
                paths.append(newpath)
    return paths


with open("edges.txt") as f:
    lines = f.readlines()

start, end = lines.pop(0).split()[1:]
edgeList = [line.strip().split() for line in lines]

g = nx.Graph()
g.add_edges_from(edgeList)
nodes = g.nodes
pos = nx.planar_layout(g)
nx.draw(g, pos, with_labels=True, node_color="#f86e00")
pr_all = [0] * 11

print(start, end)
probs = (0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0)
for i, prob in enumerate(probs):
    paths = find_all_paths(g, start, end)
    for path in paths:
        pr_all[i] += pow(prob, len(path) - 1)

for i, prob in enumerate(probs):
    print(f'probability = {prob}: probability decomposition ='
          f' {decomposition(prob)}, probability brute force = {pr_all[i]}')

plt.show()
