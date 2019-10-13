// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//
//  Definition.hpp
//  Matrix
//
//  Created by Владислав Агафонов on 19/09/2019.
//  Copyright © 2019 Владислав Агафонов. All rights reserved.
//

///TODO:
/// Поменять +, -, *, чтобы не менялись аргументы
/// Поставить везде проверку условий (наверное exceptions)
///
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <xmmintrin.h>
#include <x86intrin.h>
#include <cmath>

#define ROUND_UP(x, s) (((x)+((s)-1)) & -(s))

using namespace std;

template < class TYPE >
class Matrix {
    
    
public:
    Matrix();
    Matrix(const int &StringNumber, const int &ColumnNumber);
    ~Matrix();
    
    TYPE** getPointer() const;
    TYPE getValue(const int &String,const int &Column) const;
    
    template < class V, class U >
    friend void setValue(const U &new_value,
                         const int &String, const int &Column,
                         Matrix < V > &Target);
    template < class V >
    friend void print(const Matrix < V > &Target);
    
    template < class V >
    friend ostream& operator<<(ostream& os, const Matrix < V >& Target);
    
    template < class V >
    friend istream& operator>>(istream& in, Matrix < V >& Target);
    
    template < class V >
    friend void resize(Matrix < V >& Target, const int newStringNumber,const int newColumnNumber);
    
    //Service funtion
    template < class V >
    friend inline void transpose4x4_SSE(Matrix < V >& Target, Matrix < V >& Result,
                                         int lda, int ldb, int costyl1, int costyl2);
    template < class V >
    friend inline void transpose2Arg(Matrix < V >& Target, Matrix < V >& Result);
    
