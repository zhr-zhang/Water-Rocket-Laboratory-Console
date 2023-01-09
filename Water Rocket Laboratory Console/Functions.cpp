
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
    //������
    parameter[0].name = "�������";
    parameter[1].name = "ˮ��";
    parameter[2].name = "���ѹǿ";
    parameter[3].name = "�������ٶ�";
    parameter[4].name = "�ƽ����ܶ�";
    parameter[5].name = "�ƽ����ݻ�";
    
    //��λ
    parameter[0].unit = "(g)";
    parameter[1].unit = "(ml)";
    parameter[2].unit = "(bar)";
    parameter[3].unit = "(m/s^2)";
    parameter[4].unit = "(g/cm^3)";
    parameter[5].unit = "(ml)";

    //Ĭ��ֵ
    parameter[0].defaultt = 0;
    parameter[1].defaultt = 0;
    parameter[2].defaultt = 0;
    parameter[3].defaultt = 9.807;
    parameter[4].defaultt = 1e3;
    parameter[5].defaultt = 1e-3;

    //�Ƿ����Ĭ��ֵ
    parameter[0].defaultt_flag = false;
    parameter[1].defaultt_flag = false;
    parameter[2].defaultt_flag = false;
    parameter[3].defaultt_flag = true;
    parameter[4].defaultt_flag = true;
    parameter[5].defaultt_flag = true;

    //Ĭ��ģ����
    parameter[0].delta = transform(0, 10,   true);
    parameter[1].delta = transform(1, 10,   true);
    parameter[2].delta = transform(2, 0.25, true);
    parameter[3].delta = transform(3, 0.1,  true);
    parameter[4].delta = transform(4, 0.01, true);
    parameter[5].delta = transform(5, 10,   true);
}

void vari_initialize(variable_information* variable)
{
    variable[0].name = "ʱ��";
    variable[1].name = "�߶�";
    variable[2].name = "�ٶ�";
    variable[3].name = "���ٶ�";
    variable[4].name = "�����ٶ�";
    variable[5].name = "�������";
    variable[6].name = "��������";
    variable[7].name = "������";
    variable[8].name = "����ѹǿ";
    variable[9].name = "ˮ��";
    variable[10].name = "�������";

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