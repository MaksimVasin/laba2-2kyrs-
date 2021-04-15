#include <iostream>
#include "Linkedlist.h"
#include "Shannon-Fano.h"
template <class arr> arr* converList_Array(LinkedList* list)
{
    if (list->isEmpty()) throw std::out_of_range("list is empty");
    arr* array = new arr[list->get_size()];
    Iterator* cur = list->create_iterator();
    for (int i = 0; i < list->get_size(); i++)
    {
        if (is_same<arr, int>::value) array[i] = cur->freq(); // int - array frequency
        if (is_same<arr, char>::value) array[i] = cur->symbol(); // char - array symbols
        cur->next();
    }
    return array;
}
string coding_string(string str)
{
    LinkedList* list = ShannonFanoCoding(str);
    string code = "";
    for (size_t i = 0; i < str.length(); i++)
    {
        string codeSymbol = list->findcode(str[i]);
        for (int j = 0; j < codeSymbol.length(); j++)
            code.push_back(codeSymbol[j]);
    }
    return code;
}
string decoding_code(string str, string code)
{
    LinkedList* list = ShannonFanoCoding(str);
    string str_out = "";
    string codeSymbol = "";
    for (int i = 0; i < code.length(); i++)
    {
        codeSymbol.push_back(code[i]);
        if (list->find(codeSymbol))
        {
            str_out.push_back(list->findSymbol(codeSymbol));
            codeSymbol = "";
        }
    }
    if (codeSymbol != "") throw std::out_of_range("failed to decode");
    return str_out;
}
LinkedList* ShannonFanoCoding(string str)
{
    LinkedList* list = new LinkedList();
    char cur;
    for (size_t i = 0; i < str.length(); i++)
    {
        cur = str[i];
        if (!list->find(cur)) 
            list->push_back(cur);
    }
    list->bubbleSort();
    int* arr = converList_Array<int>(list); // array frequency
    char* arrSym = converList_Array<char>(list); // array symbols
    Coding_symbols(list, arr, arrSym, list->get_size());
    return list;
}
void Coding_symbols(LinkedList* list, int* arr, char* arrSym, size_t size_arr)
{ // left - 1, right - 0
    int leftSum = 0, rightSum = 0;
    size_t leftSize = 0, rightSize = 0;
    LinkedList* LeftList = new LinkedList();
    LinkedList* RightList = new LinkedList();

    for (int i = 0; i < size_arr; i++)
    {
        if (leftSum < rightSum)
        {
            leftSum += arr[i];
            LeftList->push_back(arrSym[i], arr[i]);
            list->CodingNode(arrSym[i], true);
            leftSize++;
        }
        else
        {
            rightSum += arr[i];
            RightList->push_back(arrSym[i], arr[i]);
            list->CodingNode(arrSym[i], false);
            rightSize++;
        }
    }
    if (LeftList->get_size() > 1)
    {
        int* Larr = converList_Array<int>(LeftList); // left array frequency
        char* LarrSym = converList_Array<char>(LeftList); // left array symbols
        Coding_symbols(list, Larr, LarrSym, leftSize);
    }
    if (RightList->get_size() > 1)
    {
        int* Rarr = converList_Array<int>(RightList); // right array frequency
        char* RarrSym = converList_Array<char>(RightList); // right array symbols
        Coding_symbols(list, Rarr, RarrSym, rightSize);
    }
}
void print_to_console()
{
    string str, codestr;
    cout << endl << "Enter string: ";
    getline(cin, str);
    LinkedList* list = ShannonFanoCoding(str);
    list->print_to_console();
    string code = coding_string(str);
    cout << "String: " << str << endl;
    cout << "Code: " << code << endl;
    cout << "SizeString = " << str.length() * sizeof(char)/* = 1байт */ * 8 << "bit" << endl; // бит
    cout << "SizeCode = " << code.length() << "bit" << endl;
    cout << "Compression ratio = " << (double)(code.length() / (double)(str.length() * 8)) * 100 << "%" << endl << endl;
    cout << "Enter code: ";
    getline(cin, codestr);
    string str2 = decoding_code(str, codestr);
    cout << "Code: " << codestr << endl;
    cout << "String: " << str2 << endl;
    cout << "SizeString = " << str2.length() * sizeof(char)/* = 1байт */ * 8 << "bit" << endl; // бит
    cout << "SizeCode = " << codestr.length() << "bit" << endl;
    cout << "Compression ratio = " << (double)(codestr.length() / (double)(str2.length() * 8)) * 100 << "%" << endl;
}

