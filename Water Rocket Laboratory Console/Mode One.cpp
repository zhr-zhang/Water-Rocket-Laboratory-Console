#include <iostream>
#include "Mode One.h"
#include "Interaction.h"
#include "Engine.h"
#include "Functions.h"
#include "Definition.h"

void MODE_ONE()
{
    speak_in(1);
    double sender[para]{};
    int num = 0;
    for (int i = 0; i < para; i++)
    {
        if (parameter[i].selection == false)
            sender[i] = parameter[i].value;
        else
            num++;
    }
    if (num == 1)
    {
        int a;
        for (int i = 0; i < para; i++)
        {
            if (parameter[i].selection == true)
            {
                a = i;
            }
        }        
        int size;
        for (size = 0; size * parameter[a].delta <= parameter[a].limit; size++);
        result_back* result = new result_back[size];
        for (int k = 0; k < size; k++)
        {
            sender[a] = parameter[a].delta * k;
            result[k] = Waterocket_engine(sender);
        }
        bool success= write_file_one(result, size);
        if (!success)
        {
            //
        }
    }
    else
    {
        int a, b;
        bool flag = false;
        for (int i = 0; i < para; i++)
        {
            if (parameter[i].selection == true && flag == false)
            {
                a = i;
                flag = true;
            }
            if (parameter[i].selection == true && flag == true)
                b = i;
        }
        int size_x, size_y;
        for (size_x = 0; size_x * parameter[a].delta <= parameter[a].limit; size_x++);
        for (size_y = 0; size_y * parameter[b].delta <= parameter[b].limit; size_y++);

        result_back** result = new result_back* [size_x];
        for (int i = 0; i < size_x; i++)
            result[i] = new result_back[size_y];
        for (int i = 0; i < size_x; i++)
        {
            sender[i] = i * parameter[a].delta;
            for (int j = 0; j < size_y; j++)
            {
                sender[j] = j * parameter[b].delta;
                result[i][j] = Waterocket_engine(sender);
            }
        }
    }
}