#pragma once
#include <iostream>
#include <string>
using namespace std;

const int para = 6;
const int vari = 11;
const double stp = 1e-4;

const string FILENAME = "C:\\Users\\Administrator\\Documents\\"
"Zuniverce\\Water Rocket Laboratory Console\\Water Rocket Laboratory Console\\Output";

const int//prmt[]���±�
������� = 0,
ˮ�� = 1,
����ѹǿ = 2,
�������ٶ� = 3,
�ƽ����ܶ� = 4,
�ƽ����ݻ� = 5;

struct parameter_information {
	string name;        //������
	string unit;        //��λ
	double value;       //����ֵ
	double delta;       //�仯���
	double limit;       //����
	double defaultt;    //Ĭ��ֵ
	bool defaultt_flag; //�Ƿ����Ĭ��ֵ
	bool selection = false; //�Ƿ�ѡ��
	
};

extern parameter_information parameter[para];

struct variable_information {
	string name,
		unit;
};

struct result_back {
	double condition[para]{}; //���ڴ洢����ģ������
	double H_top = 0, H_recoil = 0; //���߶ȡ���������߶�
	double T_total = 0, T_top = 0, T_recoil = 0, T_free = 0; //��ʱ�䡢���߶�ʱ�̡��������ʱ�䡢���ɷ���ʱ��
	int situation = -1; //����״����0 OVERWATER, 1 NORMAL, 2 FALL , 3 CRASH
	void output(bool mode, FILE* fp)
	{
		
	}
	void output(parameter_information* parameter)
	{
		for (int i = 0; i < para; i++)
		{
			cout << parameter[i].name << parameter[i].unit << " : " << condition[i] << endl;
		}
		cout << endl;
		cout << "���߶�" << "(m)" << " : " << H_top << endl;
		cout << "��������߶�	" << "(m)" << " : " << H_recoil << endl;

	}
};