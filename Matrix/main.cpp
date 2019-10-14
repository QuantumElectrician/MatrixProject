// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//
//  main.cpp
//  Matrix
//
//  Created by Владислав Агафонов on 19/09/2019.
//  Copyright © 2019 Владислав Агафонов. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

#include "Definition.hpp"

#define TYPE float

using namespace std;

int main(int argc, const char * argv[])
{
    const int SIZE = 3;
    //создание матриц
    Matrix<TYPE> MyMatrix(SIZE,SIZE);
    Matrix<TYPE> MyMatrix1(SIZE,SIZE);
    Matrix<TYPE> Result(SIZE,SIZE);
    // присвоение матрице значений одним действием {{1,2},{3,4},{5,6},{7,8}}
    //cin >> MyMatrix;
    
    for (int i = 1; i <= SIZE; i++)
    {
        for (int j = 1; j <= SIZE; j++)
        {
            setValue(i+j, i, j, MyMatrix);
        }
    }
    
    for (int i = 1; i <= SIZE; i++)
    {
        for (int j = 1; j <= SIZE; j++)
        {
            setValue(i*j, i, j, MyMatrix1);
        }
    }
    
    for (int i = 1; i <= SIZE; i++)
    {
        for (int j = 1; j <= SIZE; j++)
        {
            setValue(i*j, i, j, Result);
        }
    }
    
    setValue(10, 1, 1, MyMatrix);
    
//    cout << MyMatrix1 << Result;
//    MyMatrix = MyMatrix1 + Result;
//    cout << MyMatrix << MyMatrix1;
    
    //cout << "Original matrix: \n"<< MyMatrix << "Original matrix1: \n" << MyMatrix1;
    //cout << "Original matrix: \n"<< MyMatrix << MyMatrix.upTriangle();
    
//    double results[3];
//    MyMatrix.gauss(results);
//    cout << "RESULTS: \n";
//    for (auto index : results)
//    {
//        cout << index << "\n";
//    }
    
    //    Result = MyMatrix * MyMatrix1;
    //    cout << "Product: \n" << MyMatrix;
    
    cout << MyMatrix;
    cout << "UpTriangle MyMatrix: \n" << MyMatrix.diag().makeBeautiful();
    //cout << "det MyMatrix = " << MyMatrix.determinant() << "\n";
    
//    if (MyMatrix1 == MyMatrix)
//    {
//        cout << "TRUE\n";
//    }
//    else
//    {
//        cout << "FALSE\n";
//    }
    
    //MyMatrix = MyMatrix1;
    //transpose1Arg(MyMatrix1);
    //transpose2Arg(MyMatrix, MyMatrix);
    //cout << "Original matrix: \n"<< MyMatrix1 << "Transposed matrix: \n" << MyMatrix;
    
    //cout << Transpose(MyMatrix);
    
    //MyMatrix = {{1,2},{3,4}};
    //Matrix<int> MyMatrix1(10, 10);

    //Matrix<int> MyMatrix;
    //можно получить указатель на матрицу
    //int** p = MyMatrix.getPointer();
    
    //2 опции вывода: << или print(<class_matrix>)
    //print(MyMatrix);
    //cout << MyMatrix;
    
    //инициализация элемента [i][j] по запросу
    //setValue(5, 1, 1, MyMatrix);
    //cout << MyMatrix;
    
    //print(MyMatrix);
    //MyMatrix1 += MyMatrix;
    //cout << MyMatrix1;
    //MyMatrix1 = MyMatrix;
    //cout << MyMatrix1;
    //cout << MyMatrix;
    
    
    MyMatrix1.~Matrix();
    Result.~Matrix();
    MyMatrix.~Matrix();
    return 0;
}
