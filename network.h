//
// Created by 若松一樹 on 2021/07/25.
//

#ifndef THRESHOLDBASEDALG_NETWORK_H
#define THRESHOLDBASEDALG_NETWORK_H

#include "Node.h"
#include "configure.h"

using namespace std;

class Network {
public:
    Node *nodes;

    Network(Node n[N]) {
        nodes = n;
    }

    void send_hello(Node node) {
        for (int i = 0; i < N; ++i) {
            dist = calc_dist(node.pos, nodes[i].pos)
            if (0 < dist || dist < r * 2) {

            }
        }
    }

    double calc_dist(position p1, position p2) {
        return pow(p1.x - p2.x) + pow(p1.y - p2.y);
    }
};

#endif //THRESHOLDBASEDALG_NETWORK_H
