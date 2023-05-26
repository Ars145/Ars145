#pragma once
#include "Group.hpp"
#include "Stream.hpp"
#include "Student.hpp"
#include <ostream>
#include <istream>
class Menu{
private:
    Student * read_student(std::istream & is);//Чтение студента с проверкой на корректность входных данных
public:
    void print_menu_1(Stream & s);//Меню выбора пункта 1: ввод информации о потоке через консоль
    void print_menu_2(Stream & s);//Ввод информации о потоке из файла
    void print_menu_3(Stream & s);//Печать на консоль состояния потока
    void print_menu_start(Stream & s);//Стартовое меню
    void save_at_file(Stream & s);//Выбор пункта 4 - сохранение состояния потока в файл
    void delete_student(Stream & s);//Удаление студента с ФИО и группой
    void delete_group(Stream & s);//Кдаление группы с потока с номером
    void print_variant(Stream & s);//Задание по варианту : Вывод студентов без стипендии из групп, в которых количество таковых не менее числа min
};
