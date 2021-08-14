#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Node.h"
#include "configure.h"

using namespace std;

set<int> get_nodes_pos();

void node_generator(set<int>&, map<int, Node>&, vector<Node>&, vector<vector<Node>>&);

void start_simulation(map<int, Node> &nodes);

int output(string[TIMES]);

string get_text(map<int, Node> &, int);

int main() {
    cout << "Hello, World!" << endl;

    set<int> pos_set = get_nodes_pos();
    map<int, Node> nodes;
    vector<Node> nodes_by_dis = {};
    vector<vector<Node>> nodes_lane(4);
    node_generator(pos_set, nodes, nodes_by_dis, nodes_lane);

    cout << "nodes.size():" << nodes.size() << endl;
    start_simulation(nodes);
    return 0;
}

set<int> get_nodes_pos() {
    random_device rnd;
    set<int> pos_set;
    while (pos_set.size() < N) {
        int pos = rnd() % (15000 * 4);
        pos_set.insert(pos / 80);
        cout << pos << ", ";
    }
    cout << endl;
    set<int> tmp{};
    for (int pos:pos_set) {
        tmp.insert(pos * 80);
        cout << pos * 80 << ", ";
    }
    cout << endl;
    return tmp;
}

void node_generator(set<int> &pos_set, map<int, Node> &nodes, vector<Node> &nodes_by_dis,
                    vector<vector<Node>> &nodes_lane) {
    cout << nodes.size() << endl;
    cout << "ノードを作成します" << endl;
    random_device seed;
    mt19937 engine(seed());
    normal_distribution<> dist(mu, sig);

    auto itr = pos_set.begin();
    for (int i = 0; i < N; ++i) {
        double v = dist(engine);
        int pos = *itr;
        itr++;
        int l = pos / 15000 % 2;
        int d = pos / 30000;
        double dis = pos % 15000;
        cout << "pos:" << pos << ", lane:" << l << ", d:" << d << ", dis:" << dis << endl;
        nodes[i] = Node(i, dis, l, d, v, nodes, nodes_by_dis);
        nodes_by_dis.push_back(nodes[i]);
        nodes_lane[pos / 15000].push_back(nodes[i]);
    }
    sort(nodes_by_dis.begin(), nodes_by_dis.end());
    for (Node node:nodes_by_dis) {
        cout << node.dis << ", ";
    }
    cout << endl;
}

void start_simulation(map<int, Node> &nodes) {
    ofstream ofs(output_path);
    if (!ofs.is_open()) {
        cout << "ファイルをオープンできません" << endl;
        return;
    }

    string output_texts[TIMES];
    for (int i = 0; i < TIMES; ++i) {
        cout << "t = " << i << endl;
        for (int j = 0; j < N; ++j) {
            nodes[j].move();
        }
        output_texts[i] = get_text(nodes, i);
    }
    output(output_texts);
}

string get_text(map<int, Node> &nodes, int n) {
    string text = "t=," + to_string(n) + ",-,-\n";
    for (int i = 0; i < N; ++i) {
        text += to_string(i) + ",";
        text += to_string(nodes[i].pos.x) + ",";
        text += to_string(nodes[i].lane + (nodes[i].direction*2)) + ",";
        text += to_string(nodes[i].v) + "\n";
    }
    return text;
}

int output(string output_texts[TIMES]) {
    ofstream ofs(output_path);
    if (!ofs.is_open()) {
        cout << "ファイルをオープンできません" << endl;
        return -1;
    }

    cout << "ファイルに書き込みします" << endl;

    for (int i = 0; i < TIMES; ++i) {
        ofs << output_texts[i];
    }
    ofs.close();
    return 0;
}
