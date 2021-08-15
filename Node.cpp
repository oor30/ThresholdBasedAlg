//
// Created by 若松一樹 on 2021/07/29.
//

#include <iomanip>
#include "Node.h"

// TODO: アルゴリズムを実装
// staticメンバ変数を初期化
map<int, Node> Node::nodes;
map<pair<int, int>, vector<Node *>> Node::nodes_dl;

Node::Node() = default;

Node::Node(int id, double dis, int d, int lane, double v, int r_n, double v_max) :
        id(id),             // 車のID
        dis(dis),           // 道路に沿った位置[m]
        pos(get_pos_lane1(dis)),    // 車の位置[m],[m]
        direction(d),       // 車の進行方向(0 or 1)
        lane(lane),         // 車線
        v(v),               // 車の速さ(>0)[km/h]
        route_number(r_n),  // 道路番号
        v_max(v_max),       // 車の最大速度
        a(10),              // 車の最大加速度[km/h*s]
        b(-10),             // 車の最大減速度[km/h*s]
        t_delta(0.1),       // タイムステップ[s]
        t_react(1)          // ドライバーの反応時間[s]
{}

// 車をt_delta秒後の位置に移動
void Node::move() {
    print_info();

    v = calc_desired_speed();
    if (direction == 0)dis += (v * 1000 / 3600) * t_delta;
    else dis -= (v * 1000 / 3600) * t_delta;

    pos = get_pos_lane1(dis);
}

// 数値から位置を返す関数（道路の形状を決定）
position Node::get_pos_lane1(double d) {
    return position{d, 0};
}

// この車の情報を出力
void Node::print_info() const {
    cout << right << fixed << setprecision(1);
    cout << "nodeID:" << setw(2) << id;
    cout << ",  pos.x:" << setw(8) << pos.x << ",  pos.y:" << setw(8) << pos.y;
    cout << ",  dis:" << setw(8) << dis;
    cout << ",  v:" << setw(5) << v << ",  a:" << a;
    cout << ",  lane:" << lane << ",  direction:" << direction << endl;
}

// 比較を可能にするためoperatorをオーバーライド
bool Node::operator<(const Node &another) const {
    return dis < another.dis;
}

// 車の最適な速度を計算
double Node::calc_desired_speed() const {
    // 車線上におけるこの車の位置を特定
    int index;
    vector<Node *> nodes_my_lane = nodes_dl.at(make_pair(direction, lane));
    for (int i = 0; i < nodes_my_lane.size(); ++i) {
        if (nodes_my_lane[i]->id == id) {
            index = i;      // この車の位置
            break;
        }
    }

    // 前を走る車を特定
    Node leader;    // 前の車
    bool flag = false;      // 前に車がいるかどうか
    if (direction == 0 && index + 1 < nodes_my_lane.size()) {
        leader = *nodes_my_lane[index + 1];
        flag = true;
    } else if (direction == 1 && index > 0) {
        leader = *nodes_my_lane[index - 1];
        flag = true;
    }

    // TODO: v_maxに収束してしまう問題
    // TODO: 位置、速度、加速度の単位を統一

    // 3種の速度から最も小さいものを返す
    // 1.v_max: 車の最高速度・制限速度
    double v_at = v + a * t_delta;      // 2.加速した際の速度
    double v_safe;  // 3.前の車との距離や速度に伴う安全な速度（前に車があるときのみ）
    if (flag) {
        // source: https://www.researchgate.net/publication/282987750_Research_on_car-following_model_based_on_SUMO
        double v_l = leader.v;      // 前の車の速度
        double gap = abs(leader.dis - dis) / 1000;  // 前の車との距離
        v_safe = v_l + ((gap - v_l * t_react / 3600) / (((v_l + v) / 2 / 3600 * b) + t_react));
        if (v_safe < 0) {
            cerr << "v_safeが負です";
            cerr << "(v_safe:" << v_safe << "follower:" << id << ", leader:" << leader.id << ")" << endl;
        }
        return min({v_max, v_at, v_safe});
    } else {
        return min({v_max, v_at});
    }
}