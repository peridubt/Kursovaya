#pragma once
#include <iostream> 
#include <cstring>
#include <fstream>
#include<functional>

const int FIO_n = 40, str_n = 20;

struct Phonebook
{
private:
    char FIO[FIO_n+1], street[str_n+1];
    int house_num, flat_num;
    int phone_number;
public:
    Phonebook() {} //Неинициализирующий конструктор
    void print(std::ostream& stream) //вывод информации об одной записи
    {
        stream << "ФИО:\t" << FIO << '\n';
        stream << "Адрес:\tул. " << street << ", д. " << house_num << ", кв. " << flat_num << "\n";
        stream << "Номер телефона:\t" << phone_number << '\n';
        stream << "----------------------------------\n\n";
    }
    int compare(const Phonebook& phnbk) //компаратор по ФИО абонентов
    {
        return strcmp(FIO, phnbk.FIO);
    }
    int get_phone_num() //возвращает номер телефона (для частного задания)
    {
        return phone_number;
    }
    char* get_fio() //вовзращает ФИО (для сортировки)
    {
        return FIO;
    }
    void set_FIO() //записывает информацию о ФИО
    {
        auto Lambda_check_FIO = [](char* word)->bool //проверка ФИО
        {
            bool result = true;
            int str_size = strlen(word);
            if ((int)word[0]<-64 || (int)word[0]>-33)
                result = false;
            int space_count = 0, i = 1;
            if (result)
            {
                while (i < str_size)
                {
                    if (word[i] == ' ') //считаем количество пробелов, должно быть всего 2
                        space_count += 1;
                    if (word[i] == ' ' && ((int)word[i + 1] < -64 || (int)word[i + 1] > -33)) //Заглавная буква не из русского алфавита
                        result = false;
                    else if (word[i] == ' ' && ((int)word[i + 1] >= -64 || (int)word[i + 1] <= -33))
                        i += 1;
                    else if (word[i] != ' ' && ((int)word[i] >= -64 || (int)word[i] <= -33) && ((int)word[i] < -32 || (int)word[i] > -1)) //строчная буква не из русского алфавита либо заглавная
                        result = false;
                    ++i;
                }
                if (space_count != 2)
                    result = false;
            }
            return result;
        };
        std::cout << "ФИО (в одну строчку, 40 знаков):\n->\t";
        std::cin.getline(FIO, FIO_n);
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        while (std::cin.fail() || !Lambda_check_FIO(FIO))
        {
            std::cout << "Неверно введены данные!\nФИО не должно превышать 40 знаков.\n"<<
                "Само ФИО должно содержать только русские буквы,\nкроме буквы \"Ё\"(заглавной и строчной)."<<
                "\nКаждое слово начинается с заглавной буквы,\nв строке должно быть только 2 пробела."<<
                "\nПовторите попытку ввода:\n->\t";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.getline(FIO, FIO_n);
        }
    }
    void set_street() //записывает информацию об улице
    {
        auto Lambda_check_street = [](char* word)->bool //проверка на корректность введённых данных
        {
            const char symbols[13] = "1234567890- "; //разрешёные символы
            bool result = true;
            int str_size = strlen(word);
            int ch;
            for (int i = 0; i < str_size; ++i)
            {
                ch = (int)word[i];
                if ((ch < -64 || ch > -1) && strchr(symbols, ch) == NULL) //проверка содержит: русские буквы и разрешённые символы
                    result = false;
            }
            return result;
        };
        std::cout << "\n---Адрес---\n\nУлица (20 знаков):\n->\t";
        std::cin.getline(street, str_n);
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        while (std::cin.fail() || !Lambda_check_street(street))
        {
            std::cout << "Неверно введены данные!\nНазвание улицы не должно превышать 20 знаков."<<
                "\nСамо название должно содержать только арабские цифры и русские буквы,\nкроме буквы \"Ё\"(заглавной и строчной)."<<
                "\nПовторите попытку ввода:\n->\t";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.getline(street, str_n);
        }
    }
    void set_house_num() //записывает информацию о номере дома
    {
        std::cout << "Дом (4 цифры):\n->\t";
        std::cin >> house_num;
        while (house_num < 1 || house_num > 9999)//номер дома - число от 1 до 9999
        {
            std::cout << "Неверно введены данные!\nНомер дома должен содержать до 4 цифр включительно.\n->\t";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin >> house_num;
        }
    }
    void set_flat_num() //записывает информацию о номере квартиры
    {
        std::cout << "Квартира (3 цифры):\n->\t";
        std::cin >> flat_num;
        while (flat_num < 1 || flat_num > 999)//номер квартиры - число от 1 до 999
        {
            std::cout << "Неверно введены данные!\nНомер квартиры должен содержать 3 цифр включительно.\n->\t";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin >> flat_num;
        }
    }
    void set_phone_number() //записывает информацию о номере телефона
    {
        std::cout << "\n-----------\n\nНомер телефона (6 цифр):\n->\t";
        std::cin >> phone_number;
        while (phone_number<100000 || phone_number > 999999) //номер телефона - шестизначное число
        {
            std::cout << "Неверно введены данные!\nНомер телефона должен содержать строго 6 цифр.\n->\t";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin >> phone_number;
        }
    }
};
