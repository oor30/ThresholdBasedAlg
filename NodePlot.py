import matplotlib.pyplot as plt
import networkx as nx
import csv
from matplotlib import animation

print("hello python: NodePlot.py")

INPUT_CSV_PATH = '/Users/kazuki/Developer/CLionProjects/ThresholdBasedAlg/output/output.csv'
OUTPUT_GIF_PATH = '/Users/kazuki/Developer/CLionProjects/ThresholdBasedAlg/output/nodes.gif'

# グラフを定義
G = nx.Graph()
fig = plt.figure(figsize=(150, 10))
plt.xlabel("x-label")
plt.ylabel("y-label")
ax = fig.add_subplot(111)


def get_nodes():
    csv_file = open(INPUT_CSV_PATH, "r")
    f = csv.reader(csv_file, delimiter=",", lineterminator="\r\n")
    nodes = [row for row in f]

    nodes_outer = []
    nodes_inner = []
    cnt = 0
    for i in range(len(nodes)):
        node = nodes[i]
        if node[0] == 't=':
            if node[1] == str(cnt + 1):
                nodes_outer.append(nodes_inner)
                nodes_inner = []
                cnt += 1
        else:
            nodes_inner.append(node)
        if cnt == 10000:
            break
    print('len(nodes_outer): {}'.format(len(nodes_outer)))
    return nodes_outer


def get_ims(nodes_outer):
    ims = []
    for nodes in nodes_outer:
        pos = {}
        node_color = []
        G.add_nodes_from([n for n in range(len(nodes))])
        for node in nodes:
            pos[int(node[0])] = (float(node[1]), float(node[2]))
            node_color.append(float(node[3]))
        nex = nx.draw_networkx(G, pos=pos, node_color=node_color)
        ims.append(nex)
    return ims


nodesG = get_nodes()


def update(i):
    print('t={}'.format(i))
    plt.cla()
    ax.grid()
    ax.set_xlim(-15000, 25000)
    ax.set_ylim(-1, 4)
    pos = {}
    node_color = []
    nodes = nodesG[i*100]
    for node in nodes:
        pos[int(node[0])] = (float(node[1]), float(node[2]))
        node_color.append(float(node[3]))

    G.add_nodes_from(range(len(pos)))
    nx.draw_networkx(G, pos=pos, node_color=node_color)
    plt.title('t=' + str(i))


def main():
    # nodes = get_nodes()
    # ims = get_ims(nodes)
    # anim = animation.ArtistAnimation(fig, ims, interval=100, blit=True)
    anim = animation.FuncAnimation(fig, update, frames=99, interval=100)
    anim.save(OUTPUT_GIF_PATH, writer='pillow')
    plt.show()


if __name__ == "__main__":
    main()
