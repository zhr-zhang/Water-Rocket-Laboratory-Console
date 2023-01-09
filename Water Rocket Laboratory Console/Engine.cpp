#include <iostream>
#include "Engine.h"
#include <string>
#include "Definition.h"

double spray(double x) //根据分段一次函数求喷水流速
{
    double jetting_speed_k[19] = { //斜率
        7.8479600 , 6.0184000 , 5.0778000 , 4.4798000 , 4.0376000 , 3.7338000 , 3.4584000 ,
        3.2498000 , 3.0690000 , 2.8904000 , 2.7870000 , 2.6758000 , 2.5564000 , 2.4628000 ,
        0.6756000 , 2.2750000 , 2.1872000 , 2.1362000 , 2.0724000
    };
    double jetting_speed_b[19] = { //截距
        -2.4262200 , 1.2329000 , 3.5844000 , 5.3784000 , 6.9261000 , 8.1413000 , 9.3806000 ,
        10.4236000 ,11.4180000 ,12.4896000 ,13.1617000 ,13.9401000 ,14.8356000 ,15.5844000 ,
        30.4378000 ,15.2435000 ,16.1215000 ,16.6570000 ,17.3588000
    };
    x += 1;
    if (x < 1.5)
        return 18.6914400 * x - 28.0371600;
    else if (x >= 11)
        return jetting_speed_k[18] * x + jetting_speed_b[18];
    else
        return jetting_speed_k[int(int(x * 2) - 3)] * x + jetting_speed_b[int(int(x * 2) - 3)];
}

result_back Waterocket_engine(double* prmt) //水火箭飞行引擎
{
    //prmt：0箭体空重 1水量 2绝对压强 3重力加速度 4推进剂密度 5推进器容积
    result_back package; //创建数据包用于传回模拟结果
    for (int i = 0; i < para; i++) //记录本次模拟条件
        package.condition[i] = prmt[i];

    const double stp = 1e-4, //迭代步长(s)
        VentSize = 6.361725123e-5; //喷口面积

    double variable[vari]{};
    for (int i = 0; i < 4; i++)variable[i] = 0;
    variable[7] = prmt[箭体空重] + prmt[水量] * prmt[推进剂密度];
    variable[8] = prmt[绝对压强];
    variable[9] = prmt[水量];
    variable[10] = prmt[推进器容积] - prmt[水量];

    //double variable[1] = 0, variable[0] = 0; //当前高度、时间
    //double variable[3] = 0, variable[2] = 0; //加速度、速度
    //double variable[4], variable[5], variable[6]; //喷出流速、体积流量、质量流量
    //double variable[7] = prmt[箭体空重] + prmt[水量] * prmt[推进剂密度]; //系统总质量
    //double variable[8] = prmt[绝对压强]; //绝对压强
    //double variable[9] = prmt[水量]; //水体积
    //double variable[10] = prmt[推进器容积] - prmt[水量]; //空气体积

    double V_origin = variable[10] * variable[8]; //空气膨胀后的体积
    if (V_origin <= prmt[推进器容积]) //判断是否能将水完全喷出
        package.situation = 0; //将飞行状况标记为 OVERWATER

    bool DROP = false; //下落标记

    for (; variable[9] >= 0; variable[0] += stp) //反冲推进阶段
    {
        variable[4] = spray(variable[8]); //根据瓶内压强获取喷水速度
        variable[5] = variable[4] * VentSize; //计算体积流量
        variable[6] = prmt[推进剂密度] * variable[5]; //计算质量流量
        variable[7] -= variable[6] * stp; //更新总质量
        variable[3] = variable[6] * variable[4] / variable[7] - prmt[重力加速度]; //通过反冲获得加速度
        variable[1] += (variable[2] * 2 + variable[3] * stp) / 2 * stp; //更新当前高度
        variable[2] += variable[3] * stp; //更新速度
        variable[9] -= variable[5] * stp; //更新水量
        variable[10] = prmt[推进器容积] - variable[9]; //更新空气体积
        variable[8] = V_origin / variable[10]; //理想气体绝热膨胀求压强

        if ((variable[2] * 2 + variable[3] * stp) <= 0 && !DROP) //下落喷水，即达到最高点
        {
            package.H_top = variable[1];
            package.T_top = variable[0];
            package.situation = 2; //将飞行状况标记为 FALL
            DROP = true; //将下落标记更改为真
        }
        if (DROP && variable[1] <= 0) //判定触地喷水
        {
            package.T_recoil = variable[0];
            package.situation = 3; //将飞行状况标记为 CRASH
            package.T_total = variable[0]; //总时间
            return package; //结束模拟
        }
    }
    package.H_recoil = variable[1];
    package.T_recoil = variable[0];
    package.situation = 1; //将飞行状况标记为 NORMAL
    for (variable[3] = -prmt[重力加速度]; variable[1] > 0; variable[0] += stp) //自由飞行阶段
    {
        variable[2] += variable[3] * stp; //更新速度
        variable[1] += variable[2] * stp; //更新当前高度
        if (!DROP && variable[2] <= 0) //判定下落
        {
            package.H_top = variable[1];
            package.T_top = variable[0];
            DROP = true; //将下落标记更改为真
        }
    }
    package.T_free = variable[0] - package.T_recoil; //自由飞行时间
    package.T_total = variable[0]; //总时间
    return package; //模拟结束
}

