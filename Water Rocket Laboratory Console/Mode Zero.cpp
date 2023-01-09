#include <iostream>
#include "Mode Zero.h"
#include "Interaction.h"
#include "Engine.h"
#include "Functions.h"
#include "Definition.h"

void MODE_ZERO()
{
    variable_information variable[vari]{};
    vari_initialize(variable);

    speak_in(0);
    double sender[para]{};
    for (int i = 0; i < para; i++)
        sender[i] = parameter[i].value;
    result_back result = Waterocket_engine(sender);
    //report(result);
    int size; for (size = 0; size * stp <= result.T_total; size++);
    double** process = new double* [size];
    for (int i = 0; i < size; i++)
        process[i] = new double[vari];
    exact(sender, process, size);
    for (int i = 0; i < vari; i++)
        cout << variable[i].name << variable[i].unit << ' ';
    cout << endl;
    cout << size << endl;
    cout << result.T_total << endl;
    write_file_zero(FILENAME, process, size, variable);
    delete[]process;
}

