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

using namespace std;

int main(int argc, const char * argv[])
{
    const int SIZE = 2;
    //создание матриц
    Matrix<int> MyMatrix(SIZE,2);
    Matrix<int> MyMatrix1(2,SIZE);
    Matrix<int> Result(SIZE,SIZE);
    // присвоение матрице значений одним действием {{1,2},{3,4},{5,6},{7,8}}
    //cin >> MyMatrix;
    
    for (int i = 1; i <= SIZE; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+j, i, j, MyMatrix);
        }
    }
    
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= SIZE; j++)
        {
            setValue(i*j, i, j, MyMatrix1);
        }
    }
    
    cout << "Original matrix 1: \n"<< MyMatrix << "Original matrix 2: \n" << MyMatrix1;

//    Result = MyMatrix * MyMatrix1;
//    cout << "Product: \n" << MyMatrix;
    
    cout << "det MyMatrix = " << MyMatrix.determinant() << "\n";
    
//    if (Result == MyMatrix)
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
    
    return 0;
}
