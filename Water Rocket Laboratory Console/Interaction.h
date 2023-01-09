#pragma once
#include <string>
using namespace std;
#pragma warning(disable:4996)

void Guard();

void speak_in(int);

void report(struct result_back);

bool write_file_zero(string, double**, int, struct variable_information*);

bool write_file_one(struct result_back*, int);

bool write_file_two(struct result_back**, int, int);