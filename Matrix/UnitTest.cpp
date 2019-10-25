// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
//  UnitTest.cpp
//  Matrix
//
//  Created by Владислав Агафонов on 24/10/2019.
//  Copyright © 2019 Владислав Агафонов. All rights reserved.
//
#include "UnitTest.hpp"
#include "Definition.hpp"

void Tests::TestsOperator()
{
    cout << "\n-------------------\n-------------------\nGreetings from the Unit Test Module\n" << "Section:Operators";
    cout << "\nMatrices to test:\n-------------------\n";
    Matrix<int> MyIntMatrixSq(2,2);
    Matrix<int> MyIntMatrix(1,3);
    Matrix<int> MyIntMatrix1(3,1);
    Matrix<int> MyIntMatrix2(2,2);
    
    //matrix initialization
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+2*j, i, j, MyIntMatrixSq);
        }
    }
    setValue(10, 2, 1, MyIntMatrixSq);

    for (int i = 1; i <= 1; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            setValue(i+2*j, i, j, MyIntMatrix);
        }
    }
    setValue(10, 1, 2, MyIntMatrix);

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 1; j++)
        {
            setValue(2*i+j, i, j, MyIntMatrix1);
        }
    }
    setValue(10, 3, 1, MyIntMatrix1);
    
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+2*j, i, j, MyIntMatrix2);
        }
    }
    setValue(10, 2, 1, MyIntMatrix2);

    cout << "MyIntMatrixSq:\n" << MyIntMatrixSq << "MyIntMatrix:\n" << MyIntMatrix << "MyIntMatrix1:\n" << MyIntMatrix1;
    
    //SetValue check
    assert( MyIntMatrixSq.getValue(2,1) == 10 );
    assert( MyIntMatrix.getValue(1,2) == 10 );
    assert( MyIntMatrix1.getValue(3,1) == 10 );
    
    //!= operator check
    assert( MyIntMatrix != MyIntMatrix1 );
    
    //+ operator check
    setValue(6, 1, 1, MyIntMatrix2);
    setValue(10, 1, 2, MyIntMatrix2);
    setValue(20, 2, 1, MyIntMatrix2);
    setValue(12, 2, 2, MyIntMatrix2);
    assert(MyIntMatrix2 == MyIntMatrixSq + MyIntMatrixSq);
    
    //- operator check
    setValue(0, 1, 1, MyIntMatrix2);
    setValue(0, 1, 2, MyIntMatrix2);
    setValue(0, 2, 1, MyIntMatrix2);
    setValue(0, 2, 2, MyIntMatrix2);
    assert(MyIntMatrix2 == MyIntMatrixSq - MyIntMatrixSq);
    
    //* operator check && resize function check
    setValue(129, 1, 1, MyIntMatrix2);
    resize(MyIntMatrix2, 1, 1);
    assert(MyIntMatrix2 == MyIntMatrix*MyIntMatrix1);
    
    //= operator check
    MyIntMatrix2 = MyIntMatrix1;
    assert(MyIntMatrix2 == MyIntMatrix1);
    
    //*double operator check
    double randomNumber = 5;
    MyIntMatrix2 *= randomNumber;
    setValue(15, 1, 1, MyIntMatrix1);
    setValue(25, 2, 1, MyIntMatrix1);
    setValue(50, 3, 1, MyIntMatrix1);
    assert(MyIntMatrix2 == MyIntMatrix1);
    
    cout << "All operator tests were passed succesfully\n-------------------\n";
}

