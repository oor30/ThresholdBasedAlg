#include <iostream>
#include <fstream>
#include "Node.h"
#include "configure.h"

void nodeGenerator(Node[N]);

void startSimulation(Node node[N]);

int output(Node[N]);

int main() {
    std::cout << "Hello, World!" << std::endl;
    Node nodes[N];
    nodeGenerator(nodes);
    startSimulation(nodes);
    output(nodes);
    return 0;
}

void nodeGenerator(Node node[N]) {
    std::cout << "ファイルに書き込みしますAA" << std::endl;
    std::random_device seed;
    std::mt19937 engine(seed());
//    double mu = 70, sig = 21;
    std::normal_distribution<> dist(mu, sig);
    for (int i = 0; i < N; ++i) {
        double v = dist(engine);
//        std::cout << v << std::endl;
        node[i] = (Node(i, v, node));
    }
}

void startSimulation(Node nodes[N]) {
    for (int i = 0; i < N; ++i) {
        nodes[i].start();
    }
}

int output(Node nodes[N]) {
    std::ofstream ofs("/Users/kazuki/Developer/CLionProjects/ThresholdBasedAlg/output/output.csv");
    if (!ofs.is_open()) {
        std::cout << "ファイルをオープンできません" << std::endl;
        return -1;
    }

    std::cout << "ファイルに書き込みします" << std::endl;

    for (int i = 0; i < N; i++) {
        ofs << i << ",";
        ofs << nodes[i].pos.x << ",";
        ofs << nodes[i].pos.y << ",";
        ofs << nodes[i].velocity << std::endl;
    }
    ofs.close();
    return 0;
}