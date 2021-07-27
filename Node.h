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
    Node *nodes;
    double v_max;

    Node() {}

    Node(int i, double v, Node n[N], double v_m = 150) {
        std::random_device rnd;
        id = i;
        pos = {(double) (rnd() % 15000), (double) (rnd() % 10), 0.0};
//        direction = rnd() % 2;
//        direction = pos.y;
        velocity = v;
        state = "default";
//        r2Stable = {};
        nodes = n;
//        my_mobility = neighbor_mobility(id, pos, velocity, );
        v_max = v_m;
    }

    void start() const {
//        cout << nodes[N - 1].velocity << endl;
//        auto th = std::thread([] { &Node::periodicalMessage; });
//        th.join();
//        thread th1([this]() { this->move(); });
////        auto th1 = thread([] { &Node::move; });
//        th1.join();

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

    // TODO: car-followingモデル
    // TODO: 非同期処理
    void move() {
        pos.x += velocity;
        cout << pos.x << ", " << pos.y << endl;
    }

    void calcDesiredSpeed() {

    }
};

#endif //THRESHOLDBASEDALG_NODE_H
