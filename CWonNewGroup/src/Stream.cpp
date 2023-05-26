#include "include/Stream.hpp"
#include <iostream>

Stream::~Stream() {
    for(int i = 0; i < groups.size(); i++) {
        if(groups[i] != nullptr) {
            delete groups[i];
            groups[i] = nullptr;
        }
    }
    groups.clear();
}

void Stream::add_group(Group * group) {
	groups.push_back(group);
}
void Stream::add_student(Student *student) {//Добавление студента в поток
    for(int i = 0; i < groups.size(); i++) {
        if(groups[i]->get_group_number() == student->get_group()) {//Если совпадает номер группы у студента и группы
            groups[i]->add_student(student);//Добавляем студента в группу
            return;//Выход из функции
        }
    }
    Group * new_group = new Group(student->get_group());//Если цикл завершился без выходов из функции, значит студент из новой группы
    new_group->add_student(student);//Добавляем студента в созданную группу
    groups.push_back(new_group);//Добавляем новую группу в поток
}

void Stream::delete_student(std::string fio, int group) {//Удаление студента из потока
    for(int i = 0; i < groups.size(); i++) {
        if(groups[i]->get_group_number() == group) {//Находим группу студента
            groups[i]->delete_student(fio);//Удаляем студента с ФИО = fio из группы с номером group
        }
        if(groups[i]->size() == 0)//Если после удаления студента группа стала пустой
            delete_group(i); //Удаляем группу
    }
}

void Stream::delete_group_number(int groups_number) {//Удаление группы по номеру группы
    for(int i = 0; i < groups.size(); i++) {
        if(groups[i]->get_group_number() == groups_number) {//Найдена группа с номером groups_number
            delete_group(i);//Удаление группы с индексом i в вектое groups
        }
    }
}

void Stream::delete_group(unsigned int groups_index) {//Удаление группы с индексом groups_index в массиве groups
    groups[groups_index] = nullptr;//Указатель на nullptr чтобы не повлиять на данные о студентах
	for(int i = groups_index; i < groups.size() - 1; i++) {//Сдвиг массива на 1 позицию влево начиная с groups_index
        groups[groups_index] = groups[groups_index + 1];
    }
    groups[groups.size() - 1] = nullptr;//Указатель для последнего элемента чтоб не портить данные
    groups.pop_back();//Уменьшение размера groups, удаление последней группы
}

Group * Stream::get_group(unsigned int group_index) {
	return groups[group_index];
}

void Stream::sort_groups() {
	std::sort(groups.begin(), groups.end(), groups_cmp);
}

bool groups_cmp(Group * g1, Group * g2) { //сравнение по номеру группы
	return g1->get_group_number() < g2->get_group_number();
}

void Stream::print_list_variant(int Min){ //Задание по варианту
    sort_groups();//Сортируем группы по номеру
    for(int i = 0; i < groups.size(); i++) {
        if(groups[i] != nullptr && groups[i]->size() - groups[i]->get_group_number() > Min) { //если количество студентов в группе без стипендии больше min
            std::cout<<groups[i]->get_group_number()<<std::endl;//Печать номера группы
            groups[i]->print_students_no_grand();//печать студентов, которые не получают стипендию в этой группе
        }
    }
}

std::ostream& operator << (std::ostream& os, Stream & s) {
	for (int i = 0; i < s.groups.size(); i++) {
		os << *(s.groups[i]);
	}
	return os;
}

