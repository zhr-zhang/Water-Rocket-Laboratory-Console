// ZWR Laboratory.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


#include <iostream>
#include "Engine.h"
#include "Functions.h"
#include "Interaction.h"
#include "Mode One.h"
#include "Mode Zero.h"
#include "Definition.h"
int main()
{
    Guard(); //密码
    ParaInitialize();
    cout << "研究方式代码:\n单次模拟 0\n批量模拟 1\n研究方式:";
    int research_mode; cin >> research_mode;
    if (research_mode == 0) MODE_ZERO();
    else if (research_mode == 1) MODE_ONE();
    system("pause");
    return 0;
}
