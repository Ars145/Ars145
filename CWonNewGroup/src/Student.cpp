#include <iostream>
#include "include/Student.hpp"


Student::Student(std::string FIO, int group, int * marks, bool granded, unsigned int grand) {
	this->FIO = FIO;
	this->group = group;
	this->marks = marks;
	this->granded = granded;
	this->grand = grand;
}

Student::~Student() {
    if(marks != nullptr)
        delete [] marks;
    marks = nullptr;
}
std::string Student::get_FIO() {
	return this->FIO;
}

void Student::set_FIO(std::string FIO) {
	this->FIO = FIO;
}


int * Student::get_marks() {
	return this->marks;
}
void Student::set_marks(int * marks) {
	delete[] marks;
	this->marks = marks;
}

bool Student::is_granded() {
	return this->granded;
}
void Student::set_granded(bool granded) {
	this->granded = granded;
}

unsigned int Student::get_grand() {
	return this->grand;
}

void Student::print_marks() {
    for(int i = 0; i < 5; i++)
        std::cout<<marks[i]<<" ";
}
void Student::set_grand(unsigned int grand) {
	this->grand = grand;
}
std::ostream& operator << (std::ostream &os, Student &s) {//Пергруженный оператор вывода в соответствии с правилами
	os << s.get_FIO() << " "<<s.get_group()<<" ";//вывод ФИО и номера группы
    if (s.is_granded()) {//Если студент получает стипендию
        os<<"1 "<<std::to_string(s.get_grand())<<" ";//Вывод 1 и числа - размер стипендии
    } else {
        os<<"0 ";//Вывод 0 , если студент не получает стипендию
    }
    int * marks = s.get_marks();//Печать оценок студента
    for (int i = 0; i < 5; i++) {//
        os << marks[i] << ' ';
    }
    os<<std::endl;
    return os;
}
