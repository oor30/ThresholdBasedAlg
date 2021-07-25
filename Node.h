//
// Created by 若松一樹 on 2021/07/25.
//

#ifndef THRESHOLDBASEDALG_NODE_H
#define THRESHOLDBASEDALG_NODE_H

#include <iostream>
#include <set>
#include <map>
#include <random>
#include <thread>
#include "configure.h"
//#include "network.h"


using namespace std;

class Node {
private:
    std::map<int, Node> r2Stable;
    map<int, Node> r2_slower;
    map<int, Node> r2_faster;
public:
    int id;
    position pos{};
    int direction;
    double velocity;
    std::string state;
    Node *node;

    Node() {}

    Node(int i, double v, Node n[N]) {
        std::random_device rnd;
        id = i;
        pos = {(double) (rnd() % 15000), (double) (rnd() % 10), 0.0};
//        direction = rnd() % 2;
//        direction = pos.y;
        velocity = v;
        state = "default";
//        r2Stable = {};
        node = n;
//        my_mobility = neighbor_mobility(id, pos, velocity, );
    }

    void start() const {
        cout << node[N - 1].velocity << endl;
        auto th = std::thread([] { &Node::periodicalMessage; });
        th.join();
    }

    void periodicalMessage() {
        for (int i = 0; i < N; ++i) {

        }
    }

    void received_hello(Node n) {
        double v_gap = n.velocity - this->velocity;
        if (abs(v_gap) < v_th) {
            r2Stable[n.id] = n;
            if (v_gap >= 0) {
                r2_faster[n.id] = n;
            } else {
                r2_slower[n.id] = n;
            }
        }
    }

    void move() {

    }

    static double calcDist(double x, double y) {
        return x * x + y * y;
    }
};

#endif //THRESHOLDBASEDALG_NODE_H
