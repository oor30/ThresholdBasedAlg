//
// Created by 若松一樹 on 2021/07/25.
//

#ifndef THRESHOLDBASEDALG_CONFIGURE_H
#define THRESHOLDBASEDALG_CONFIGURE_H
#define N 400
#define r 150
#define R 800
#define mu 70
#define sig 21
#define v_th sig
#define output_path "/Users/kazuki/Developer/CLionProjects/ThresholdBasedAlg/output/output.csv"

typedef struct {
    double x, y, z;
} position;

class neighbor_mobility {
    int id;
    position pos;
    double velocity;
    int direction;
    int nodal_degree;

    neighbor_mobility(int i, position p, double v, int d, int n) {
        id = i;
        pos = p;
        velocity = v;
        direction = d;
        nodal_degree = n;
    }
};

#endif //THRESHOLDBASEDALG_CONFIGURE_H
