#include "include/Group.hpp"
#include <iostream>
#include <ostream>
Group::Group(unsigned int group_number) {
	this->group_number = group_number;
}

Group::~Group() {//Деструктор
    for(int i = 0; i < students.size(); i++) {
        if(students[i] != nullptr) {
            delete students[i];
            students[i] = nullptr;
        }
    }
    students.clear();
}
unsigned int Group::get_group_number() {
	return this->group_number;
}

void Group::set_group_number(unsigned int group_number) {
	this->group_number = group_number;
}

void Group::add_student(Student * student) {
	students.push_back(student);
}

void Group::delete_student(int student_index) {//Удаление student_index-го студента из массива
    for(int i = student_index; i < students.size() - 1; i++) {
        students[i] = students[i + 1];
    }
    students[students.size()- 1]= nullptr;
    students.pop_back();
}
void Group::delete_student(std::string fio) {
    for(int i = 0; i < students.size(); i++) {
        if(students[i]->get_FIO() == fio) {//Если совпало ФИО
            delete students[i];
            students[i] = nullptr;
            delete_student(i);//Удаляем этого студента
            return;
        }
    }
}

Student * Group::get_student(unsigned int student_index) {
    return students[student_index];
}

int Group::count_grant() {
    int count = 0;//Переменная счетчик
    for(int i = 0; i < students.size(); i++) {
        if(students[i]->is_granded())//Если получает стипендию
            count++;
    }
    return count;
}
void Group::print_students_no_grand() {//Вспомогательная функци для задания по варианту
    std::cout<<"Number Group : "<< this->group_number<<std::endl;
    std::cout<<"Students without grand:"<<std::endl;
    for(int i = 0; i < students.size(); i++) {
        if(students[i] != nullptr && !students[i]->is_granded()) {//Если студент существует и без стипендии
            std::cout<<students[i]->get_FIO()<<"\tmarks:";//печатаем его ФИО и оценки
            students[i]->print_marks();
            std::cout<<std::endl;
        }
    }
}
std::ostream& operator << (std::ostream &os, Group &g) {
	for (int i = 0; i < g.students.size(); i++) {
		os << *(g.students[i]);//Вывод каждого студента в группе
	}
	os << '\n';
	return os;
}
