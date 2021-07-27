#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include "configure.h"

using namespace std;

void nodeGenerator(Node[N]);

void startSimulation(Node node[N]);

int output(Node[N], string[100]);

string get_text(Node[N], int);

int main() {
    cout << "Hello, World!" << endl;
    Node nodes[N];
    nodeGenerator(nodes);
    startSimulation(nodes);
//    output(nodes);
    return 0;
}

void nodeGenerator(Node node[N]) {
    cout << "ノードを作成します" << endl;
    random_device seed;
    mt19937 engine(seed());
    normal_distribution<> dist(mu, sig);
    for (int i = 0; i < N; ++i) {
        double v = dist(engine);
        node[i] = (Node(i, v, node));
    }
}

void startSimulation(Node nodes[N]) {
    ofstream ofs(output_path);
    if (!ofs.is_open()) {
        cout << "ファイルをオープンできません" << endl;
        return;
    }

    string output_texts[100];
    for (int i = 0; i < 100; ++i) {
//        nodes[i].start();
        for (int j = 0; j < N; ++j) {
            nodes[j].move();
        }
        output_texts[i] = get_text(nodes, i);
    }
    output(nodes, output_texts);
}

string get_text(Node nodes[N], int n) {
    string text = "t=," + to_string(n) + ",-,-,\n";
    for (int i = 0; i < N; ++i) {
        text += to_string(i) + ",";
        text += to_string(nodes[i].pos.x) + ",";
        text += to_string(nodes[i].pos.y) + ",";
        text += to_string(nodes[i].velocity) + "\n";
    }
    return text;
}

int output(Node nodes[N], string output_texts[100]) {
    ofstream ofs(output_path);
    if (!ofs.is_open()) {
        cout << "ファイルをオープンできません" << endl;
        return -1;
    }

    cout << "ファイルに書き込みします" << endl;

//    for (int i = 0; i < N; i++) {
//        ofs << i << ",";
//        ofs << nodes[i].pos.x << ",";
//        ofs << nodes[i].pos.y << ",";
//        ofs << nodes[i].velocity << endl;
//    }

    for (int i = 0; i < 100; ++i) {
        ofs << output_texts[i];
    }
    ofs.close();
    return 0;
}