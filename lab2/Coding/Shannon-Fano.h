#pragma once
#include "Linkedlist.h"
#include <string>
using namespace std;

LinkedList* ShannonFanoCoding(string);
void Coding_symbols(LinkedList*, int*, char*, size_t);
template <class arr> arr* converList_Array(LinkedList*);
string coding_string(string);
string decoding_code(string, string);
void print_to_console();