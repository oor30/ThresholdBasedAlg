import matplotlib.pyplot as plt
import networkx as nx
import csv

print("hello python")

csv_file = open("/Users/kazuki/Developer/CLionProjects/ThresholdBasedAlg/output/output.csv", "r")
f = csv.reader(csv_file, delimiter=",", lineterminator="\r\n")

# 12個の頂点と、ランダムに引いた辺を持つグラフを定義
G = nx.Graph()
# G.add_nodes_from([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
# for i in range(len(G.nodes)):
#     for j in range(i + 1, len(G.nodes)):
#         if np.random.uniform() < 0.3:
#             G.add_edge(node_labels[i], node_labels[j])

# pos = {
#     n: (np.cos(2 * i * np.pi / 12), np.sin(2 * i * np.pi / 12))
#     for i, n in enumerate(G.nodes)
# }
nodes = [row for row in f]
G.add_nodes_from([n for n in range(len(nodes))])
pos = {int(node[0]): (int(node[1]), int(node[2])) for node in nodes}
node_color = [float(node[3]) for node in nodes]
# pos = {
#     n: (n, 0) for n in range(10)
# }
print(pos)

# 座標を指定せずに描写する
nx.draw_networkx(G, pos=pos, node_color=node_color)
plt.show()
