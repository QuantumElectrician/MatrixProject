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
/// Добавить makeBeautiful всюду
///
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <xmmintrin.h>
#include <x86intrin.h>
#include <cmath>
#include <exception>

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
    
    //not released
    template < class V, class U >
    friend void resize( Matrix < V >& Target, const int newStringNumber,const int newColumnNumber,
                       const U typeIdentificator );
    
    template < class V >
    friend void resize(Matrix < V >& Target, const int newStringNumber,const int newColumnNumber);
    
    template < class V >
    friend inline void transpose2Arg(Matrix < V >& Target, Matrix < V >& Result);
    
    template < class V >
    friend inline void transpose1Arg(Matrix < V >& Target);
    
    
    Matrix < TYPE >& operator = (const Matrix < TYPE > &rhs);
    Matrix < TYPE > operator + (const Matrix < TYPE > &rhs);
    Matrix < TYPE > operator - (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator += (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator -= (const Matrix < TYPE > &rhs);
    Matrix < TYPE > operator * (Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator *= (Matrix < TYPE > &rhs);
    bool operator == (const Matrix < TYPE > &rhs) const;
    bool operator != (const Matrix < TYPE > &rhs) const;
    TYPE* operator[] (const int index);

    double determinantInt();
    double determinantFloatingPoint();
    double determinantTriangl();
    Matrix < TYPE >& upTriangle();
    Matrix < TYPE >& operator * (double operand);
    Matrix < TYPE >& operator *= (double operand);
    Matrix < TYPE >& diag();
    Matrix < TYPE >& makeBeautiful();
    vector < TYPE > gauss();
    Matrix < TYPE >& concate(const Matrix < TYPE >& rhs);
    Matrix < TYPE >& invert();
    Matrix < TYPE > eraseColums (int index1, int index2);
    Matrix < TYPE > eraseStrings (int index1, int index2);
    Matrix < TYPE >& copy(Matrix< TYPE >& From);
    bool isE ();
    bool isZero();
    vector<int> isZeroString();
    bool checkZeroString(const int i);
    vector<int> isZeroColumn();
    bool checkZeroColumn(const int j);
    
    
private:
    int StringNumber;
    int ColumnNumber;
    TYPE** value;
    constexpr const static double EPS = 1e-5;
    
    double determinantTrianglNotSafe();
    //Service funtion
    template < class V >
    friend inline void transpose4x4_SSE(Matrix < V >& Target, Matrix < V >& Result,
                                        int lda, int ldb, int costyl1, int costyl2);
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
    if (StringNumber > 0)
    {
        free(value);
    }
    cout << "\n[DESTRUCTOR] Destructed\n";
    
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
void setValue(const U &new_value, const int &string, const int &column,
              Matrix < V > &Target)
{
    if (string-1 >= Target.StringNumber)
    {
        cout << "[SET_VALUE] Out of range\n";
        throw runtime_error("[SET_VALUE] Out of range\n");
    }
    Target.value[string-1][column-1] = static_cast<V>(new_value);
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
    
    TempOuter = static_cast< V** > ( realloc(Target.value, sizeof(V*) * newStringNumber) );
    
    if (TempOuter == NULL)
    {
        cout << "[RESIZE] malloc was not succeeded\n";
        throw runtime_error("[RESIZE] malloc was not succeeded\n");
    }
    
    Target.value = TempOuter;
    for (int i = 0; i < newStringNumber; i++)
    {
        if (i < Target.StringNumber)
        {
            TempInner = static_cast< V* > ( realloc(Target.value[i], sizeof(V) * newColumnNumber) );
            if ((TempInner==NULL) || (TempOuter==NULL))
            {
                cout << "[RESIZE] malloc was not succeeded\n";
                throw runtime_error("[RESIZE] malloc was not succeeded\n");
            }
            Target.value[i] = TempInner;
        }
        else
        {
            TempInner = static_cast< V* > ( malloc(sizeof(V) * newColumnNumber) );
            if ((TempInner==NULL) || (TempOuter==NULL))
            {
                cout << "[RESIZE] malloc was not succeeded\n";
                throw runtime_error("[RESIZE] malloc was not succeeded\n");
            }
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


template < class TYPE >
Matrix < TYPE > Matrix < TYPE >::operator + (const Matrix < TYPE > &rhs)
{
    if ((rhs.StringNumber != (this->StringNumber)) || (rhs.ColumnNumber != (this->ColumnNumber)))
    {
        cout << "[OPERATOR+] Not valid size\n";
        throw runtime_error("[OPERATOR+] Not valid size\n");
    }
    
    Matrix < TYPE > Result(rhs.StringNumber, rhs.ColumnNumber);
    Result = *this;
    Result += rhs;
    return Result;
}

template < class TYPE >
Matrix < TYPE > Matrix < TYPE >::operator - (const Matrix < TYPE > &rhs)
{
    if ((rhs.StringNumber != (this->StringNumber)) || (rhs.ColumnNumber != (this->ColumnNumber)))
    {
        cout << "[OPERATOR-] Not valid size\n";
        throw runtime_error("[OPERATOR-] Not valid size\n");
    }
    
    Matrix < TYPE > Result(rhs.StringNumber, rhs.ColumnNumber);
    Result = *this;
    Result -= rhs;
    return Result;
}

template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::operator += (const Matrix < TYPE > &rhs)
{
    if ((rhs.StringNumber != (this->StringNumber)) || (rhs.ColumnNumber != (this->ColumnNumber)))
    {
        cout << "[OPERATOR+=] Not valid size\n";
        throw runtime_error("[OPERATOR+=] Not valid size\n");
    }
    
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
    if ((rhs.StringNumber != (this->StringNumber)) || (rhs.ColumnNumber != (this->ColumnNumber)))
    {
        cout << "[OPERATOR-=] Not valid size\n";
        throw runtime_error("[OPERATOR-=] Not valid size\n");
    }
    
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
    if (&Target == &Result)
    {
        cout << "[TRANSPOSITION]Invalid usage\n";
        throw runtime_error("[TRANSPOSITION]Invalid usage\n");
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

template < class TYPE >
Matrix< TYPE > Matrix< TYPE >::operator*(Matrix < TYPE >& rhs)
{
    if (this->ColumnNumber != rhs.StringNumber)
    {
        cout << "[OPERATOR*] Not valid size\n";
        throw runtime_error("[OPERATOR*] Not valid size\n");
    }
    
    Matrix < TYPE > Result(this->StringNumber, rhs.ColumnNumber);
    Result = *this;
    Result *= rhs;
    return Result;
}


template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::operator *= (Matrix < TYPE > &rhs)
{
    if (this->ColumnNumber != rhs.StringNumber)
    {
        cout << "[OPERATOR*=] Not valid size\n";
        throw runtime_error("[OPERATOR*=] Not valid size\n");
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
double Matrix < TYPE >::determinantInt()
{
    if (this->StringNumber != this->ColumnNumber)
    {
        cout << "[DETERMINANT_INT] Sizes are not equal\n";
        throw runtime_error("[DETERMINANT_INT] Sizes are not equal\n");
        return -1;
    }
    
    static_assert(is_integral<TYPE>::value,
                  "[DETERMINANT_INT] Only integral types avaliable\n");
    
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
                {
                    for (int k = 0; k < size - 1; k++)
                    {
                        Temp.value[j][k] = this->value[j][k];
                    }
                }
                    //Temp.value[j] = Target.value[j];
                else
                {
                    for (int k = 0; k < size - 1; k++)
                    {
                        Temp.value[j][k] = this->value[j+1][k];
                    }
                }
                    //Temp.value[j] = Target.value[j+1];
            }
            det += pow((double)-1, (i+j)) * Temp.determinantInt() * (this->value[i][size-1]);
        }
        Temp.~Matrix<TYPE>();
    }
    //cout << "\n [DETERMINANT:]\n" << Target;
    return det;
}

template < class TYPE >
double Matrix< TYPE >::determinantFloatingPoint()
{
    if (this->StringNumber != this->ColumnNumber)
    {
        cout << "[DETERMINANT_FLOATING_POINT] Sizes are not equal\n";
        throw runtime_error("[DETERMINANT_FLOATING_POINT] Sizes are not equal\n");
        return -1;
    }
    
    static_assert(is_floating_point<TYPE>::value,
                  "[DETERMINANT_FLOATING_POINT] Only floating point types avaliable\n");
    
    double det = 1;
    Matrix < TYPE > Temp(this->StringNumber, this->ColumnNumber);
    Temp.copy(*this);
    Temp.diag();
    for (int i = 0; i < Temp.StringNumber; i++)
    {
        det *= Temp.value[i][i];
    }
    return det;
}

template < class TYPE >
double Matrix< TYPE >::determinantTriangl()
{
    if (this->StringNumber != this->ColumnNumber)
    {
        cout << "[DETERMINANT_FLOATING_POINT] Sizes are not equal\n";
        throw runtime_error("[DETERMINANT_FLOATING_POINT] Sizes are not equal\n");
        return -1;
    }
    
    double det = 1;
    for (int i = 0; i < this->StringNumber; i++)
    {
        det *= this->value[i][i];
    }
    return det;
}



template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::upTriangle()
{
    static_assert(is_floating_point<TYPE>::value,
                  "[UPTRIANGLE] Only floating point types avaliable\n");
    
    int i, j, k = 0;
    int countSwaps = 1;
    double eps = 1e-5;
    for (i = 0; i < this->StringNumber; ++ i)
    {
        // находим строку с максимальным первым элементом
        int iMax = i;
        for (j = i + 1; j < this->StringNumber; ++ j)
            if ( abs (this->value[j][i]) > abs (this->value[iMax][i]) )
                iMax = j;
        if (abs (this->value[iMax][i]) < eps)
            continue;
        for (k = 0; k < this->ColumnNumber; ++k)
            swap (this->value[i][k], this->value[iMax][k]);
        countSwaps = - countSwaps * (i != iMax ? 1 : - 1);
        
        for (j = i + 1; j < this->StringNumber; ++ j)
        {
            double q = - this->value[j][i] / this->value[i][i];
            for (k = this->ColumnNumber - 1; k >= i; -- k)
                this->value[j][k] += q * this->value[i][k];
        }
    }
    
    // умножаем матрицу на -1, если мы сделали  нечётное количество перестановок строк
    *this = *this * static_cast<double>(countSwaps);
    return this->makeBeautiful();
}

template < class TYPE >
Matrix < TYPE >& Matrix<TYPE>::operator * (double operand)
{
    for (int i = 0; i < this->StringNumber; i++)
    {
        for (int j = 0; j < this->ColumnNumber; j++)
        {
            this->value[i][j] *= operand;
        }
    }
    return *this;
}


template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::makeBeautiful()
{
    for (int i = 0; i < this->StringNumber; i++)
    {
        for (int j = 0; j < this->ColumnNumber; j++)
        {
            if (abs(this->value[i][j]) < EPS)
            {
                this->value[i][j] = 0;
            }
        }
    }
    return *this;
}

template < class TYPE >
Matrix < TYPE >& Matrix<TYPE>::operator *= (double operand)
{
    return (*this * operand);
}
//ДОПИЛЕНО, но есть более новая версия (ниже)
//template < class TYPE >
//void Matrix< TYPE >::gauss(double* results)
//{
//    static_assert(is_floating_point<TYPE>::value,
//                  "[GAUSS] Only floating point types avaliable\n");
//
//    int i, j = 0;
//    this->upTriangle();
//
//    //проверяем определитель исходной матрицы
//    double localDet = this->determinantTrianglNotSafe();
//    if (localDet == 0)
//    {
//        cout << "[GAUSS] Unsuccesful: degenerate core matrix ";
//        throw runtime_error("[GAUSS] Unsuccesful: degenerate core matrix ");
//    }
//
//    results[this->StringNumber-1] =
//    (this->value[this->ColumnNumber-2][this->ColumnNumber-1]) / (this->value[this->ColumnNumber-2][this->StringNumber-1]);
//    for (i = this->StringNumber - 2; i >= 0; i--)
//    {
//        results[i] = this->value[i][this->StringNumber];
//        for ( j = i+1; j < this->StringNumber; j++)
//        {
//            results[i] -= this->value[i][j] * results[j];
//        }
//        results[i] /= this->value[i][i];
//
//        if (abs(results[i]) < EPS)
//        {
//            results[i] = 0;
//        }
//    }
//}

template < class TYPE >
vector< TYPE > Matrix< TYPE >::gauss()
{
    static_assert(is_floating_point<TYPE>::value,
                  "[GAUSS] Only floating point types avaliable\n");
    
    int i, j = 0;
    vector < TYPE > results (this->StringNumber, 0);
    this->upTriangle();
    
    //проверяем определитель исходной матрицы
    double localDet = this->determinantTrianglNotSafe();
    if (localDet == 0)
    {
        cout << "[GAUSS] Unsuccesful: degenerate core matrix ";
        throw runtime_error("[GAUSS] Unsuccesful: degenerate core matrix ");
    }
    
    results[this->StringNumber-1] =
    (this->value[this->ColumnNumber-2][this->ColumnNumber-1]) / (this->value[this->ColumnNumber-2][this->StringNumber-1]);
    for (i = this->StringNumber - 2; i >= 0; i--)
    {
        results[i] = this->value[i][this->StringNumber];
        for ( j = i+1; j < this->StringNumber; j++)
        {
            results[i] -= this->value[i][j] * results[j];
        }
        results[i] /= this->value[i][i];
        
        if (abs(results[i]) < EPS)
        {
            results[i] = 0;
        }
    }
    return results;
}

template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::diag()
{
    static_assert(is_floating_point<TYPE>::value,
                  "[DIAG] Only floating point types avaliable\n");
    
    this->upTriangle();
    for (int i = 1; i < this->StringNumber; ++i)
        for (int j = 0; j < i; ++j)
        {
            if (abs (this->value[i][i]) < EPS)
            {
                cout << "[DIAG] Diagonalization was unsuccesful\n";
                throw runtime_error("[DIAG] Diagonalization was unsuccesful\n");
            }
            double q = - this->value[j][i] / this->value[i][i];
            for (int k = this->ColumnNumber - 1; k >= i; --k)
                this->value[j][k] += q * this->value[i][k];
        }
    return *this;
    
}

template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::concate(const Matrix < TYPE >& rhs)
{
    if ( this->StringNumber != rhs.StringNumber )
    {
        cout << "[CONCATE] Column numbers are not equal\n";
        throw runtime_error("[CONCATE] Column numbers are not equal\n");
    }
    int newColumnNumber = this->ColumnNumber + rhs.ColumnNumber;
    resize(*this, this->StringNumber, newColumnNumber);
    
    for (int i = 0; i < this->StringNumber; i++)
    {
        for (int j = 0; j < rhs.ColumnNumber; j++)
        {
            this->value[i][this->ColumnNumber - rhs.ColumnNumber + j] = rhs.value[i][j];
        }
    }
    return *this;
}

template < class TYPE >
Matrix < TYPE >& Matrix< TYPE >::invert()
{
    static_assert(is_floating_point<TYPE>::value,
                  "[INVERT] Only floating point types avaliable\n");
    
    if (this->determinantFloatingPoint() == 0)
    {
        cout << "[INVERT] Degenerate matrix\n";
        throw runtime_error("[INVERT] Degenerate matrix\n");
    }
    
    //делаем единичную
    Matrix < TYPE > E(this->StringNumber, this->StringNumber);
    for (int i = 0; i < this->StringNumber; i++)
    {
        setValue(1, i+1, i+1, E);
    }
    
    Matrix < TYPE > Temp(this->StringNumber, this->StringNumber);
    Temp.copy(*this);
    Temp.concate(E);
    Temp.diag().makeBeautiful();
    
//    if (Temp.ColumnNumber == 0)
//    {
//        return Temp;
//    }
    
    for (int i = 0; i < this->ColumnNumber; ++i)
    {
        for (int k = 2*(this->ColumnNumber)-1; k >= 0; --k)
        {
            Temp.value[i][k] /= Temp.value[i][i];
            //cout << "[INVERT]:\n" << Temp;
        }
    }
    

    resize(*this, Temp.StringNumber, Temp.ColumnNumber - E.ColumnNumber);
    //cout << "[INVERT]:\n" << Temp;
    for (int i = 0; i < E.StringNumber; i++)
    {
        for (int j = 0; j < E.ColumnNumber; j++)
        {
            this->value[i][j] = Temp.value[i][this->StringNumber+j];
            //cout << "this->value[" << i << "][" << j << "]" << this->value[i][j] << "\n";
        }
    }
    return *this;
}

template < class TYPE >
Matrix < TYPE > Matrix < TYPE >::eraseColums (int index1, int index2)
{
    Matrix < TYPE > Temp(this->StringNumber, this->ColumnNumber - (index2 - index1 + 1));
    for (int j = 0; j < index1; ++j)
        for (int i = 0; i < this->StringNumber; ++ i)
            Temp.value[i][j] = this->value[i][j];
    for (int j = index2 + 1; j < this->ColumnNumber; ++ j)
        for (int i = 0; i < this->StringNumber; ++ i)
            Temp.value[i][j - index2 - 1 + index1] = this->value[i][j];
    return Temp;
}

template < class TYPE >
Matrix < TYPE > Matrix < TYPE >::eraseStrings (int index1, int index2)
{
    Matrix < TYPE > Temp(this->StringNumber, this->ColumnNumber);
    Temp.copy(*this);
    transpose1Arg(Temp);
    Temp.eraseColums(index1, index2);
    transpose1Arg(Temp);
    return Temp;
}

template < class V >
double Matrix < V >::determinantTrianglNotSafe()
{
    double localDet = 1;
    for (int i = 0; i < this->StringNumber; i++)
    {
        localDet *= this->value[i][i];
    }
    return localDet;
}

template < class TYPE >
Matrix < TYPE >& Matrix < TYPE >::copy( Matrix< TYPE >& From )
{
    *this = From;
    return *this;
}

template < class TYPE >
bool Matrix< TYPE >::isE ()
{
    if (this->ColumnNumber!=this->StringNumber)
    {
        return false;
    }
    
    for (int i = 0; i < this->StringNumber; i++)
    {
        if (this->value[i][i] != 1)
        {
            return false;
        }
    }
    
    for (int i = 0; i < this->StringNumber; i++)
    {
        for (int j = 0; j < this->ColumnNumber; j++)
        {
            if (i != j)
            {
                if (this->value[i][j] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

template < class TYPE >
bool Matrix< TYPE >::isZero()
{
    for (int i = 0; i < this->StringNumber; i++)
    {
        for (int j = 0; j < this->ColumnNumber; j++)
        {
            if (this->value[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

template < class TYPE >
vector<int> Matrix<TYPE>::isZeroString()
{
    vector<int> results;
    for (int i = 0; i < this->StringNumber; i++)
    {
        if (this->checkZeroString(i))
        {
            results.push_back(i);
        }
    }
    return results;
}

template < class TYPE >
bool Matrix<TYPE>::checkZeroString(const int i)
{
    for (int j = 0; j < this->ColumnNumber; j++)
    {
        if (this->value[i][j] != 0)
        {
            return false;
        }
    }
    return true;
}

template < class TYPE >
vector<int> Matrix<TYPE>::isZeroColumn()
{
    vector<int> results;
    for (int i = 0; i < this->ColumnNumber; i++)
    {
        if (this->checkZeroColumn(i))
        {
            results.push_back(i);
        }
    }
    return results;
}

template < class TYPE >
bool Matrix<TYPE>::checkZeroColumn(const int j)
{
    for (int i = 0; i < this->StringNumber; i++)
    {
        if (this->value[i][j] != 0)
        {
            return false;
        }
    }
    return true;
}

