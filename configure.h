//
// Created by 若松一樹 on 2021/07/25.
//

#ifndef THRESHOLDBASEDALG_CONFIGURE_H
#define THRESHOLDBASEDALG_CONFIGURE_H
#define N 100
#define TIMES 10000
#define r 150
#define R 800
#define mu 70
#define sig 21
#define v_th sig
#define output_path "/Users/kazuki/Developer/CLionProjects/ThresholdBasedAlg/output/output.csv"

typedef struct {
    double x, y;
} position;

enum class STATE {
    default_,
    CH,
    CM
};

//position get_pos_lane1(double d) {
//    return position{d, 0};
//}


#endif //THRESHOLDBASEDALG_CONFIGURE_H
