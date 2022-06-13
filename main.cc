#include "bjb.h"
#include "bjb.cc"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace bjb;

void testDescendents() {
    VectorMatrixOps vOps;
    V3_t a = {1.5, -5, 18};
    V3_t b = {2, 6, -9.2};
    V3_t c = {-8, 3, 1};
    V3_t d = {6, 7, 8};
    V3_t e = {9, 10, 11};
    M33_t m1 = {a, b, c};
    M33_t m2 = {b, c, d};
    M33_t m3 = {c, d, e};
    N33_t n1 = {m1, nullptr, 0};
    N33_t n2 = {m2, &n1, 0};
    N33_t n3 = {m3, &n2, 2};

    std::cout << "\n\nTesting descendents:\n";
    vOps.ppDescendents<N33_t>(n3);
}

void testM4() {
    VectorMatrixOps vOps;
    V4_t v1 = {1, 2, 3, 4};
    V4_t v2 = {-1, -2, -3, -4};
    V4_t v3 = {5, 6, 7, 8};
    V4_t v4 = {-5, -6, -7, -8};
    M44_t m1 = {v1, v2, v3, v4};

    std::cout << "\n\nShowing dot product for V4:\n";
    double dotProd = vOps.calcDotProduct<V4_t, vecElement_t>(v1, v2);
    vOps.ppVec<V4_t, vecElement_t>(v1);
    printf(" * ");
    vOps.ppVec<V4_t, vecElement_t>(v2);
    printf(" = %f\n", dotProd);

    std::cout << "Showing original M4:\n";
    vOps.ppMatrix<M44_t, V4_t>(m1);
    vOps.transposeInPlace<M44_t, V4_t, vecElement_t>(&m1);
    std::cout << "Shpowing transposed matrix:\n";
    vOps.ppMatrix<M44_t, V4_t>(m1);

}

int main() {
    VectorMatrixOps vOps;

    V3_t a = {1.5, -5, 18};
    V3_t b = {2, 6, -9.2};
    V3_t c = {-8, 3, 1};
    M33_t m = {a, b, c};
    M33_t mOrig;
    M43_t m43 = {a, b, c, a};

    if (1) {
        std::cout << "Testing the dot product func:\n";
        double dotProd = vOps.calcDotProduct<V3_t, vecElement_t>(a, b);
        vOps.ppVec<V3_t, vecElement_t>(a);
        printf(" * ");
        vOps.ppVec<V3_t, vecElement_t>(b);
        printf(" = %f\n", dotProd);
    }
    
    if (1) {
        vOps.deepCopyMatrix<M33_t, V3_t, vecElement_t>(&mOrig, m);

        printf("M33\n");
        vOps.ppMatrix<M33_t, V3_t>(m);
        printf("Transposed M33\n");
        vOps.transposeInPlace<M33_t, V3_t, vecElement_t>(&m);
        vOps.ppMatrix<M33_t, V3_t>(m);
        printf("M33 Deep copy\n");
        vOps.ppMatrix<M33_t, V3_t>(mOrig);
    }

    if (1)
        testDescendents();

    if (1)
        testM4();

    if (1)
        vOps.transposeInPlace<M43_t, V3_t, vecElement_t>(&m43);
}