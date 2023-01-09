
#include "Functions.h"
#include "Definition.h"

double transform(int i, double value, bool direction)
{
    const double PI = 3.1415926535;
    if (direction == true)
    {
        if (i == 0)
            return value / 1e3;
        else if (i == 1)
            return value / 1e6;
        else if (i == 2)
            return value;
        else if (i == 3)
            return value;
        else if (i == 4)
            return value * 1e3;
        else if (i == 5)
            return value / 1e6;
        return value * value * PI / 4e6;
    }
    else
    {
        if (i == 0)
            return value * 1e3;
        else if (i == 1)
            return value * 1e6;
        else if (i == 2)
            return value;
        else if (i == 3)
            return value;
        else if (i == 4)
            return value / 1e3;
        else if (i == 5)
            return value * 1e6;
        return sqrt(value * 4e6 / PI);
    }
}

void ParaInitialize()
{
    //变量名
    parameter[0].name = "箭体空重";
    parameter[1].name = "水量";
    parameter[2].name = "相对压强";
    parameter[3].name = "重力加速度";
    parameter[4].name = "推进剂密度";
    parameter[5].name = "推进器容积";
    
    //单位
    parameter[0].unit = "(g)";
    parameter[1].unit = "(ml)";
    parameter[2].unit = "(bar)";
    parameter[3].unit = "(m/s^2)";
    parameter[4].unit = "(g/cm^3)";
    parameter[5].unit = "(ml)";

    //默认值
    parameter[0].defaultt = 0;
    parameter[1].defaultt = 0;
    parameter[2].defaultt = 0;
    parameter[3].defaultt = 9.807;
    parameter[4].defaultt = 1e3;
    parameter[5].defaultt = 1e-3;

    //是否存在默认值
    parameter[0].defaultt_flag = false;
    parameter[1].defaultt_flag = false;
    parameter[2].defaultt_flag = false;
    parameter[3].defaultt_flag = true;
    parameter[4].defaultt_flag = true;
    parameter[5].defaultt_flag = true;

    //默认模拟间隔
    parameter[0].delta = transform(0, 10,   true);
    parameter[1].delta = transform(1, 10,   true);
    parameter[2].delta = transform(2, 0.25, true);
    parameter[3].delta = transform(3, 0.1,  true);
    parameter[4].delta = transform(4, 0.01, true);
    parameter[5].delta = transform(5, 10,   true);
}

void vari_initialize(variable_information* variable)
{
    variable[0].name = "时间";
    variable[1].name = "高度";
    variable[2].name = "速度";
    variable[3].name = "加速度";
    variable[4].name = "喷流速度";
    variable[5].name = "体积流量";
    variable[6].name = "质量流量";
    variable[7].name = "总质量";
    variable[8].name = "绝对压强";
    variable[9].name = "水量";
    variable[10].name = "空气体积";

    variable[0].unit = "(s)";
    variable[1].unit = "(m)";
    variable[2].unit = "(m/s)";
    variable[3].unit = "(m/s^2)";
    variable[4].unit = "(m/s)";
    variable[5].unit = "(m^3/s)";
    variable[6].unit = "(kg/s)";
    variable[7].unit = "(kg)";
    variable[8].unit = "(bar)";
    variable[9].unit = "(m^3)";
    variable[10].unit = "(m^3)";
}