void exact(double* prmt, double** position, int size) //水火箭飞行引擎
{
    //prmt：0箭体空重 1水量 2绝对压强 3重力加速度 4推进剂密度 5推进器容积

    const double stp = 1e-4, //迭代步长(s)
        VentSize = 6.361725123e-5; //喷口面积

    double variable[vari]{};
    for (int i = 0; i < 4; i++)variable[i] = 0;
    variable[7] = prmt[箭体空重] + prmt[水量] * prmt[推进剂密度];
    variable[8] = prmt[绝对压强];
    variable[9] = prmt[水量];
    variable[10] = prmt[推进器容积] - prmt[水量];

    int present_size = 0;
    double V_origin = variable[10] * variable[8]; //空气膨胀后的体积
    bool DROP = false; //下落标记

    for (; variable[9] >= 0; variable[0] += stp) //反冲推进阶段
    {
        variable[4] = spray(variable[8]); //根据瓶内压强获取喷水速度
        variable[5] = variable[4] * VentSize; //计算体积流量
        variable[6] = prmt[推进剂密度] * variable[5]; //计算质量流量
        variable[7] -= variable[6] * stp; //更新总质量
        variable[3] = variable[6] * variable[4] / variable[7] - prmt[重力加速度]; //通过反冲获得加速度
        variable[1] += (variable[2] * 2 + variable[3] * stp) / 2 * stp; //更新当前高度
        variable[2] += variable[3] * stp; //更新速度
        variable[9] -= variable[5] * stp; //更新水量
        variable[10] = prmt[推进器容积] - variable[9]; //更新空气体积
        variable[8] = V_origin / variable[10]; //理想气体绝热膨胀求压强

        if ((variable[2] * 2 + variable[3] * stp) <= 0 && !DROP) //下落喷水，即达到最高点
        {
            DROP = true; //将下落标记更改为真
        }
        if (DROP && variable[1] <= 0) //判定触地喷水  
        {
            return; //结束模拟
        }
        for (int i = 0; i < vari && present_size < size; i++)
            position[present_size][i] = variable[i];
        present_size++;
    }
    for (variable[3] = -prmt[重力加速度]; variable[1] > 0; variable[0] += stp) //自由飞行阶段
    {
        variable[2] += variable[3] * stp; //更新速度
        variable[1] += variable[2] * stp; //更新当前高度
        if (!DROP && variable[2] <= 0) //判定下落
        {
            DROP = true; //将下落标记更改为真
        }
        for (int i = 0; i < vari && present_size < size; i++)
            position[present_size][i] = variable[i];
        present_size++;
    }
    return; //模拟结束
}