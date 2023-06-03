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
    size = arr_size;
    if (size)
    {
        arr = new Phonebook * [size];
        for (int i = 0; i < size; ++i)
            arr[i] = new Phonebook;
    }
    else
        arr = nullptr;
}
//Array::~Array()
//{
//    for (size_t i = 0; i < size; ++i)
//        delete arr[i];
//    delete[] arr;
//}
void Array::fill_array(std::ifstream& file)
{
    file.seekg(0);
    file.read((char*)&size, sizeof(size));
    if (size)
    {
        arr = new Phonebook * [size];
        for (int i = 0; i < size; ++i)
            arr[i] = new Phonebook;
    }
    else
        arr = nullptr;
    int i = 0;
    while (i < size)
    {
        file.read((char*)arr[i], sizeof(Phonebook));
        ++i;
    }
}
void Array::clear_tmp()
{
    arr = nullptr;
    size = 0;
}
void Array::print()
{
    for (int i = 0; i < size; ++i)
        arr[i]->print(std::cout);
}
void Array::sorting()
{
    for (size_t count = size; count > 1; --count)
        for (size_t i = 0; i < count - 1; ++i)
            if (arr[i]->compare(*arr[i + 1]) > 0)
                std::swap(arr[i], arr[i + 1]);
}
void Array::arr_copy(ptrPhnbk* mas, int size_arr)
{
    for (int i = 0; i < size_arr; ++i)
        *arr[i] = *mas[i];
}
void Array::add_note()
{
    Array tmp(size + 1);
    tmp.arr_copy(arr, size);
    std::cout << "Введите данные о новом абоненте.\n\n";
    add_info(tmp.get_arr()[size]);
    for (size_t i = 0; i < size; ++i)
        delete arr[i];
    delete[] arr;
    arr = tmp.get_arr();
    ++size;
    tmp.clear_tmp();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cout << "\nЗапись добавлена!\n\n";
}
void Array::edit_note()
{
    if (size != 0)
    {
        std::cout << "Введите номер записи от 1 до " << size << ", по которой будут изменяться данные:\n->\t";
        long int note;
        std::cin >> note;
        
        while (note < 1 || note > size)
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
    if (size != 0)
    {
        Array tmp(size - 1);
        std::cout << "Введите номер записи от 1 до " << size << ", по которому она будет удалена:\n->\t";
        long int note;
        std::cin >> note;
        while (note < 1 || note > size)
        {
            std::cout << "Введённое значение не находится в указанном промежутке!\nПовторите попытку ввода:\n->\t";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin >> note;
        }
        size_t i = 0, new_i = 0;
        while (i < size)
        {
            if (i != note - 1)
            {
                *tmp.get_arr()[new_i] = *arr[i];
                ++new_i;
            }
            ++i;
        }
        for (size_t i = 0; i < size; ++i)
            delete arr[i];
        delete[] arr;
        arr = tmp.get_arr();
        --size;
        tmp.clear_tmp();
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
    file.write((char*)&size, sizeof(size));
    if (file)
    {
        for (size_t i = 0; i < size; ++i)
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
    int size = 0, i = 0;
    Phonebook note;
    bool find = false;
    file_in.read((char*)&size, sizeof(size));
    if (size)
    {
        file_out << "Здесь представлены данные абонентов, у которых номер телефона начинается на \"" << num_search << "\".\n\n";
        while (i < size)
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
            std::cout << "Абонентов, чьи номера телефонов начинаются на \"" << num_search << "\", нет";
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
    file_in.seekg(0);
    file_in.read((char*)&size, sizeof(size));
    if (size!=0)
    {
        stream << "\nКоличество записей:\t" << size << "\n\n";
        while (i < size)
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