void Tests::TestsFunctions()
{
    double EPS = 1e-5;
    cout << "\n-------------------\n-------------------\nGreetings from the Unit Test Module\n" << "Section: Functions\n";
    cout << "\nMatrices to test:\n-------------------\n";
    Matrix<float> MyFloatMatrixSq(2,2);
    Matrix<float> MyFloatMatrix(1,3);
    Matrix<float> MyFloatMatrix1(2,1);
    Matrix<float> MyFloatMatrix2(2,2);
    
    //matrix initialization
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+2*j, i, j, MyFloatMatrixSq);
        }
    }
    setValue(10, 2, 1, MyFloatMatrixSq);
    
    for (int i = 1; i <= 1; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            setValue(i+2*j, i, j, MyFloatMatrix);
        }
    }
    setValue(10, 1, 2, MyFloatMatrix);
    
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 1; j++)
        {
            setValue(2*i+j, i, j, MyFloatMatrix1);
        }
    }
    setValue(10, 1, 1, MyFloatMatrix1);
    
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+2*j, i, j, MyFloatMatrix2);
        }
    }
    setValue(10, 2, 1, MyFloatMatrix2);
    
    cout << "MyFloatMatrixSq:\n" << MyFloatMatrixSq << "MyFloatMatrix:\n" << MyFloatMatrix
            << "MyFloatMatrix1:\n" << MyFloatMatrix1;
    
    //upTriangle check
    MyFloatMatrixSq.upTriangle();
    assert ( (abs(MyFloatMatrixSq.getValue(1,1) - 10) < EPS )&&(abs(MyFloatMatrixSq.getValue(1,2) - 6) < EPS )&&
            (abs(MyFloatMatrixSq.getValue(2,1) - 0) < EPS )&&(abs(MyFloatMatrixSq.getValue(2,2) + 3.2) < EPS )
           );
    
    //diag check
    MyFloatMatrixSq.diag();
    assert ( (abs(MyFloatMatrixSq.getValue(1,1) - 10) < EPS )&&(abs(MyFloatMatrixSq.getValue(1,2) - 0) < EPS )&&
             (abs(MyFloatMatrixSq.getValue(2,1) - 0) < EPS )&&(abs(MyFloatMatrixSq.getValue(2,2) + 3.2) < EPS )
           );
    
    //determinant section check
        //determinant for a triangular matrix
    assert( abs(MyFloatMatrixSq.determinantTriangl() + 32) < EPS );
        //matrix reinitialization to check default determinant
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+2*j, i, j, MyFloatMatrixSq);
        }
    }
    setValue(10, 2, 1, MyFloatMatrixSq);
        //general floating point matrix determinant
    assert( abs(MyFloatMatrixSq.determinantFloatingPoint() + 32) < EPS );
    
    //concate check
    MyFloatMatrixSq.concate(MyFloatMatrix1);
    assert ( (abs(MyFloatMatrixSq.getValue(1,1) - 3) < EPS )&&(abs(MyFloatMatrixSq.getValue(1,2) - 5) < EPS )&&
             (abs(MyFloatMatrixSq.getValue(2,1) - 10) < EPS )&&(abs(MyFloatMatrixSq.getValue(2,2) - 6) < EPS ) &&
             (abs(MyFloatMatrixSq.getValue(1,3) - 10) < EPS )&&(abs(MyFloatMatrixSq.getValue(2,3) - 5) < EPS )
           );
    
    //gauss check
    vector<float> gaussResults(2,0);
    gaussResults = MyFloatMatrixSq.gauss();
    assert ( ( abs(gaussResults[0] + 1.09375) < EPS ) && ( abs(gaussResults[1] - 2.65625) < EPS ) );
    
    //invert check
    resize(MyFloatMatrixSq, 2, 2);
        //matrix reinitialization
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+2*j, i, j, MyFloatMatrixSq);
        }
    }
    setValue(10, 2, 1, MyFloatMatrixSq);
    MyFloatMatrixSq.invert();
    assert ( (abs(MyFloatMatrixSq.getValue(1,1) + 0.1875) < EPS )&&(abs(MyFloatMatrixSq.getValue(1,2) - 0.15625) < EPS )&&
            (abs(MyFloatMatrixSq.getValue(2,1) - 0.3125) < EPS )&&(abs(MyFloatMatrixSq.getValue(2,2) + 0.09375) < EPS )
            );
    
    //eraseColums check
        //matrix reinitialization
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; j <= 2; j++)
        {
            setValue(i+2*j, i, j, MyFloatMatrixSq);
        }
    }
    setValue(10, 2, 1, MyFloatMatrixSq);
    MyFloatMatrix1 = MyFloatMatrixSq.eraseColums(0,0);
    assert ( (abs(MyFloatMatrix1.getValue(1,1) - 5) < EPS )&&(abs(MyFloatMatrix1.getValue(2,1) - 6) < EPS ) );
    
    //eraseStrings check
    MyFloatMatrix1 = MyFloatMatrixSq.eraseStrings(0,0);
    assert ( (abs(MyFloatMatrix1.getValue(1,1) - 10) < EPS )&&(abs(MyFloatMatrix1.getValue(1,2) - 6) < EPS ) );
    
    //copy check
    MyFloatMatrix.copy(MyFloatMatrixSq);
    assert ( (abs(MyFloatMatrix.getValue(1,1) - 3) < EPS )&&(abs(MyFloatMatrix.getValue(1,2) - 5) < EPS )&&
            (abs(MyFloatMatrix.getValue(2,1) - 10) < EPS )&&(abs(MyFloatMatrix.getValue(2,2) -6) < EPS )
            );
    
    //isE check
        //E matrix creation
    setValue(1, 1, 1, MyFloatMatrix);
    setValue(1, 2, 2, MyFloatMatrix);
    setValue(0, 1, 2, MyFloatMatrix);
    setValue(0, 2, 1, MyFloatMatrix);
    assert(MyFloatMatrix.isE());
    
    //isZero check
        //Zero matrix creation
    setValue(0, 1, 1, MyFloatMatrix);
    setValue(0, 2, 2, MyFloatMatrix);
    assert(MyFloatMatrix.isZero());
    
    //checkZeroString check
    assert(MyFloatMatrix.checkZeroString(1));
    
    //isZeroString check
    vector<int> results1;
    results1 = MyFloatMatrix.isZeroString();
    assert( (results1[0] == 0)&&(results1[1] == 1) );
    
    //checkZeroColumn check
    assert(MyFloatMatrix.checkZeroString(1));
    
    //isZeroColumn check
    vector<int> results2;
    results2 = MyFloatMatrix.isZeroColumn();
    assert( (results1[0] == 0)&&(results1[1] == 1) );
    
    //transpose2Arg check
        //Square matrix check
    transpose2Arg(MyFloatMatrixSq, MyFloatMatrix1);
    assert ( (abs(MyFloatMatrix1.getValue(1,1) - 3) < EPS )&&(abs(MyFloatMatrix1.getValue(1,2) - 10) < EPS )&&
            (abs(MyFloatMatrix1.getValue(2,1) - 5) < EPS )&&(abs(MyFloatMatrix1.getValue(2,2) -6) < EPS )
            );
        //Non-square matrix check
    Matrix<float> TransposeCheck(1,2);
    setValue(3, 1, 1, TransposeCheck);
    setValue(7, 1, 2, TransposeCheck);
    transpose2Arg(TransposeCheck, MyFloatMatrix1);
    assert ( (abs(MyFloatMatrix1.getValue(1,1) - 3) < EPS )&&(abs(MyFloatMatrix1.getValue(2,1) - 7) < EPS ) );
    
    
    //transpose1Arg check
        //Square matrix check
    transpose1Arg(MyFloatMatrixSq);
    assert ( (abs(MyFloatMatrixSq.getValue(1,1) - 3) < EPS )&&(abs(MyFloatMatrixSq.getValue(1,2) - 10) < EPS )&&
            (abs(MyFloatMatrixSq.getValue(2,1) - 5) < EPS )&&(abs(MyFloatMatrixSq.getValue(2,2) -6) < EPS )
            );
        //Non-square matrix check
    transpose1Arg(TransposeCheck);
    assert ( (abs(TransposeCheck.getValue(1,1) - 3) < EPS )&&(abs(TransposeCheck.getValue(2,1) - 7) < EPS ) );
 
    cout << "All function tests were passed succesfully\n-------------------\n";

}
