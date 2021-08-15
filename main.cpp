#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Node.h"
#include "configure.h"

using namespace std;

set<int> get_nodes_pos();

void node_generator(set<int> &);

void start_simulation();

int output(string[TIMES]);

string get_text(int);

// main関数
int main() {
    cout << "Hello, World!" << endl;

    set<int> pos_set = get_nodes_pos();
    node_generator(pos_set);

    cout << "nodes.size():" << Node::nodes.size() << endl;
    start_simulation();
    return 0;
}

// TODO: 初期位置を{direction, lane, distance}の構造体で返すように変更
// 初期位置の集合を返す関数
set<int> get_nodes_pos() {
    random_device rnd;
    set<int> pos_set;       // 初期位置の集合
    set<int> neighbor_check;    // すぐ近くに違う初期位置がないかチェックするための集合
    cout << "0~60000の整数の乱数：" << endl;
    while (neighbor_check.size() < N) {
        int pos = (int)(rnd() % (15000 * 4));   // 後で15000m * 2車線 * 2方向に分ける
        if (!neighbor_check.count(pos / 80)) {  // 近くに違う位置がなければ
            neighbor_check.insert(pos / 80);    // 80で割った商をsetに追加
            pos_set.insert(pos);    // 実際の位置を追加
        }
        cout << pos << ", ";
    }
    cout << endl;
    return pos_set;
}

// ノードを作成
void node_generator(set<int> &pos_set) {
    cout << Node::nodes.size() << endl;
    cout << "ノードを作成します" << endl;
    random_device seed;
    mt19937 engine(seed());
    normal_distribution<> dist(mu, sig);

    auto itr = pos_set.begin();
    for (int i = 0; i < N; ++i) {
        double v = dist(engine);    // 正規分布より速度を決定
        int pos = *itr;
        itr++;
        int d = pos / 30000;        // 方向
        int l = pos / 15000 % 2;    // 車線
        double dis = pos % 15000;   // 位置
        cout << "pos:" << pos << ", lane:" << l << ", d:" << d << ", dis:" << dis << endl;
        Node::nodes[i] = Node(i, dis, d, l, v);
        Node::nodes_dl[make_pair(d, l)].push_back(&Node::nodes[i]);
    }
    cout << endl;
}

// シミュレーションを開始
void start_simulation() {
    // TODO: シミュレーションログを記録し、より多くの情報をアウトプット(LINQ検討)
    vector<map<string, double>> logs(TIMES);

    ofstream ofs(output_path);
    if (!ofs.is_open()) {
        cerr << "ファイルをオープンできません" << endl;
        return;
    }

    string output_texts[TIMES];
    for (int i = 0; i < TIMES; ++i) {
        map<string, double> log;

        cout << "t = " << i << endl;
        for (int j = 0; j < N; ++j) {
            Node::nodes[j].move();
        }
        output_texts[i] = get_text(i);
    }
    output(output_texts);
}

// csvに出力するテキストを生成
string get_text(int n) {
    string text = "t=," + to_string(n) + ",-,-\n";
    for (int i = 0; i < N; ++i) {
        text += to_string(i) + ",";
        text += to_string(Node::nodes[i].pos.x) + ",";
        text += to_string(Node::nodes[i].lane + (Node::nodes[i].direction * 2)) + ",";
        text += to_string(Node::nodes[i].v) + "\n";
    }
    return text;
}

// csvに出力
int output(string output_texts[TIMES]) {
    ofstream ofs(output_path);
    if (!ofs.is_open()) {
        cerr << "ファイルをオープンできません" << endl;
        return -1;
    }

    cout << "ファイルに書き込みします" << endl;

    for (int i = 0; i < TIMES; ++i) {
        ofs << output_texts[i];
    }
    ofs.close();
    return 0;
}
