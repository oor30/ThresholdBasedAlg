#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include "configure.h"

using namespace std;

void nodeGenerator(map<int, Node>&);

void startSimulation(map<int, Node>&);

int output(string[100]);

string get_text(map<int, Node>&, int);

map<int, Node> nodes;
int main() {
    cout << "Hello, World!" << endl;
//    Node nodes[N];
    nodeGenerator(nodes);
    cout << "nodes.size():" << nodes.size() << endl;
    startSimulation(nodes);
//    output(nodes);
    return 0;
}

void nodeGenerator(map<int, Node>& nodes) {
    cout << nodes.size() << endl;
    cout << "ノードを作成します" << endl;
    random_device seed;
    mt19937 engine(seed());
    normal_distribution<> dist(mu, sig);
    for (int i = 0; i < N; ++i) {
        double v = dist(engine);
        nodes[i] = Node(i, v, nodes);
    }
}
//void nodeGenerator(Node node[N]) {
//    cout << "ノードを作成します" << endl;
//    random_device seed;
//    mt19937 engine(seed());
//    normal_distribution<> dist(mu, sig);
//    for (int i = 0; i < N; ++i) {
//        double v = dist(engine);
//        node[i] = (Node(i, v, node));
//    }
//}

void startSimulation(map<int, Node>& nodes) {
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
    output(output_texts);
}
//void startSimulation(Node nodes[N]) {
//    ofstream ofs(output_path);
//    if (!ofs.is_open()) {
//        cout << "ファイルをオープンできません" << endl;
//        return;
//    }
//
//    string output_texts[100];
//    for (int i = 0; i < 100; ++i) {
////        nodes[i].start();
//        for (int j = 0; j < N; ++j) {
//            nodes[j].move();
//        }
//        output_texts[i] = get_text(nodes, i);
//    }
//    output(nodes, output_texts);
//}

string get_text(map<int, Node>& nodes, int n) {
    string text = "t=," + to_string(n) + ",-,-\n";
    for (int i = 0; i < N; ++i) {
        text += to_string(i) + ",";
        text += to_string(nodes[i].pos.x) + ",";
        text += to_string(nodes[i].pos.y) + ",";
        text += to_string(nodes[i].v) + "\n";
    }
    return text;
}
//string get_text(Node nodes[N], int n) {
//    string text = "t=," + to_string(n) + ",-,-\n";
//    for (int i = 0; i < N; ++i) {
//        text += to_string(i) + ",";
//        text += to_string(nodes[i].pos.x) + ",";
//        text += to_string(nodes[i].pos.y) + ",";
//        text += to_string(nodes[i].v) + "\n";
//    }
//    return text;
//}

int output(string output_texts[100]) {
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
//        ofs << nodes[i].v << endl;
//    }

    for (int i = 0; i < 100; ++i) {
        ofs << output_texts[i];
    }
    ofs.close();
    return 0;
}
//int output(Node nodes[N], string output_texts[100]) {
//    ofstream ofs(output_path);
//    if (!ofs.is_open()) {
//        cout << "ファイルをオープンできません" << endl;
//        return -1;
//    }
//
//    cout << "ファイルに書き込みします" << endl;
//
////    for (int i = 0; i < N; i++) {
////        ofs << i << ",";
////        ofs << nodes[i].pos.x << ",";
////        ofs << nodes[i].pos.y << ",";
////        ofs << nodes[i].v << endl;
////    }
//
//    for (int i = 0; i < 100; ++i) {
//        ofs << output_texts[i];
//    }
//    ofs.close();
//    return 0;
//}