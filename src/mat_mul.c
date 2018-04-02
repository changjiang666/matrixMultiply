#include "mat_mul.h"
#include "alloc.h"
#include <stdio.h>  //for printf
#define S_NUM 10
#define SON_MAT 4
#define P_NUM 7
#define ADD 0
#define SUB 1

/*
**暴力法的初始化操作，matA, matB都是指向数组的指针
*/
void
init_Force(int (*const matA)[SIZE], int (*const matB)[SIZE])
{
    int i, j;
    for(i = 0; i < SIZE; ++i)
    {
        for(j = 0; j < SIZE; ++j)
        {
            matA[i][j] = 1;
            matB[i][j] = 1;
        }
    }
}


/*
**显示结果，由于不想使得matC被意外改变，所以设置为const
*/
void
show_Result(int const (*const matC)[SIZE])
{
    int i, j;
    for(i = 0; i < SIZE; ++i)
    {
        for(j = 0; j < SIZE; ++j)
        {
            printf("%4d", matC[i][j]);
        }
        printf("\n");
    }
}



/*
**暴力法求解过程，返回指向数组的指针matC, 具体的内存存放在动态内存
**传入的参数matA, matB都是指向数组的指针
**遍历matA, matB的每一个元素，按照矩阵乘法的定义进行计算
**由于有三层for循环，每层循环执行n次， 因此时间复杂度为O（n^3）
*/
int
(*brute_Force(int const (*const matA)[SIZE], int const (*const matB)[SIZE]))[SIZE]
{
    int (*matC)[SIZE] = alloc(SIZE * SIZE * sizeof(int));
    int i, j, k;
    for(i = 0; i < SIZE; ++i)
        for(j = 0; j < SIZE; ++j)
            {
                matC[i][j] = 0;
                for(k = 0; k < SIZE; ++k)
                    matC[i][j] += matA[i][k] * matB[k][j];
            }
    return matC;
}



/*
**矩阵的加减运行, matA, matB, matC均为二维指针, num 是数组的维数， flag为0执行加法运算，为1执行减法
*/
void
add_sub(int **matA, int **matB, int **matC, int num, int flag)
{
    int i, j;
    for(i = 0; i < num; ++i)
    {
        for(j = 0; j < num; ++j)
        {

            matC[i][j] = (ADD == flag) ? matA[i][j] + matB[i][j] : matA[i][j] - matB[i][j];
        }
    }
}


/*
**Srassen方法的初始化
**可以输入来确定矩阵的维度
*/
void init_Stra(int **matA, int **matB, int num)
{
    int i, j;
    for(i = 0; i < num; ++i)
    {
        for(j = 0; j < num; ++j)
        {
            matA[i][j] = 2;
            matB[i][j] = 2;
        }
    }
}


/*
**Strassen求解矩阵
*/
int **
Strassen(int **matA, int **matB, int num)
{
    int i, j;
    int **matC;
    matC = (int **)alloc(sizeof(int *) * num);
    for(i = 0; i < num; ++i)
    {
        matC[i] = (int *)alloc(sizeof(int) * num);
    }

    if(1 == num)
    {
        matC[0][0] = matA[0][0] * matB[0][0];
        return matC;
    }

    int **A[SON_MAT], **B[SON_MAT];
    int **S[S_NUM];
    for(i = 0; i < SON_MAT; ++i)
    {
        A[i] = (int **)alloc(sizeof(int *) * num / 2);
        B[i] = (int **)alloc(sizeof(int *) * num / 2);
        for(j = 0; j < num / 2; ++j)
        {
            A[i][j] = (int *)alloc(sizeof(int) * num / 2);
            B[i][j] = (int *)alloc(sizeof(int) * num / 2);
        }
    }
    for(i = 0; i < S_NUM; ++i)
    {
        S[i] = (int **)alloc(sizeof(int *) * num / 2);
        for(j = 0; j < num / 2; ++j)
        {
            S[i][j] = (int *)alloc(sizeof(int) * num / 2);
        }
    }


    for(i = 0; i < num / 2; ++i)
    {
        for(j = 0; j < num / 2; ++j)
        {
            A[0][i][j] = matA[i][j];
            A[1][i][j] = matA[i ][j + num / 2];
            A[2][i][j] = matA[i + num / 2][j];
            A[3][i][j] = matA[i + num / 2][j + num / 2];
            B[0][i][j] = matB[i][j];
            B[1][i][j] = matB[i ][j + num / 2];
            B[2][i][j] = matB[i + num / 2][j];
            B[3][i][j] = matB[i + num / 2][j + num / 2];
        }
    }

    add_sub(B[1], B[3], S[0], num / 2, SUB);
    add_sub(A[0], A[1], S[1], num / 2, ADD);
    add_sub(A[2], A[3], S[2], num / 2, ADD);
    add_sub(B[2], B[0], S[3], num / 2, SUB);
    add_sub(A[0], A[3], S[4], num / 2, ADD);
    add_sub(B[1], B[3], S[5], num / 2, ADD);
    add_sub(A[1], A[3], S[6], num / 2, SUB);
    add_sub(B[2], B[3], S[7], num / 2, ADD);
    add_sub(A[0], A[2], S[8], num / 2, SUB);
    add_sub(B[0], B[1], S[9], num / 2, ADD);


    int **P[P_NUM];
    for(i = 0; i < P_NUM; ++i)
    {
        P[i] = (int **)alloc(sizeof(int *) * num / 2);
        for(j = 0; j < num / 2; ++j)
        {
            P[i][j] = (int *)alloc(sizeof(int) * num / 2);
        }
    }

    P[0] = Strassen(A[0], S[0], num / 2);
    P[1] = Strassen(S[1], B[3], num / 2);
    P[2] = Strassen(S[2], B[0], num / 2);
    P[3] = Strassen(A[3], S[3], num / 2);
    P[4] = Strassen(S[4], S[5], num / 2);
    P[5] = Strassen(S[6], S[7], num / 2);
    P[6] = Strassen(S[8], S[9], num / 2);


    int **C[SON_MAT];
    for(i = 0; i < SON_MAT; ++i)
    {
        C[i] = (int **)alloc(sizeof(int *) * num / 2);
        for(j = 0; j < num / 2; ++j)
        {
            C[i][j] = (int *)alloc(sizeof(int) * num / 2);
        }
    }

    add_sub(P[4], P[3], C[0], num / 2, ADD);
    add_sub(C[0], P[1], C[0], num / 2, SUB);
    add_sub(C[0], P[5], C[0], num / 2, ADD);

    add_sub(P[0], P[1], C[1], num / 2, ADD);

    add_sub(P[2], P[3], C[2], num / 2, ADD);

    add_sub(P[4], P[0], C[3], num / 2, ADD);
    add_sub(C[3], P[2], C[3], num / 2, SUB);
    add_sub(C[3], P[6], C[3], num / 2, SUB);

    for(i = 0; i < num / 2; ++i)
    {
        for(j = 0; j < num /2; ++j)
        {
            matC[i][j] = C[0][i][j];
            matC[i + num / 2][j] = C[2][i][j];
            matC[i][j + num / 2] = C[1][i][j];
            matC[i + num / 2][j + num / 2] = C[3][i][j];
        }
    }

    return matC;
}

