//
// Created by 若松一樹 on 2021/07/29.
//

#include <iomanip>
#include "Node.h"

map<pair<int, int>, vector<Node*>> Node::nodes_dl;

Node::Node() = default;

Node::Node(int id, double dis, int lane, int d, double v,
           vector<Node> &nodes_by_dis, int r_n, double v_max) :
        id(id),
        dis(dis),           // 道路に沿った位置[m]
        pos(get_pos_lane1(dis)),    // 車の位置[m],[m]
        lane(lane),         // 車線
        direction(d),       // 車の進行方向(0 or 1)
        v(v),               // 車の速さ(>0)[km/h]
        route_number(r_n),  // 道路番号
//        nodes(&nodes),
        nodes_by_dis(&nodes_by_dis),
//        nodes_lane(&nodes_lane),
        v_max(v_max),       // 車の最大速度
        a(10),              // 車の最大加速度[km/h*s]
        b(-10),             // 車の最大減速度[km/h*s]
        t_delta(0.1),       // タイムステップ[s]
        t_react(1)          // ドライバーの反応時間[s]
{}

// TODO: car-followingモデル
// TODO: 非同期処理
void Node::move() {
    print_info();

    v = calc_desired_speed();
    if (direction == 0)dis += (v * 1000 / 3600) * t_delta;
    else dis -= (v * 1000 / 3600) * t_delta;

    pos = get_pos_lane1(dis);
}

position Node::get_pos_lane1(double d) {
    return position{d, 0};
}

void Node::print_info() const {
    cout << right << fixed << setprecision(1);
    cout << "nodeID:"<< setw(2) << id;
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
    // TODO: グローバル変数ではなくstaticメンバ変数または仮引数にするのもあり？
    extern map<int, Node> nodes;
//    extern vector<vector<vector<Node*>>> nodes_lane;
    vector<Node*> nodes_my_lane = nodes_dl.at(make_pair(direction, lane));
//    vector<Node*> nodes_my_lane = nodes_lane[direction][lane];
    for (int i = 0; i < nodes_my_lane.size(); ++i) {
        if (nodes_my_lane[i]->id == id) {
            index = i;
            break;
        }
    }
//    int index;
//    for (int i = 0; i < N; ++i) {
//        if ((*nodes_by_dis)[i].id == id) {
//            index = i;
//            break;
//        }
//    }

    Node leader;
    bool flag = false;
    if (direction == 0 && index+1 < nodes_my_lane.size()) {
        leader = *nodes_my_lane[index+1];
        flag = true;
    }
    else if (direction == 1 && index > 0) {
        leader = *nodes_my_lane[index-1];
        flag = true;
    }
//    if (direction == 0) {
//        for (int i = index + 1; i < N; ++i) {
//            if ((*nodes_by_dis)[i].lane == lane) {
//                leader = (*nodes_by_dis)[i];
//                flag = true;
//                break;
//            }
//        }
//    } else {
//        for (int i = index - 1; i < 0; --i) {
//            if ((*nodes_by_dis)[i].lane == lane) {
//                leader = (*nodes_by_dis)[i];
//                flag = true;
//                break;
//            }
//        }
//    }
    double v_safe;
    double v_at = v + a * t_delta;
    if (flag) {
        // source: Researchoncar-followingmodelbasedonSUMO_SongJie.pdf
        double v_l = leader.v;
        double gap = abs(leader.dis - dis) / 1000;
        v_safe = v_l + ((gap - v_l * t_react / 3600) / (((v_l + v) / 2 / 3600 * b) + t_react));
        if (v_safe < 0) {
            cout << "v_safeが負です";
            cout << "(follower:" << id << ", leader:" << leader.id << ")" << endl;
        }
        return min({v_max, v_at, v_safe});
    } else {
        return min({v_max, v_at});
    }
}