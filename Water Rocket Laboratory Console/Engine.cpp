#include <iostream>
#include "Engine.h"
#include <string>
#include "Definition.h"

double spray(double x) //���ݷֶ�һ�κ�������ˮ����
{
    double jetting_speed_k[19] = { //б��
        7.8479600 , 6.0184000 , 5.0778000 , 4.4798000 , 4.0376000 , 3.7338000 , 3.4584000 ,
        3.2498000 , 3.0690000 , 2.8904000 , 2.7870000 , 2.6758000 , 2.5564000 , 2.4628000 ,
        0.6756000 , 2.2750000 , 2.1872000 , 2.1362000 , 2.0724000
    };
    double jetting_speed_b[19] = { //�ؾ�
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

result_back Waterocket_engine(double* prmt) //ˮ�����������
{
    //prmt��0������� 1ˮ�� 2����ѹǿ 3�������ٶ� 4�ƽ����ܶ� 5�ƽ����ݻ�
    result_back package; //�������ݰ����ڴ���ģ����
    for (int i = 0; i < para; i++) //��¼����ģ������
        package.condition[i] = prmt[i];

    const double stp = 1e-4, //��������(s)
        VentSize = 6.361725123e-5; //������

    double variable[vari]{};
    for (int i = 0; i < 4; i++)variable[i] = 0;
    variable[7] = prmt[�������] + prmt[ˮ��] * prmt[�ƽ����ܶ�];
    variable[8] = prmt[����ѹǿ];
    variable[9] = prmt[ˮ��];
    variable[10] = prmt[�ƽ����ݻ�] - prmt[ˮ��];

    //double variable[1] = 0, variable[0] = 0; //��ǰ�߶ȡ�ʱ��
    //double variable[3] = 0, variable[2] = 0; //���ٶȡ��ٶ�
    //double variable[4], variable[5], variable[6]; //������١������������������
    //double variable[7] = prmt[�������] + prmt[ˮ��] * prmt[�ƽ����ܶ�]; //ϵͳ������
    //double variable[8] = prmt[����ѹǿ]; //����ѹǿ
    //double variable[9] = prmt[ˮ��]; //ˮ���
    //double variable[10] = prmt[�ƽ����ݻ�] - prmt[ˮ��]; //�������

    double V_origin = variable[10] * variable[8]; //�������ͺ�����
    if (V_origin <= prmt[�ƽ����ݻ�]) //�ж��Ƿ��ܽ�ˮ��ȫ���
        package.situation = 0; //������״�����Ϊ OVERWATER

    bool DROP = false; //������

    for (; variable[9] >= 0; variable[0] += stp) //�����ƽ��׶�
    {
        variable[4] = spray(variable[8]); //����ƿ��ѹǿ��ȡ��ˮ�ٶ�
        variable[5] = variable[4] * VentSize; //�����������
        variable[6] = prmt[�ƽ����ܶ�] * variable[5]; //������������
        variable[7] -= variable[6] * stp; //����������
        variable[3] = variable[6] * variable[4] / variable[7] - prmt[�������ٶ�]; //ͨ�������ü��ٶ�
        variable[1] += (variable[2] * 2 + variable[3] * stp) / 2 * stp; //���µ�ǰ�߶�
        variable[2] += variable[3] * stp; //�����ٶ�
        variable[9] -= variable[5] * stp; //����ˮ��
        variable[10] = prmt[�ƽ����ݻ�] - variable[9]; //���¿������
        variable[8] = V_origin / variable[10]; //�����������������ѹǿ

        if ((variable[2] * 2 + variable[3] * stp) <= 0 && !DROP) //������ˮ�����ﵽ��ߵ�
        {
            package.H_top = variable[1];
            package.T_top = variable[0];
            package.situation = 2; //������״�����Ϊ FALL
            DROP = true; //�������Ǹ���Ϊ��
        }
        if (DROP && variable[1] <= 0) //�ж�������ˮ
        {
            package.T_recoil = variable[0];
            package.situation = 3; //������״�����Ϊ CRASH
            package.T_total = variable[0]; //��ʱ��
            return package; //����ģ��
        }
    }
    package.H_recoil = variable[1];
    package.T_recoil = variable[0];
    package.situation = 1; //������״�����Ϊ NORMAL
    for (variable[3] = -prmt[�������ٶ�]; variable[1] > 0; variable[0] += stp) //���ɷ��н׶�
    {
        variable[2] += variable[3] * stp; //�����ٶ�
        variable[1] += variable[2] * stp; //���µ�ǰ�߶�
        if (!DROP && variable[2] <= 0) //�ж�����
        {
            package.H_top = variable[1];
            package.T_top = variable[0];
            DROP = true; //�������Ǹ���Ϊ��
        }
    }
    package.T_free = variable[0] - package.T_recoil; //���ɷ���ʱ��
    package.T_total = variable[0]; //��ʱ��
    return package; //ģ�����
}

void exact(double* prmt, double** position, int size) //ˮ�����������
{
    //prmt��0������� 1ˮ�� 2����ѹǿ 3�������ٶ� 4�ƽ����ܶ� 5�ƽ����ݻ�

    const double stp = 1e-4, //��������(s)
        VentSize = 6.361725123e-5; //������

    double variable[vari]{};
    for (int i = 0; i < 4; i++)variable[i] = 0;
    variable[7] = prmt[�������] + prmt[ˮ��] * prmt[�ƽ����ܶ�];
    variable[8] = prmt[����ѹǿ];
    variable[9] = prmt[ˮ��];
    variable[10] = prmt[�ƽ����ݻ�] - prmt[ˮ��];

    int present_size = 0;
    double V_origin = variable[10] * variable[8]; //�������ͺ�����
    bool DROP = false; //������

    for (; variable[9] >= 0; variable[0] += stp) //�����ƽ��׶�
    {
        variable[4] = spray(variable[8]); //����ƿ��ѹǿ��ȡ��ˮ�ٶ�
        variable[5] = variable[4] * VentSize; //�����������
        variable[6] = prmt[�ƽ����ܶ�] * variable[5]; //������������
        variable[7] -= variable[6] * stp; //����������
        variable[3] = variable[6] * variable[4] / variable[7] - prmt[�������ٶ�]; //ͨ�������ü��ٶ�
        variable[1] += (variable[2] * 2 + variable[3] * stp) / 2 * stp; //���µ�ǰ�߶�
        variable[2] += variable[3] * stp; //�����ٶ�
        variable[9] -= variable[5] * stp; //����ˮ��
        variable[10] = prmt[�ƽ����ݻ�] - variable[9]; //���¿������
        variable[8] = V_origin / variable[10]; //�����������������ѹǿ

        if ((variable[2] * 2 + variable[3] * stp) <= 0 && !DROP) //������ˮ�����ﵽ��ߵ�
        {
            DROP = true; //�������Ǹ���Ϊ��
        }
        if (DROP && variable[1] <= 0) //�ж�������ˮ  
        {
            return; //����ģ��
        }
        for (int i = 0; i < vari && present_size < size; i++)
            position[present_size][i] = variable[i];
        present_size++;
    }
    for (variable[3] = -prmt[�������ٶ�]; variable[1] > 0; variable[0] += stp) //���ɷ��н׶�
    {
        variable[2] += variable[3] * stp; //�����ٶ�
        variable[1] += variable[2] * stp; //���µ�ǰ�߶�
        if (!DROP && variable[2] <= 0) //�ж�����
        {
            DROP = true; //�������Ǹ���Ϊ��
        }
        for (int i = 0; i < vari && present_size < size; i++)
            position[present_size][i] = variable[i];
        present_size++;
    }
    return; //ģ�����
}