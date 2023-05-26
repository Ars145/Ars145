#pragma once
#include <iostream>
#include <ostream>
#include <vector>
class Student;//обьявление класса Student для использования
#include "Student.hpp"

class Group {
private:
	unsigned int group_number;//номер группы
	std::vector<Student *> students;//Массив указателей на студентов
public:
	Group(unsigned int group_number);
    ~Group();
	unsigned int get_group_number();
	void set_group_number(unsigned int new_group_number);
    void print_students_no_grand();//Вывод на консоль студентов, не получающих стипендию(задание по варианту)
    int count_grant();//Количество студентов со стипендией
	void add_student(Student * student);
    void delete_student(int student_index);
	void delete_student(std::string fio);
    int size(){return students.size();}//Количество студентов в группе
	Student * get_student(unsigned int student_index);

	friend std::ostream& operator << (std::ostream &os, Group &g);//Перегрузка оператора вывода для записи в файл либо консоль информации о потоке
};

