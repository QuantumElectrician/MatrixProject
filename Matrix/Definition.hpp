//
//  Definition.hpp
//  Matrix
//
//  Created by Владислав Агафонов on 19/09/2019.
//  Copyright © 2019 Владислав Агафонов. All rights reserved.
//
#pragma once

#ifndef Definition_hpp
#define Definition_hpp

#include <stdio.h>

#endif /* Definition_hpp */

template < class TYPE >
class Matrix {
public:
    Matrix();
    Matrix(const TYPE &new_value);
    ~Matrix();
    
    TYPE getValue() const;
    void setValue(const TYPE &new_value);
private:
    TYPE value;
};

