#pragma once
#include "Phonebook.h"

using ptrPhnbk = Phonebook*;

struct Array
{
private:
    ptrPhnbk* arr;
    int size;
public:
    Array() {};
    Array(size_t arr_size);
    //~Array();
    void fill_array(std::ifstream& file);
    void clear_tmp();
    void print();
    void sorting();
    void arr_copy(ptrPhnbk* mas, int size_arr);
    void add_note();
    void edit_note();
    void delete_note();
    bool to_binary(const char* file_name);
    void text_output(std::istream& file_in, std::ostream& stream);
    void task(std::istream& file_in, std::ostream& file_out, int num_search, char* file_out_name);

    ptrPhnbk* get_arr()
    {
        return arr;
    }
    int get_size()
    {
        return size;
    }
};
