#include "Array.h"

void add_info(Phonebook* a)
{
    a->set_FIO();
    a->set_street();
    a->set_house_num();
    a->set_flat_num();
    a->set_phone_number();
}
Array::Array(size_t arr_size)
{   
    real_size = arr_size;
    fact_size = 0;
    arr = new Phonebook * [real_size];
    for (int i = 0; i < real_size; ++i)
        arr[i] = new Phonebook;
}
//Array::~Array()
//{
//    for (size_t i = 0; i < size; ++i)
//        delete arr[i];
//    delete[] arr;
//}
void Array::fill_array(std::ifstream& file)
{
    file.read((char*)&fact_size, sizeof(fact_size));
    file.read((char*)&real_size, sizeof(real_size));
    if (fact_size)
    {
        arr = new Phonebook * [real_size];
        for (size_t i = 0; i < real_size; ++i)
            arr[i] = new Phonebook;
    }
    else
        arr = nullptr;
    size_t i = 0;
    while (i < fact_size)
    {
        file.read((char*)arr[i], sizeof(Phonebook));
        ++i;
    }
}
void Array::clear_tmp()
{
    arr = nullptr;
    real_size = 0;
    fact_size = 20;
}
void Array::print()
{
    for (int i = 0; i < fact_size; ++i)
        arr[i]->print(std::cout);
}
void Array::sorting()
{
    for (size_t count = fact_size; count > 1; --count)
        for (size_t i = 0; i < count - 1; ++i)
            if (arr[i]->compare(*arr[i + 1]) > 0)
                std::swap(arr[i], arr[i + 1]);
}
void Array::arr_copy(ptrPhnbk* mas, size_t size_arr)
{
    for (size_t i = 0; i < size_arr; ++i)
        *arr[i] = *mas[i];
}
void Array::add_note()
{
    if (real_size != fact_size)
    {
        add_info(get_arr()[fact_size++]);
    }
    else
    {
        Array tmp(real_size + 20);
        tmp.arr_copy(arr, fact_size);
        std::cout << "Введите данные о новом абоненте.\n\n";
        add_info(tmp.get_arr()[real_size]);
        for (size_t i = 0; i < real_size; ++i)
            delete arr[i];
        delete[] arr;
        arr = tmp.get_arr();
        tmp.clear_tmp();
        fact_size = real_size + 1;
        real_size += 20;
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nЗапись добавлена!\n\n";
    }
}
void Array::edit_note()
{
    if (fact_size != 0)
    {
        std::cout << "Введите номер записи от 1 до " << fact_size << ", по которой будут изменяться данные:\n->\t";
        long int note;
        std::cin >> note;
        
        while (note < 1 || note > fact_size)
        {
            std::cout << "Введённое значение не находится в указанном промежутке!\nПовторите попытку ввода:\n->\t";
            std::cin >> note;
        }
        std::cout << "Введите новые данные об абоненте:\n";
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        add_info(arr[note - 1]);
        std::cout << "Запись №" << note << " изменена!\n\n";
    }
    else
        std::cout << "Невозможно совершить изменение, так как файл пустой.\n\n";
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
void Array::delete_note()
{
    if (fact_size != 0)
    {
        std::cout << "Введите номер записи от 1 до " << fact_size << ", по которому она будет удалена:\n->\t";
        long int note;
        std::cin >> note;
        while (note < 1 || note > fact_size)
        {
            std::cout << "Введённое значение не находится в указанном промежутке!\nПовторите попытку ввода:\n->\t";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin >> note;
        }
        size_t i = 0, new_i = 0;
        while (i < fact_size)
        {
            if (i != note - 1)
            {
                arr[new_i] = arr[i];
                ++new_i;
            }
            ++i;
        }
        --fact_size;
        std::cout << "Запись №" << note << " удалена!\n\n";
    }
    else
        std::cout << "Невозможно совершить удаление, так как файл пустой.\n\n";
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
bool Array::to_binary(const char* file_name) // Проверяет, открылся ли файл. Побочный эффект - запись в бинарный файл
{
    bool result = true;
    std::ofstream file(file_name, std::ios::binary | std::ios::out);
    file.write((char*)&fact_size, sizeof(fact_size));
    file.write((char*)&real_size, sizeof(real_size));
    if (file)
    {
        for (size_t i = 0; i < fact_size; ++i)
            file.write((char*)arr[i], sizeof(Phonebook));
        file.close();
    }
    else
        result = false;
    return result;
}
// перед заданием тоже спрашивать про изменения в файле
void Array::task(std::istream& file_in, std::ostream& file_out, int num_search, char* file_out_name)
{
    size_t f_size = 0, r_size = 0, i = 0;
    Phonebook note;
    bool find = false;
    file_in.read((char*)&f_size, sizeof(f_size));
    file_in.read((char*)&r_size, sizeof(r_size));
    if (f_size)
    {
        file_out << "Здесь представлены данные абонентов, у которых номер телефона начинается на \"" << num_search << "\".\n\n";
        while (i < f_size)
        {
            ++i;
            file_in.read((char*)&note, sizeof(note));
            if (note.get_phone_num() / 10000 == num_search)
            {
                file_out << "Запись №\t" << i << "\n";
                find = true;
                note.print(file_out);
            }
        }
        if (!find)
        {
            file_out << "Абонентов, чьи номера телефонов начинаются на \"" << num_search << "\", нет";
            std::cout << "Абонентов, чьи номера телефонов начинаются на \"" << num_search << "\", нет\n";
            std::cout << "Данные внесены в файл \"" << file_out_name << "\"!\n\n";
        }
        else
            std::cout << "Данные внесены в файл \"" << file_out_name << "\"!\n\n";
    }
    else
        std::cout << "Невозможно выполнить задачу, так как файл пустой.\n\n";
}
void Array::text_output(std::istream& file_in, std::ostream& stream)
{
    int i = 0;
    Phonebook note;
    file_in.read((char*)&fact_size, sizeof(fact_size));
    file_in.read((char*)&real_size, sizeof(real_size));
    if (fact_size!=0)
    {
        stream << "\nКоличество записей:\t" << fact_size << "\n\n";
        while (i < fact_size)
        {
            ++i;
            file_in.read((char*)&note, sizeof(note));
            stream << "Запись № " << i << "\n";
            note.print(stream);
        }
    }
    else
        std::cout << "Записей нет, так как файл пустой.\nДобавьте запись и повторите попытку.\n\n";
}
