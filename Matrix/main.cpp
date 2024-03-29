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
#include "UnitTest.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    Tests MyTest;
    MyTest.TestsOperator();
    MyTest.TestsFunctions();
    return 0;
}
