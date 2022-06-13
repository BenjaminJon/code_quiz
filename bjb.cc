#include "bjb.h"
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

using namespace bjb;

template <typename V, typename E>
double VectorMatrixOps::getNumVecElements() {
    return sizeof(V)/sizeof(E);
}

template <typename M, typename V>
double VectorMatrixOps::getNumMatrixElements() {
    return sizeof(M)/sizeof(V);
}

template <typename V, typename E>
void VectorMatrixOps::ppVec(V vec) {
    double elements = getNumVecElements<V, E>();

    // Cast the structs to pointers of the right type so it can be treated like an array
    V *vecPtr = &vec;
    E *elePtr = (E *)&vecPtr[0];
    printf("[");
    for (int i = 0; i < elements; i++)
        if (i == 0)
            printf("%f", elePtr[i]);
        else
        printf(" %f", elePtr[i]);

    printf("]");
}

template <typename M, typename E>
void VectorMatrixOps::ppMatrix(M m) {

    int rows = getNumVecElements<M, E>();
    printf("[");
    for (int i = 0; i < rows; i ++) {
        if (i > 0)
            printf(" ");

        ppVec<E, vecElement_t>(m.col[i]);

        if (i == rows - 1)
            printf("]\n");
        else
            printf("\n");
    }
}

template <typename N>
void VectorMatrixOps::ppDescendents(N n) {

    typeof(N) nextNode = n;
    std::cout << "Showing data for parent node.\n";
    ppMatrix<typeof(n.data), typeof(n.data.col[0])>(n.data);

    for (int i = n.numChildren; i > 0; i--) {
        printf("Showing data for child node %d\n", i);
        nextNode = *nextNode.children;
        ppMatrix<typeof(n.data), typeof(n.data.col[0])>(nextNode.data);
    }
}

template <typename M, typename V, typename E>
void VectorMatrixOps::transposeInPlace(M *matrix) {
    int n = getNumMatrixElements<M, V>();
    int m = getNumVecElements<V, E>();

    if (n != m)
        throw std::invalid_argument( "cannot transposeInPlace with a matrix is not square." );

    for (int r = 0; r < n; r++) {
        for (int c = r; c < m; c++) {
            // Cast the structs to pointers of the right type so it can be treated like an array
            V *nPtr = &matrix->col[r];
            V *mPtr = &matrix->col[c];
            E *nValPtr = (E *)&nPtr[0];
            E *mValPtr = (E *)&mPtr[0];

            E nm = nValPtr[c];
            nValPtr[c] = mValPtr[r];
            mValPtr[r] = nm;
        }
    }
}

template <typename M, typename V, typename E>
void VectorMatrixOps::deepCopyMatrix(M *matrixCopy, M matrix) {
    int n = getNumMatrixElements<M, V>();
    int m = getNumVecElements<V, E>();

    for (int r = 0; r < n; r++) {
        // Cast the structs to pointers of the right type so it can be treated like an array
        E *vPtr = (E *)&matrix.col[r];
        E *vPtrCopy = (E *)&matrixCopy->col[r];

        for (int c = 0; c < m; c++) {
            vPtrCopy[c] = vPtr[c];
        }
    }
}

template <typename V, typename E> 
double VectorMatrixOps::calcDotProduct(V a, V b) {
    int numElements = getNumVecElements<V, E>();
    double res = 0;

    // Cast the structs to pointers of the right type so it can be treated like an array
    V *aVecPtr = &a;
    V *bVecPtr = &b;
    E *aElePtr = (E *)&aVecPtr[0];
    E *bElePtr = (E *)&bVecPtr[0];

    // Iterate through the length of the vectors and sum the products
    for (int i = 0; i < numElements; i++) {
        res += aElePtr[i]*bElePtr[i];
    }

    return res;
}