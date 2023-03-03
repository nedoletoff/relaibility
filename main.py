import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

with open("edges.txt") as f:
    lines = f.readlines()

start, end = lines.pop(0).split()[1:]
edgeList = [line.strip().split() for line in lines]

g = nx.Graph()
g.add_edges_from(edgeList)
nodes = g.nodes
pos = nx.planar_layout(g)
nx.draw(g, pos, with_labels=True, node_color="#f86e00")

tempg = g.copy()
probs = np.linspace(0, 1, 11)
bf_res = [0] * 10

dfs = nx.dfs_edges(g, source=start, depth_limit=1)
count = 0
while len(tempg) >= 1:
    count += 1
    for i in dfs:
        if i[1] == end:
            for bf, prob in zip(bf_res, probs):
                bf += prob ** count
    tempg.remove_node(dfs[0][0])
    dfs = nx.dfs_edges(tempg, source=dfs[1], depth_limit=1)


#for i in nx.bfs_layers(g, sources=start):


print(start)
print(end)
print(bf_res)

#nx.draw(bfs, pos, with_labels=True, node_color="#f86e00", edge_color="#dd2222")

plt.show()
