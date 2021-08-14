//
// Created by 若松一樹 on 2021/07/25.
//

#ifndef THRESHOLDBASEDALG_NODE_H
#define THRESHOLDBASEDALG_NODE_H

#include <iostream>
#include <set>
#include <map>
#include <vector>
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

    Node(int id, double dis, int lane, int d, double v, map<int, Node> &nodes,
         vector<Node> &nodes_by_dis_, int r_n = 0, double v_max = 150);

    void move();

    static position get_pos_lane1(double d) ;

    void print_info() const;

    bool operator<(const Node &another) const;

    double calc_desired_speed() const;
    // 車のセンサーから得られる情報
    int id{};
    double dis{};
    position pos{};
    int route_number{};
    int direction{};
    double v{};
    STATE state = STATE::default_;
//    Node *nodes;
    map<int, Node> *nodes{};
    vector<Node> *nodes_by_dis{};

    // 交通モデル用パラメータ（車自身が持たない）
    // -> クラスタリングには用いない
    int lane;
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

//    void received_hello(Node n) {
//        double v_gap = n.v - this->v;
//        if (abs(v_gap) < v_th) {
//            r2Stable[n.id] = n;
//            if (v_gap >= 0) {
//                r2_faster[n.id] = n;
//            } else {
//                r2_slower[n.id] = n;
//            }
//        }
//    }
};

#endif //THRESHOLDBASEDALG_NODE_H
