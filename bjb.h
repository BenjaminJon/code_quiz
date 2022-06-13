#ifndef BJB_H
#define BJB_H

namespace bjb {
    typedef double vecElement_t;

    typedef struct Vec3 {
        vecElement_t x, y, z;
    } V3_t;

    typedef struct Mat33 {
        V3_t col[3];
    } M33_t;

    typedef struct Vec4 {
        vecElement_t w, x, y, z;
    } V4_t;

    typedef struct Mat44 {
        V4_t col[4];
    } M44_t;

    typedef struct Mat43 {
        V3_t col[4];
    } M43_t;

    typedef struct Node33 {
        M33_t data;
        Node33 *children;
        unsigned int numChildren;
    } N33_t;

    /*
        Use function templating for all matrix methods so that:
        1. The logic can be extended to arbitrary M and V dimensions
        2. The logic can iterate through all of it's elements without
           requiring any prior knowledge of the VecX member names.
    */
    class VectorMatrixOps {

        public:
            template <typename V, typename E> 
            double getNumVecElements();

            template <typename M, typename V>
            double getNumMatrixElements();

            template <typename V, typename E>
            void ppVec(V vec);

            template <typename M, typename E>
            void ppMatrix(M m);

            template <typename N>
            void ppDescendents(N n);

            template <typename M, typename V, typename E> 
            void transposeInPlace(M *matrix);

            template <typename M, typename V, typename E>
            void deepCopyMatrix(M *matrixCopy, M matrix);

            template <typename V, typename E> 
            double calcDotProduct(V a, V b);
    };
}
#endif /* BJB_H */