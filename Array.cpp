#include "Array.h"


Array::Array(size_t arr_size)
{   
    real_size = arr_size;
    fact_size = 0;
    arr = new Phonebook * [real_size]; //выделение памяти для массива и его ячеек
    //в соответствии с реальным размером
    for (int i = 0; i < real_size; ++i)
        arr[i] = new Phonebook;
}
void Array::add_info(Phonebook* a) // добавление информации об одной записи
{
    // использует функции из Phonebook.h
    a->set_FIO();
    a->set_street();
    a->set_house_num();
    a->set_flat_num();
    a->set_phone_number();
}
void Array::fill_array(std::ifstream& file)
{
    file.read((char*)&fact_size, sizeof(fact_size)); //считываем фактический размер из файла
    file.read((char*)&real_size, sizeof(real_size)); //считываем реальный размер из файла
    if (fact_size) 
    {
        arr = new Phonebook * [real_size];
        for (size_t i = 0; i < real_size; ++i)
            arr[i] = new Phonebook;
    }
    else
    {
        real_size = 20;
        fact_size = 0; //если фактический размер оказался равен 0, то выделяем 20 ячеек
        arr = new Phonebook * [real_size];
        for (int i = 0; i < real_size; ++i)
            arr[i] = new Phonebook;
    }
    size_t i = 0;
    while (i < fact_size) //заполняем массив
    {
        file.read((char*)arr[i], sizeof(Phonebook));
        ++i;
    }
}
void Array::clear_tmp()
{
    arr = nullptr;
    real_size = 20;
    fact_size = 0;
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
                std::swap(arr[i], arr[i + 1]); //происходит сортировка обменом
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
        add_info(get_arr()[fact_size++]); //в ближайшую пустую ячейку записываются данные
    }
    else //если массив вдруг заполнен
    {
        Array tmp(real_size + 20); //выделяется временный массив на 20 ячеек больше
        tmp.arr_copy(arr, fact_size); //в него копируются данные
        std::cout << "Введите данные о новом абоненте.\n\n";
        add_info(tmp.get_arr()[real_size]); //записываются данные в первую пустую ячейку
        for (size_t i = 0; i < real_size; ++i)
            delete arr[i];
        delete[] arr; //старый массив очищается
        arr = tmp.get_arr(); //ему присваивается значение временного массива
        tmp.clear_tmp(); // временный массив удаляется
        fact_size = real_size + 1; //фиксируем изменения с размерами
        real_size += 20;
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
        
        while (note < 1 || note > fact_size) //проверка на диапазон
        {
            std::cout << "Введённое значение не находится в указанном промежутке!\nПовторите попытку ввода:\n->\t";
            std::cin >> note;
        }
        std::cout << "Введите новые данные об абоненте:\n";
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        add_info(arr[note - 1]); //по указанному номеру изменяем ячейку с соответсвующим индексом
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
        while (note < 1 || note > fact_size) //проверка на диапазон
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
                arr[new_i] = arr[i]; //копируем все ячейки, кроме той, которую указали
                ++new_i; //для этого используем счётчик нужных ячеек
            }
            ++i;
        }
        delete arr[fact_size - 1]; //удаляем лишнюю ячейку, которая оказалась продублированной
        --fact_size; //размер уменьшился на единицу
        std::cout << "Запись №" << note << " удалена!\n\n";
    }
    else
        std::cout << "Невозможно совершить удаление, так как файл пустой.\n\n";
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
bool Array::to_binary(const char* file_name) 
{
    bool result = true;
    std::ofstream file(file_name, std::ios::binary | std::ios::out);
    file.write((char*)&fact_size, sizeof(fact_size)); //бинарный файл будет содержать фактический размер
    file.write((char*)&real_size, sizeof(real_size)); //реальный размер
    if (file)
    {
        for (size_t i = 0; i < fact_size; ++i)
            file.write((char*)arr[i], sizeof(Phonebook)); //и сами записи
        file.close();
    }
    else
        result = false;
    return result;
}
void Array::task(std::istream& file_in, std::ostream& file_out, int num_search, char* file_out_name)
{
    size_t f_size = 0, r_size = 0, i = 0;
    Phonebook note;
    bool find = false;
    file_in.read((char*)&f_size, sizeof(f_size)); //считываем фактический размер
    file_in.read((char*)&r_size, sizeof(r_size)); //и реальный
    if (f_size) //использовать будем только фактический
    {
        file_out << "Здесь представлены данные абонентов, у которых номер телефона начинается на \"" << num_search << "\".\n\n";
        while (i < f_size)
        {
            ++i;
            file_in.read((char*)&note, sizeof(note)); //считываем запись
            if (note.get_phone_num() / 10000 == num_search)
            {
                file_out << "Запись №\t" << i << "\n";
                find = true;
                note.print(file_out); //выводим запись в файл
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
void Array::text_output(std::istream& file_in, std::ostream& stream) //можно вывести через основные потоки вывода: консоль или файл
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
