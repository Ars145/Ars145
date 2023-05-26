#pragma once

#include <algorithm>
#include <ostream>

#include "Group.hpp"
#include "Student.hpp"

class Stream {
private:
	std::vector<Group *> groups;
	void sort_groups();
    void delete_group(unsigned int group_index);//Удаление группы по индексу в векторе групп
public:
    Stream() = default;

	~Stream();
    void add_group(Group * group);
    void delete_student(std::string fio, int group);//Удаление студента с потока по ФИО и группе
    void delete_group_number(int groups_number);//Удаление группы по номеру группы
    void add_student(Student * student);
	Group * get_group(unsigned int group_index);
	friend std::ostream& operator << (std::ostream& os, Stream & s);
    void print_list_variant(int Min);//Задание по варианту: печать студентов без стипендии из тех групп, количество таковых в которых не менее числа Min
};

bool groups_cmp(Group * g1, Group * g2); //Функция сравнения для сортировки
