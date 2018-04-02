#include <stdio.h>
#include <stdlib.h>
#include "mat_mul.h"

int
main(void)
{
    //����ע�Ͳ��ֲ��Ա���������ȷ��
    //matA, matB, matC �ڶ���, main�����Ķ�ջ��ֻ�����˶�Ӧ�ĵ�ָ��
//    int (*matA)[SIZE], (*matB)[SIZE], (*matC)[SIZE];
//    matA = alloc(SIZE * SIZE * sizeof(int));
//    matB = alloc(SIZE * SIZE * sizeof(int));
//    matC = alloc(SIZE * SIZE * sizeof(int));
//
//    init_Force(matA, matB);           //init matA, matB
//    matC = brute_Force(matA, matB);     //compute matC
//    show_Result(matC);        //show result matC

    int i, j;
    int const num = 32;
    int **matA, **matB, **matC;
    matA = (int **)alloc(sizeof(int *) * num);
    matB = (int **)alloc(sizeof(int *) * num);
    for(i = 0; i < num; ++i)
    {
        matA[i] = (int *)alloc(sizeof(int) * num);
        matB[i] = (int *)alloc(sizeof(int) * num);
    }

    init_Stra(matA, matB, num);

    matC = Strassen(matA, matB, num);
    for(i = 0; i < num; ++i)
    {
        for(j = 0; j < num ; ++j)
        {
            printf("%4d", matC[i][j]);
        }
        printf("\n");
    }


    return EXIT_SUCCESS;       // return OS the ERROR code or SUCCESS code
}

