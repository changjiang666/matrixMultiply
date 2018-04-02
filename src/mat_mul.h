#ifndef MAT_MUL_H_
#define MAT_MUL_H_
#define SIZE 16     //define matrix size

//�������ṩ�Ľӿ�
void init_Force(int (*const matA)[SIZE], int (*const matB)[SIZE]);
void show_Result(int const (*const matC)[SIZE]);
int (*brute_Force(int const (*const matA)[SIZE], int const (*const matB)[SIZE]))[SIZE];


//Strassen���ṩ�Ľӿ�
void init_Stra(int **matA, int **matB, int num);
int **Strassen(int **matA, int **matB, int num);

#endif // MAT_MUL_H_
