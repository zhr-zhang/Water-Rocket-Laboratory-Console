#include "Interaction.h"
#include "Functions.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include "Definition.h"
#pragma warning(disable:4996)

void Guard()
{
    char x;
    string sAnswer;
    string sPassword = "112358eabEAB!@#";
    cout << "Password:" << endl;
again:
    while ((x = getch()) != '\r') {
        if (x != '\b') {
            sAnswer.push_back(x);
        }
        else {
            sAnswer.pop_back();
        }
    }
    if (sAnswer == sPassword) {
        return;
    }
    else {
        cout << "The password is not correct." << endl;
        cout << "again:" << endl;
        goto again;
    }
    
}

void speak_in(int mode)
{
    if (mode == 0)
    {
        cout << endl;
        for (int i = 0; i < para; i++)
        {
            cout << parameter[i].name << parameter[i].unit << " : ";
            if (parameter[i].defaultt_flag == true)
            {
                cout << endl << "defaut value : " << transform(i, parameter[i].defaultt, false) << parameter[i].unit;
                cout << endl << "input -1 to use default value" << endl;
                double medium; cin >> medium;
                if (medium < 0)
                    parameter[i].value = parameter[i].defaultt;
                else
                    parameter[i].value = transform(i, medium, true);
            }
            else
            {
                cin >> parameter[i].value;
                parameter[i].value = transform(i, parameter[i].value, true);
            }
        }
    }

    else if (mode == 1)
    {
        for (int i = 0; i < para; i++)
            cout << i << ' ' << parameter[i].name << endl;
        int num;
        do {
            cout << endl << "变量数量 (1~2): ";
            cin >> num; //变量数量
        } while (num < 0 || num > 2);
        for (int i = 0; i < num; i++)
        {
            int choice;
            do {
                cout << "选择变量 " << char(i + 'a') << " : ";
                cin >> choice;
            } while (choice < 0 || choice >= para || parameter[i].selection == true);
            parameter[choice].selection = true;
        }

        cout << endl << "变量参数:" << endl;
        for (int i = 0; i < para; i++) //变量的输入
        {
            if (parameter[i].selection == true)
            {
                double medium;
                cout << endl << parameter[i].name << "." << endl; //变量名提示
                do {
                    cout << "上限 " << parameter[i].unit << " : ";
                    cin >> medium;
                } while (medium < 0);
                parameter[i].limit = transform(i, medium, true);
                do {
                    cout << "间隔 " << parameter[i].unit << " : ";
                    cout << endl << "defaut value : " << transform(i, parameter[i].delta, false) << parameter[i].unit;
                    cout << endl << "input -1 to use default value" << endl;
                    cin >> medium;
                } while (medium > parameter[i].limit);
                if (medium >= 0)
                    parameter[i].delta = transform(i, medium, true);
            }
        }

        cout << endl << "常量参数:" << endl;
        for (int i = 0; i < para; i++) //常量的输入
        {
            if (parameter[i].selection == false)
            {
                double medium;
                cout << parameter[i].name << parameter[i].unit << ":";
                if (parameter[i].defaultt_flag == true)
                {
                    cout << endl << "defaut value : " << transform(i, parameter[i].defaultt, false) << parameter[i].unit;
                    cout << endl << "input -1 to use default value" << endl; cin >> medium;
                    if (medium < 0)
                        parameter[i].value = parameter[i].defaultt;
                    else
                        parameter[i].value = transform(i, medium, true);
                }
                else
                {
                    do {
                        cin >> medium;
                    } while (medium < 0);
                    parameter[i].value = transform(i, medium, true);
                }
                cout << endl;
            }
        }
    }
}

void report(result_back result)
{
    cout << "模拟条件 : " << endl;
    for (int i = 0; i < para; i++)
    {
        cout << parameter[i].name << parameter[i].unit << " : "
            << transform(i, result.condition[i], false) << endl;
    }
    cout << "最大高度 : " << result.H_top << endl;
    cout << "反冲结束高度 : " << result.H_recoil << endl;
    cout << "总时间 : " << result.T_total << endl;
    cout << "反冲结束时间 : " << result.T_recoil << endl;
    cout << "自由飞行时间 : " << result.T_free << endl;
    cout << "最大高度时刻 : " << result.T_top << endl;
    cout << "飞行状况 : " << result.situation << endl;
    cout << "(0 OVERWATER, 1 NORMAL, 2 FALL , 3 CRASH)" << endl;
}

bool write_file_zero(string fname, double** data, int size, variable_information* variable)
{
    cout << "writing ...";
    int k = 0;

    FILE* fp = fopen(fname.c_str(), "wt+");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        return false;
    }
    for (int i = 0; i < vari; i++)
        fprintf(fp, "%s%s ", variable[i].name.c_str(), variable[i].unit.c_str());
    fputc('\n', fp);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < vari; j++)
        {
            fprintf(fp, "%.10f ", data[i][j]);
            printf("%3d%%\b\b\b\b", int(100.0 * k++ / (size * vari)));
        }
        fputc('\n', fp);
    }
    fclose(fp);
    cout << "done." << endl;
    return true;
}


bool write_file_one(struct result_back* data, int size)
{
    FILE* fp;
    if ((fp = fopen("C:\\Users\\Administrator\\Documents\\Zuniverce\\ZWR Laboratory\\file_output\\批量单变量.txt", "wt+")) == NULL)
        return false;
    int a;
    for (int i = 0; i < para; i++)
        if (parameter[i].selection == true)
            a = i;
    cout << parameter[a].name << parameter[a].unit << ' ';
    cout << "最大高度"
        << "反冲结束高度"
        << "总时间"
        << "最大高度时刻"
        << "反冲结束时间"
        << "自由飞行时间"
        << "飞行状况";


    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%.10f ", (i * parameter[a].delta));
        /////////////////////////////////
    }
    return true;
}

bool write_file_two(struct result_back** data, int size_x, int size_y)
{
    FILE* fp;
    if ((fp = fopen("C:\\Users\\Administrator\\Documents\\Zuniverce\\ZWR Laboratory\\file_output\\批量双变量.txt", "wt+")) == NULL)
        return false;
    return true;
}