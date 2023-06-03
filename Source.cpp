#define _CRT_SECURE_NO_WARNINGS
#include "Array.h"
#include <Windows.h>
#include <string>
#include <sstream>

void menu1_pop_up()
{
    std::cout << "1. Создать новый файл.\n" <<
        "2. Открыть существующий файл.\n" <<
        "0. Выход.\n";
}
void menu2_pop_up()
{
    std::cout << "1. Создать файл.\n" <<
        "2. Открыть файл.\n" <<
        "3. Добавить запись.\n" <<
        "4. Изменить запись.\n" <<
        "5. Удалить запись.\n" <<
        "6. Отобрать абонентов по первым двум цифрам\n   номера телефона и вывести результат в txt.\n" <<
        "7. Печать в консоль.\n" <<
        "8. Печать в txt.\n" <<
        "9. Сохранить изменения.\n" <<
        "0. Выход.\n";
}
void save_edits(Array &mass, bool &edits, char* filename)
{
    std::string edit_choice;
    if (edits)
    {
        std::cout << "Есть несохранённые изменения! Сохранить их? (Да - Д/Нет - Н)\n";
        while (edits)
        {
            std::cout << "->\t";
            std::getline(std::cin, edit_choice);
            if (edit_choice == "Д" || edit_choice == "д" || edit_choice == "Да" || edit_choice == "да")
            {
                mass.sorting();
                if (mass.to_binary(filename))
                    std::cout << "Изменения сохранены!\n\n";
                else
                    std::cout << "Не удалось сохранить изменения, так как вы не внесли данные\n";
                edits = false;
            }
            else if (edit_choice == "Н" || edit_choice == "н" || edit_choice == "Нет" || edit_choice == "нет")
            {
                mass.clear_tmp();
                edits = false;
            }
            else
            {
                std::cout << "Вы ввели неверное значение. Повторите попытку ввода.\nСохранить изменения? (Да - Д/Нет - Н)\n";
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
            }
        }
    }
}
void save_edits(Array &mass, bool& edits, char* filename, std::ifstream& file_in)
{
    std::string edit_choice;
    if (edits)
    {
        std::cout << "Есть несохранённые изменения! Сохранить их? (Да - Д/Нет - Н)\n";
        while (edits)
        {
            std::cout << "->\t";
            std::getline(std::cin, edit_choice);
            if (edit_choice == "Д" || edit_choice == "д" || edit_choice == "Да" || edit_choice == "да")
            {
                mass.sorting();
                if (mass.to_binary(filename))
                    std::cout << "Изменения сохранены!\n\n";
                else
                    std::cout << "Не удалось сохранить изменения, так как вы не внесли данные\n";
                edits = false;
            }
            else if (edit_choice == "Н" || edit_choice == "н" || edit_choice == "Нет" || edit_choice == "нет")
            {
                mass.clear_tmp();
                file_in.open(filename, std::ios::binary | std::ios::in);
                mass.fill_array(file_in);
                file_in.close();
                edits = false;
            }
            else
            {
                std::cout << "Вы ввели неверное значение. Повторите попытку ввода.\nСохранить изменения? (Да - Д/Нет - Н)\n";
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
            }
        }
    }
}
bool StrToInt(int& i, std::string s)
{
    char c;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail() || ss.get(c))
    {
        return false;
    }
    return true;
}
bool check_filename(char* filename)
{
    const char restricted_sym[] = "/\\:*?\"<>|";
    int str_size = strlen(filename);
    bool result = true;
    for (int i = 0; i < str_size; ++i)
        if (strchr(restricted_sym, (int)filename[i]) != NULL)
            result = false;
    return result;
}
void CreateNewFile(char* filename, std::ofstream& new_file)
{
    std::cout << "Придумайте название для файла.\nДанному файлу автоматически присвоится расширение txt:\n->\t";
    std::cin >> filename;
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    while (!check_filename(filename))
    {
        std::cout << "В вашем файле содержатся запретные символы: /\\:*?\"<>|\nПридумайте другое имя и повторите попытку:\n->\t";
        std::cin >> filename;
        std::cin.ignore(std::cin.rdbuf()->in_avail());
    }
    strcat(filename, ".txt");
    new_file.open(filename, std::ios::binary);
    std::cout << "\nФайл \"" << filename << "\" создан!\n\n";
}
void OpenExistingFile(char* filename, std::ifstream& existing_file, Array &mass, bool &flag_menu1, int &menu1)
{
    std::cout << "Введите название существующего файла.\n(Файл должен быть формата txt):\n->\t";
    std::cin >> filename;
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    strcat(filename, ".txt");
    existing_file.open(filename, std::ios::binary);
    if (existing_file.is_open())
    {
        mass.clear_tmp();
        std::cout << "\nФайл \"" << filename << "\" открыт!\n\n";
        mass.fill_array(existing_file);
        existing_file.close();
        flag_menu1 = false;
        menu1 = 0;
    }
    else
    {
        std::cout << "Неправильное имя файла, либо файл не существует.\nВведите имя заново (2) либо создайте новый файл (1).\n";
        existing_file.clear();
    }
}
void DoTask(int &num_search,char* filename,char* file_out_name, std::ifstream& file_in, std::ofstream& file_out, Array &mass)
{
    std::cout << "Введите первые две цифры номера телефона, по которым нужно отобрать абонентов.\nДанные будут выведены в отдельный файл.\n->\t";
    std::cin >> num_search;
    std::cout << "Придумайте название для файла вывода результата:\n->\t";
    std::cin >> file_out_name;
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    while (!check_filename(file_out_name))
    {
        std::cout << "В вашем файле содержатся запретные символы: /\\:*?\"<>|\nПридумайте другое имя и повторите попытку:\n->\t";
        
        std::cin >> file_out_name;
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        
    }
    strcat(file_out_name, ".txt");
    file_out.open(file_out_name);
    file_in.open(filename, std::ios::binary | std::ios::in);
    mass.task(file_in, file_out, num_search, file_out_name);
    file_out.close();
    file_in.close();
}
void PrintToConsole(char* filename, std::ifstream& file_in, Array &mass)
{
    file_in.open(filename, std::ios::binary | std::ios::in);
    if (file_in.is_open())
        mass.text_output(file_in, std::cout);
    else
        std::cout << "Невозможно произвести печать, так как вы не открыли файл!\n";
    file_in.close();
}
void PrintToTxt(char* filename, char* file_out_name, std::ifstream& file_in, std::ofstream& file_out, Array &mass)
{
    file_in.open(filename, std::ios::binary | std::ios::in);
    if (mass.get_size()!=0)
    {
        std::cout << "Придумайте название файла для вывода в txt:\n->\t";
        std::cin >> file_out_name;
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        while (!check_filename(file_out_name))
        {
            std::cout << "В вашем файле содержатся запретные символы: /\\:*?\"<>|\nПридумайте другое имя и повторите попытку:\n->\t";
            std::cin >> file_out_name;
            std::cin.ignore(std::cin.rdbuf()->in_avail());
        }
        strcat(file_out_name, ".txt");
        file_out.open(file_out_name);
        if (file_in.is_open())
        {
            std::cout << "\nФайл \"" << file_out_name << "\" создан! Данные сохранены в формате txt.\n\n";
            mass.text_output(file_in, file_out);
        }
        else
            std::cout << "Невозможно произвести печать, так как вы не открыли файл!\n\n";
        file_out.close();
    }
    else
        std::cout << "Записей нет, так как файл пустой.\nДобавьте запись и повторите попытку.\n\n";
    file_in.close();
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu1_pop_up();
    int menu1;
    std::string input;
    
    std::cout << "\nВыберите опцию из меню:\n->\t";
    std::getline(std::cin, input, '\n');

    std::ifstream existing_file, file_in;
    std::ofstream new_file, file_out;
    char filename[100], file_out_name[100];
    bool flag_menu1 = true;
    bool edits = false;
    Array mass(0);
    std::ofstream current_file;


    while (!StrToInt(menu1, input))
    {
        std::cout << "Введено неверное значение! Повторите попытку ввода:\n->\t";
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::getline(std::cin, input, '\n');
    }

    menu1 = stoi(input);

    while (menu1 != 0 && flag_menu1)
    {
        switch (menu1)
        {
        case 1:
        {
            CreateNewFile(filename, new_file);
            flag_menu1 = false;
            menu1 = 0;
            break;
        }
        case 2:
        {
            OpenExistingFile(filename, existing_file, mass, flag_menu1, menu1);
            break;
        }
        default:
            std::cout << "Такой позиции в списке нет! Попробуйте заново.\n";
            break;
        }
        if (menu1 != 0)
        {
            menu1_pop_up();
            std::cout << "\nВыберите опцию из меню:\n->\t";
            std::getline(std::cin, input, '\n');
            while (!StrToInt(menu1, input))
            {
                std::cout << "Введено неверное значение! Повторите попытку ввода:\n->\t";
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::getline(std::cin, input, '\n');
            }
            menu1 = stoi(input);
        }
    }
    if (!flag_menu1)
    {
        menu2_pop_up();
        int menu2;
        int num_search;
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\nВыберите опцию из меню:\n->\t";
        std::getline(std::cin, input, '\n');
        while (!StrToInt(menu2, input))
        {
            std::cout << "Введено неверное значение! Повторите попытку ввода:\n->\t";
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::getline(std::cin, input, '\n');
        }
        menu2 = stoi(input);

        while (menu2 != 0)
        {
            switch (menu2)
            {
            case 1:
                save_edits(mass, edits, filename);
                if (file_in.is_open())
                    file_in.close();
                new_file.close();
                existing_file.close();
                CreateNewFile(filename, new_file);
                new_file.close();
                mass.clear_tmp();
                break;
            case 2:
                save_edits(mass, edits, filename);
                if (file_in.is_open())
                    file_in.close();
                existing_file.close();
                new_file.close();
                OpenExistingFile(filename, existing_file, mass, flag_menu1, menu1);
                break;
            case 3:
                std::cout << "Открыт файл \"" << filename << "\".\n";
                mass.add_note();
                edits = true;
                //++arr_size;
                break;
            case 4:
                std::cout << "Открыт файл \"" << filename << "\".\n";
                mass.edit_note();
                edits = true;
                break;
            case 5:
                std::cout << "Открыт файл \"" << filename << "\".\n";
                mass.delete_note();
                edits = true;
                break;
            case 6:
                save_edits(mass, edits, filename, file_in);
                DoTask(num_search, filename, file_out_name, file_in, file_out, mass);
                break;
            case 7:
                save_edits(mass, edits, filename, file_in);
                PrintToConsole(filename, file_in, mass);
                break;
            case 8:
                save_edits(mass, edits, filename, file_in);
                PrintToTxt(filename, file_out_name, file_in, file_out, mass);
                break;
            case 9:
                mass.sorting();
                if (mass.to_binary(filename))
                {
                    std::cout << "Данные сохранены в файле \"" << filename << "\"!\n\n";
                    edits = false;
                }
                else
                    std::cout << "Не удалось сохранить данные! Ошибка чтения файла.\n\n";
                break;
            default:
                std::cout << "Такой позиции в списке нет!Попробуйте заново.\n\n";
                break;
            }
            if (menu2 != 0)
            {
                menu2_pop_up();
                std::cout << "\nВыберите опцию из меню:\n->\t";
                std::getline(std::cin, input, '\n');
                while (!StrToInt(menu2, input))
                {
                    std::cout << "Введено неверное значение! Повторите попытку ввода:\n->\t";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::getline(std::cin, input, '\n');
                }
                menu2 = stoi(input);
                std::cout << "\n\n";
            }
        }
    }
    save_edits(mass, edits, filename);
    file_in.close();
    file_out.close();
    std::cout << "-------------------\nВыход из программы.\n-------------------\n";
    std::cin.get();
    return 0;
}