    template < class V >
    friend inline void transpose1Arg(Matrix < V >& Target);
    
    
    
    
    Matrix < TYPE >& operator = (const Matrix < TYPE > &rhs);
    //Matrix < TYPE >& operator = (const std::string  stringMatrix);
    Matrix < TYPE >& operator + (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator - (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator += (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator -= (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator * (Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator *= (Matrix < TYPE > &rhs);
    bool operator == (const Matrix < TYPE > &rhs) const;
    bool operator != (const Matrix < TYPE > &rhs) const;
    TYPE* operator[] (const int index);

    double determinant();
    
    
private:
    int StringNumber;
    int ColumnNumber;
    TYPE** value;
};


template < class TYPE >
Matrix < TYPE > :: Matrix()
{
    StringNumber = 0;
    ColumnNumber = 0;
}

template < class TYPE >
Matrix < TYPE > :: Matrix(const int &StringNumberToWrite, const int &ColumnNumberToWrite)
{
    StringNumber = StringNumberToWrite;
    ColumnNumber = ColumnNumberToWrite;
    // динамическое создание массива
    value = new TYPE * [StringNumber];
    assert(value != NULL);
    for (int i = 0; i < StringNumber; i++)
    {
        value[i] = new TYPE [ColumnNumber];
        assert(value[i] != NULL);
    }
    //cout << "[CONSTRUCTOR]Memory allocated\n";
    
    //инициализация нулями
    for (int i = 0; i < StringNumber; i++)
    {
        for (int j = 0; j < ColumnNumber; j++)
        {
            value[i][j] = 0;
            //cout << "[CONSTRUCTOR] Created [" << i << "][" << j << "] element \n";
        }
    }
}

template < class TYPE >
Matrix < TYPE > :: ~Matrix()
{
    for(int i = 0; i < StringNumber; i++)
    {
        free(value[i]);
    }
    free(value);
    cout << "[DESTRUCTOR] Destructed\n";
    
    StringNumber = 0;
    ColumnNumber = 0;
}

template < class TYPE >
TYPE** Matrix < TYPE > :: getPointer() const
{
    return value;
}

template < class TYPE >
TYPE Matrix < TYPE > :: getValue(const int &String, const int &Column) const
{
    return value[String][Column];
}

template < class V, class U >
void setValue(const U &new_value, const int &String, const int &Column,
              Matrix < V > &Target)
{
    Target.value[String-1][Column-1] = static_cast<V>(new_value);
}

template < class V >
void print(const Matrix < V > &Target)
{
    //cout << Target.StringNumber << " " << Target.ColumnNumber << "\n";
    //cout << Target.value[1][0] << "\n";
    for (int a = 0; a < Target.StringNumber; a++)
    {
        for (int b = 0; b < Target.ColumnNumber; b++)
        {
            cout << Target.value[a][b] << ",";
        }
        cout << "\n";
    }
}

template < class V >
ostream& operator<<(ostream& os, const Matrix < V >& Target)
{
    for (int a = 0; a < Target.StringNumber; a++)
    {
        for (int b = 0; b < Target.ColumnNumber; b++)
        {
            os << Target.value[a][b] << ",";
        }
        os << "\n";
    }
    os << "\n-------------------\n";
    return os;
}


template < class V >
istream&  operator>> (istream& in, Matrix < V > &Target)
{
    bool beginString = false;
    bool flag = false;
    int currentMatrixString = 0;
    int currentMatrixColumn = 0;
    std::string stringMatrix;
    in >> stringMatrix;
    for (char current : stringMatrix)
    {
        if ( (current == '{') && (beginString == false) )
        {
            beginString = true;
        }
        
        if ( (current == '{') && (beginString == true) )
        {
            flag = true;
        }
        
        if ( (current == '}') && (beginString == true) )
        {
            flag = false;
            currentMatrixString++;
            currentMatrixColumn = 0;
        }
        
        if ( (flag == true) && (current >= '0') && (current <= '9') )
        {
            Target.value[currentMatrixString][currentMatrixColumn] =
            (V)(current - '0');
            currentMatrixColumn++;
        }
        
    }
    return in;
}

template < class TYPE >
Matrix < TYPE >&  Matrix< TYPE >::operator= (const Matrix < TYPE > &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    
    resize(*this, rhs.StringNumber, rhs.ColumnNumber);
    
    for (int i = 0; i < rhs.StringNumber; i++)
    {
        for (int j = 0; j < rhs.ColumnNumber; j++)
        {
            this->value[i][j] = rhs.value[i][j];
        }
    }
    
    return *this;
}

template < class V >
void resize( Matrix < V >& Target, const int newStringNumber,const int newColumnNumber )
{
    V** TempOuter;
    V* TempInner;
    
    assert(Target.value != NULL);
    TempOuter = static_cast< V** > ( realloc(Target.value, sizeof(V*) * newStringNumber) );
    assert(TempOuter != NULL);
    Target.value = TempOuter;
    for (int i = 0; i < newStringNumber; i++)
    {
        if (i < Target.StringNumber)
        {
            assert(Target.value[i] != NULL);
            TempInner = static_cast< V* > ( realloc(Target.value[i], sizeof(V) * newColumnNumber) );
            assert(TempInner != NULL);
            Target.value[i] = TempInner;
        }
        else
        {
            TempInner = static_cast< V* > ( malloc(sizeof(V) * newColumnNumber) );
            assert(TempInner != NULL);
            Target.value[i] = TempInner;
        }
    }
    
    for (int i = 0; i < newStringNumber; i++)
    {
        for (int j = 0; j < newColumnNumber; j++)
        {
            if ( (i >= Target.StringNumber) || (j>= Target.ColumnNumber) )
            {
                Target.value[i][j] = 0;
            }
        }
    }
    
    Target.ColumnNumber = newColumnNumber;
    Target.StringNumber = newStringNumber;
}

///тут проблема с тем, что левый аргумент + тоже меняется
///как будто оператор унарный
template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::operator + (const Matrix < TYPE > &rhs)
{
    for (int i = 0; i < rhs.StringNumber; i++)
    {
        for (int j = 0; j < rhs.ColumnNumber; j++)
        {
            this->value[i][j] += rhs.value[i][j];
        }
    }
    return *this;
}

template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::operator - (const Matrix < TYPE > &rhs)
{
    for (int i = 0; i < rhs.StringNumber; i++)
    {
        for (int j = 0; j < rhs.ColumnNumber; j++)
        {
            this->value[i][j] -= rhs.value[i][j];
        }
    }
    return *this;
}

template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::operator += (const Matrix < TYPE > &rhs)
{
    for (int i = 0; i < rhs.StringNumber; i++)
    {
        for (int j = 0; j < rhs.ColumnNumber; j++)
        {
            this->value[i][j] += rhs.value[i][j];
        }
    }
    return *this;
}

template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::operator -= (const Matrix < TYPE > &rhs)
{
    for (int i = 0; i < rhs.StringNumber; i++)
    {
        for (int j = 0; j < rhs.ColumnNumber; j++)
        {
            this->value[i][j] -= rhs.value[i][j];
        }
    }
    return *this;
}

template < class V >
inline void transpose4x4_SSE(Matrix < V >& Target, Matrix < V >& Result, int lda, int ldb, int pointer1, int pointer2)
{
    //cout << "Tic \n" << Result;
    __m128 row1 = _mm_load_ps((float*)&Target.value[pointer1][pointer2]);
    __m128 row2 = _mm_load_ps((float*)&Target.value[pointer1+1][pointer2]);
    __m128 row3 = _mm_load_ps((float*)&Target.value[pointer1+2][pointer2]);
    __m128 row4 = _mm_load_ps((float*)&Target.value[pointer1+3][pointer2]);
    _MM_TRANSPOSE4_PS(row1, row2, row3, row4);
    _mm_store_ps((float*)&Result.value[pointer2][pointer1], row1);
    _mm_store_ps((float*)&Result.value[pointer2+1][pointer1], row2);
    _mm_store_ps((float*)&Result.value[pointer2+2][pointer1], row3);
    _mm_store_ps((float*)&Result.value[pointer2+3][pointer1], row4);
    //cout << "Toc \n"<< Result;
}


template < class V >
inline void transpose2Arg(Matrix < V >& Target, Matrix < V >& Result)
{
    ///Тут опять же исключение
    if (&Target == &Result)
    {
        cout << "[TRANSPOSITION]Invalid usage\n";
        assert(&Target != &Result);
        return;
    }
    
#pragma omp parallel for
    const int originalStringNumber = Target.StringNumber;
    const int originalColumnNumber = Target.ColumnNumber;
    int lda = ROUND_UP(originalStringNumber, 4);
    int ldb = ROUND_UP(originalColumnNumber, 4);
    
    ///не оч понятно, почему не работает с округленными НЕквадратными матрицами
    ///спасает оквадрачивание
    ///говорят, что размер блока 16 ускоряет вычисления  (сначала пробовал 4 и было ок)
    ///померить и может как-то по умному выбрать размер блока
    lda = max(lda, ldb);
    ldb = lda;
    
    resize(Target, lda, ldb);
    resize(Result, lda, ldb);
    
    const int n = Target.StringNumber;
    const int m = Target.ColumnNumber;
    
    const int block_size = 4;
    
    for(int i = 0; i < n; i+=block_size)
    {
        for(int j=0; j<m; j+=block_size)
        {
            int max_i2 = i+block_size < n ? i + block_size : n;
            int max_j2 = j+block_size < m ? j + block_size : m;
            for(int i2 = i; i2 < max_i2; i2+=4)
            {
                for(int j2 = j; j2 < max_j2; j2+=4)
                {
                    transpose4x4_SSE(Target, Result, lda, ldb, i2, j2);
                }
            }
        }
    }
    
    resize(Result, originalColumnNumber, originalStringNumber);
    resize(Target, originalColumnNumber, originalStringNumber);
}

template < class V >
inline void transpose1Arg(Matrix < V >& Target)
{
    Matrix< V > Temp(Target.StringNumber, Target.ColumnNumber);
    transpose2Arg(Target, Temp);
    Target = Temp;
}

///такая же проблема, как у +
///наверное нужно передавать переменную для результата?
template < class TYPE >
Matrix< TYPE >& Matrix< TYPE >::operator*(Matrix < TYPE >& rhs)
{
    if (this->ColumnNumber == rhs.StringNumber)
    {
        ///тут надо обработать ошибку
        assert(this->ColumnNumber == rhs.StringNumber);
        //return static_cast<Matrix< TYPE >&> (0);
    }
    
    Matrix < TYPE > Temp(this->StringNumber, rhs.ColumnNumber);
    
    transpose1Arg(rhs);
    
    for (int i = 0; i < Temp.StringNumber; i++)
    {
        for (int j = 0; j < Temp.ColumnNumber; j++)
        {
            for (int k = 0; k < (this->ColumnNumber); k++)
            {
                Temp.value[i][j] += this->value[i][k]*rhs.value[j][k];
            }
        }
    }
    
    transpose1Arg(rhs);
    
    *this = Temp;
    
    return *this;
}


template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::operator *= (Matrix < TYPE > &rhs)
{
    return (*this * rhs);
}

template < class TYPE >
bool Matrix < TYPE >::operator == (const Matrix < TYPE > &rhs) const
{
    if ( (this->ColumnNumber != rhs.ColumnNumber) || (this->StringNumber != rhs.StringNumber) )
    {
        return false;
    }
    
    for (int i = 0; i < this->StringNumber; i++)
    {
        for (int j = 0; j < this->ColumnNumber; j++)
        {
            if (this->value[i][j] != rhs.value[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

template < class TYPE >
bool Matrix < TYPE >::operator!=(const Matrix < TYPE > &rhs) const
{
    return (!(*this == rhs));
}

template < class TYPE >
TYPE* Matrix < TYPE >::operator[] (const int index)
{
    return this->value[index];
}

template < class TYPE >
double Matrix < TYPE >::determinant()
{
    if (this->StringNumber != this->ColumnNumber)
    {
        cout << "[DETERMINANT] Sizes are not equal\n";
        assert(this->StringNumber != this->ColumnNumber);
        return -1;
    }
    
    double det = 0;
    int i,j = 0;
    int size = this->StringNumber;
    
    if(size == 1)
    {
        det = this->value[0][0];
    }
    else if(size == 2)
    {
        det = (this->value[0][0]) * (this->value[1][1]) - (this->value[0][1]) * (this->value[1][0]);
    }
    else
    {
        Matrix < TYPE > Temp(size-1, size-1);
        for(i = 0; i < size; ++i)
        {
            for(j = 0; j < size-1; ++j)
            {
                if (j < i)
                    Temp.value[j] = this->value[j];
                else
                    Temp.value[j] = this->value[j+1];
            }
            det += pow((double)-1, (i+j))*Temp.determinant() * (this->value[i][size-1]);
        }
        Temp.~Matrix<TYPE>();
    }
    return det;
    
}

