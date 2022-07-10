//
// Created by lhc456 on 2022/7/10.
//
#include"SparseMatrix.h"

int main() {
    SMatrix sm, sm1;
    memset(&sm, 0, sizeof(sm));
//    memset(&sm1, 0, sizeof(sm1));

    CreateMatrix(&sm);
    PrintMatrix(&sm);

    FastTransposeMatrix(&sm, &sm1);

    PrintMatrix(&sm1);

    //CopyMatrix(&sm, &sm1);
    return 0;
}