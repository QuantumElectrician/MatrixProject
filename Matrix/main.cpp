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
    //создание матрицы 2*2
    Matrix<int> MyMatrix(2,2);
    // присвоение матрице значений одним действием {{1,2},{3,4}}
    cin >> MyMatrix;
    cout << MyMatrix;
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
    //setValue(3, 1, 1, MyMatrix1);
    
    //print(MyMatrix);
    //MyMatrix1 += MyMatrix;
    //cout << MyMatrix1;
    //MyMatrix1 = MyMatrix;
    //cout << MyMatrix1;
    //cout << MyMatrix;
    
    return 0;
}
