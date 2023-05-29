//
//  require.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#ifndef require_hpp
#define require_hpp

#include <stdio.h>
#include <string>
#include <cstdio>
#include <cstdlib>

//头文件不能写 任何名称空间
//using namespace std;

//内联函数 速度快
inline void require(bool requirement, const std::string& msg="Requirement failed")//参数 默认值
{
    if (!requirement) {
        //输出错误信息  stderr是标准错误
        fputs(msg.c_str(),stderr);
        fputs("\n",stderr);
        exit(1);
    }
}

#endif /* require_hpp */
