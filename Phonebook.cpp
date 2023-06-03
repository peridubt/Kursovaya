#include "Array.h"

void Phonebook::print(std::ostream& stream) 
{
    stream << "ФИО:\t" << FIO <<'\n';
    stream << "Адрес:\tул. " << street << ", д. " << house_num << ", кв. " << flat_num << "\n";
    stream << "Номер телефона:\t" << phone_number <<'\n';
    stream << "----------------------------------\n\n";
}

int Phonebook::compare(const Phonebook& phnbk) 
{
    return strcmp(FIO, phnbk.FIO);
}
