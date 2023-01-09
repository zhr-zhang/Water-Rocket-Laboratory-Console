#pragma once
#include <iostream>
#include <string>
using namespace std;

const int para = 6;
const int vari = 11;
const double stp = 1e-4;

const string FILENAME = "C:\\Users\\Administrator\\Documents\\"
"Zuniverce\\Water Rocket Laboratory Console\\Water Rocket Laboratory Console\\Output";

const int//prmt[]的下标
箭体空重 = 0,
水量 = 1,
绝对压强 = 2,
重力加速度 = 3,
推进剂密度 = 4,
推进器容积 = 5;

struct parameter_information {
	string name;        //参数名
	string unit;        //单位
	double value;       //参数值
	double delta;       //变化间隔
	double limit;       //上限
	double defaultt;    //默认值
	bool defaultt_flag; //是否存在默认值
	bool selection = false; //是否被选中
	
};

extern parameter_information parameter[para];

struct variable_information {
	string name,
		unit;
};

struct result_back {
	double condition[para]{}; //用于存储本次模拟条件
	double H_top = 0, H_recoil = 0; //最大高度、反冲结束高度
	double T_total = 0, T_top = 0, T_recoil = 0, T_free = 0; //总时间、最大高度时刻、反冲结束时间、自由飞行时间
	int situation = -1; //飞行状况：0 OVERWATER, 1 NORMAL, 2 FALL , 3 CRASH
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
		cout << "最大高度" << "(m)" << " : " << H_top << endl;
		cout << "反冲结束高度	" << "(m)" << " : " << H_recoil << endl;

	}
};