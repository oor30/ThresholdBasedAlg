//
// Created by 若松一樹 on 2021/07/29.
//

#include "Node.h"

Node::Node() {}

Node::Node(int id, double v, Node *n, int r_n, double v_max) {
    std::random_device rnd;
    this->id = id;
    pos = {(double) (rnd() % 15000), (double) (rnd() % 10)};
    route_number = r_n;
    direction = pos.y / 5;
    this->v = v;
    nodes = n;

    lane_no = pos.y;
    this->v_max = v_max;
    a = 0;
    b = 10;
    t_delta = 0;
    t_react = 1;
}

// TODO: car-followingモデル
// TODO: 非同期処理
void Node::move() {
    pos.x += v;
    cout << pos.x << ", " << pos.y << endl;
}

// TODO: nodesのmap化