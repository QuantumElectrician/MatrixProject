//
//  Definition.hpp
//  Matrix
//
//  Created by Владислав Агафонов on 19/09/2019.
//  Copyright © 2019 Владислав Агафонов. All rights reserved.
//
#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "parcer.h"

using namespace std;


template < class TYPE >
class Matrix {
    
    
public:
    Matrix();
    Matrix(const int &StringNumber, const int &ColumnNumber);
    ~Matrix();
    
    TYPE** getPointer() const;
    TYPE getValue(const int &String,const int &Column) const;
    
    template < class V >
    friend void setValue(const V &new_value,
                         const int &String, const int &Column,
                         Matrix < V > &Target);
    template < class V >
    friend void print(const Matrix < V > &Target);
    
    template < class V >
    friend ostream& operator<<(ostream& os, const Matrix < V >& Target);
    
    template < class V >
    friend istream& operator>>(istream& in, Matrix < V >& Target);
    
    Matrix < TYPE >& operator = (const Matrix < TYPE > &rhs);
    //Matrix < TYPE >& operator = (const std::string  stringMatrix);
    //bool operator == (const char*  stringMatrix) const;
    //bool operator == (const char*  stringMatrix) const;
    Matrix < TYPE >& operator + (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator - (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator += (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator -= (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator * (const Matrix < TYPE > &rhs);
    Matrix < TYPE >& operator *= (const Matrix < TYPE > &rhs);
    




    
private:
    int StringNumber;
    int ColumnNumber;
    TYPE** value;
};


template < class TYPE >
Matrix < TYPE > :: Matrix()
{
    StringNumber = 1;
    ColumnNumber = 1;
    
    // динамическое создание массива
    value = new TYPE * [StringNumber];
    for (int i = 0; i < StringNumber; i++)
    {
    value[i] = new TYPE [ColumnNumber];
    }
        
    //инициализация нулями
    for (int i = 0; i < StringNumber; i++)
    {
        for (int j = 0; j < ColumnNumber; j++)
        {
            value[i][j] = 0;
        }
    }
}

template < class TYPE >
Matrix < TYPE > :: Matrix(const int &StringNumberToWrite, const int &ColumnNumberToWrite)
{
    StringNumber = StringNumberToWrite;
    ColumnNumber = ColumnNumberToWrite;
    // динамическое создание массива
    value = new TYPE * [StringNumber];
    for (int i = 0; i < StringNumber; i++)
    {
        value[i] = new TYPE [ColumnNumber];
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
    for(int i = 0; i < ColumnNumber; i++)
    {
        free(value[i]);
    }
    free(value);
    cout << "[DESTRUCTOR] Destructed\n";
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


template < class V >
void setValue(const V &new_value, const int &String, const int &Column,
              Matrix < V > &Target)
{
    Target.value[String-1][Column-1] = new_value;
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

template < class TYPE >
Matrix < TYPE >&  Matrix< TYPE >::operator= (const Matrix < TYPE > &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    
    //почему здесь НЕ нужен friend (private поля видно)
    //почему вызывался деструктор без & в возвращаемом значении
    for (int i = 0; i < rhs.StringNumber; i++)
    {
        for (int j = 0; j < rhs.ColumnNumber; j++)
        {
            this->value[i][j] = rhs.value[i][j];
        }
    }
    
    return *this;
}

//почему эту штуку убивают пробелы -- непонятно
template < class V >
istream&  operator>> (istream& in, Matrix < V > &Target)
{
    bool beginString = false;
    bool flag = false;
    int currentMatrixString = 0;
    int currentMatrixColumn = 0;
    std::string stringMatrix;
    cin >> stringMatrix;
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



