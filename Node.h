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


using namespace std;

class Node {
    // クラスタリング用変数（車自身が持つ）
private:

// 周囲の車のリスト
    std::map<int, Node> r2Stable;
    map<int, Node> r2_slower;
    map<int, Node> r2_faster;
public:
    Node();
    Node(int id, double v, map<int, Node> nodes, int r_n = 0, double v_max = 150);
//    Node(int id, double v, Node *n, int r_n = 0, double v_max = 150);
    void move();
    // 車のセンサーから得られる情報
    int id;
    position pos{};
    int route_number;
    int direction;
    double v;
    STATE state = STATE::default_;
//    Node *nodes;
    map<int, Node> nodes;

    // 交通モデル用パラメータ（車自身が持たない）
    // -> クラスタリングには用いない
    int lane_no;
    double v_max;
    double a;
    double b;
    double t_delta;
    double t_react;

    void start() const {
//        cout << nodes[N - 1].v << endl;
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
        double v_gap = n.v - this->v;
        if (abs(v_gap) < v_th) {
            r2Stable[n.id] = n;
            if (v_gap >= 0) {
                r2_faster[n.id] = n;
            } else {
                r2_slower[n.id] = n;
            }
        }
    }

//    double calcDesiredSpeed() {
//        double v_at = v + a * t_delta;
//        double v_safe = v_l + ((gap - v_l * t_react)/((v_l + v)/2 * b) + t_react);
//        return min({v_max, v_at, v_safe});
//    }
};

#endif //THRESHOLDBASEDALG_NODE_H
