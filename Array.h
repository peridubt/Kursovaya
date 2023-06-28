#pragma once
#include "Phonebook.h"

using ptrPhnbk = Phonebook*;

struct Array
{
private:
    ptrPhnbk* arr;
    size_t real_size;
    size_t fact_size;
    
public:
    Array() {}; // неинициализирующий конструктор
    Array(size_t arr_size); // инициализирующий конструктор
    void add_info(Phonebook* a);
    void fill_array(std::ifstream& file); // заполнение массива из бин. файла
    void clear_tmp(); //очистка массива
    void print(); //вывод данных из массива
    void sorting(); //сортировка данных
    void arr_copy(ptrPhnbk* mas, size_t size_arr); //копирование массива
    void add_note(); //добавление записи
    void edit_note(); //редактирование записи
    void delete_note(); //удаление записи
    bool to_binary(const char* file_name); //запись значений в бинарный файл
    void text_output(std::istream& file_in, std::ostream& stream); //вывод содержимого бинарного файла через поток вывода
    void task(std::istream& file_in, std::ostream& file_out, int num_search, char* file_out_name); //выполнение частного задания

    ptrPhnbk* get_arr() //возвращает массив структур
    {
        return arr;
    }
    size_t get_real_size() //возвращает реальный размер
    {
        return real_size;
    }
    size_t get_fact_size() //возвращает фактический размер
    {
        return fact_size;
    }
};
