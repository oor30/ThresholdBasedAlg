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

    Node(int, double, int, int, double, int r_n = 0, double v_max = 120);

    void move();

    static position get_pos_lane1(double d);

    void print_info() const;

    bool operator<(const Node &another) const;

    double calc_desired_speed() const;

    // 車のセンサーから得られる情報
    int id{};           // 車のID
    double dis{};       // 道路に沿った位置[m]
    position pos{};     // 車の位置[m],[m]
    int direction{};    // 車の進行方向(0 or 1)
    double v{};         // 車の速さ(>0)[km/h]
    int route_number{};     // 道路番号
    STATE state = STATE::default_;      // 車の役割（default/CH/CM）
    static map<int, Node> nodes;        // すべての車のコンテナ

    // 交通モデル用パラメータ（車自身が持たない）
    // -> クラスタリングには用いない
    static map<pair<int, int>, vector<Node *>> nodes_dl;    // 同一車線上の車のコンテナ
    int lane{};             // 車線
    double v_max = 120;     // 車の最大速度
    double a = 10;          // 車の最大加速度[km/h*s]
    double b = -10;         // 車の最大減速度[km/h*s]
    double t_delta = 0.1;   // 移動のタイムステップ[s]
    double t_react = 1;     // ドライバーの反応時間[s]
};

#endif //THRESHOLDBASEDALG_NODE_H
