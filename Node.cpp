//
// Created by 若松一樹 on 2021/07/29.
//

#include <iomanip>
#include "Node.h"

Node::Node() = default;

Node::Node(int id, double dis, int lane, int d, double v, map<int, Node> &nodes,
           vector<Node> &nodes_by_dis, int r_n, double v_max) :
        id(id),
        dis(dis),
        pos(get_pos_lane1(dis)),
        lane(lane),
        direction(d),
        v(v),
        route_number(r_n),
        nodes(&nodes),
        nodes_by_dis(&nodes_by_dis),
        v_max(v_max),
        a(5),
        b(10),
        t_delta(1),
        t_react(1) {
//    this->id = id;
//    this->dis = dis;
//    this->pos = get_pos_lane1(dis);
//    this->lane = lane;
//    direction = d;
//    this->v = v;
//    route_number = r_n;
//    this->nodes = nodes;
//    this->nodes_by_dis = &nodes_by_dis;
//
//    this->v_max = v_max;
//    a = 0;
//    b = 10;
//    t_delta = 0;
//    t_react = 1;
}

// TODO: car-followingモデル
// TODO: 非同期処理
void Node::move() {
    print_info();

    v = calc_desired_speed();
    if (direction == 0)dis += v;
    else dis -= v;

    pos = get_pos_lane1(dis);
}

position Node::get_pos_lane1(double d) {
    return position{d, 0};
}

void Node::print_info() const {
    cout << right << fixed << setprecision(1);
    cout << "nodeID:" << id;
    cout << ",  pos.x:" << setw(8) << pos.x << ",  pos.y:" << setw(8) << pos.y;
    cout << ",  dis:" << setw(8) << dis;
    cout << ",  v:" << setw(5) << v << ",  a:" << a;
    cout << ",  lane:" << lane << ",  direction:" << direction << endl;
}

bool Node::operator<(const Node &another) const {
    return dis < another.dis;
}

double Node::calc_desired_speed() const {
    int index;
    for (int i = 0; i < N; ++i) {
        if ((*nodes_by_dis)[i].id == id) {
            index = i;
            break;
        }
    }
    Node leader;
    bool flag = false;
    if (direction == 0) {
        for (int i = index + 1; i < N; ++i) {
            if ((*nodes_by_dis)[i].lane == lane) {
                leader = (*nodes_by_dis)[i];
                flag = true;
                break;
            }
        }
    } else {
        for (int i = index - 1; i < 0; --i) {
            if ((*nodes_by_dis)[i].lane == lane) {
                leader = (*nodes_by_dis)[i];
                flag = true;
                break;
            }
        }
    }
    double v_safe;
    double v_at = v + a * t_delta;
    if (flag) {
        double v_l = leader.v;
        double gap = abs(v_l - v);
        v_safe = v_l + ((gap - v_l * t_react) / ((v_l + v) / 2 * b) + t_react);
        return min({v_max, v_at, v_safe});
    } else {
        return min({v_max, v_at});
    }
}