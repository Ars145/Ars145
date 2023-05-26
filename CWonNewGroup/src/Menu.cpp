#include <iostream>
#include "include/Menu.hpp"
#include <fstream>
bool is_number(std::string str) { //проверка на число
    for(int i = 0; i < str.size(); i++)
        if(str[i] < '0' || str[i] > '9') return false;
    return true;
}

bool is_correct_name(std::string str) {//имя введено без чисел
    for(int i = 0; i < str.size(); i++)
        if(str[i] >= '0' && str[i] <= '9') return false;
    return true;
}

Student * Menu::read_student(std::istream &is) { //считывание информации о студенте
    //если студент считан, вернет указатель на него, в противном случае - nullptr
    std::string surname, name, father_name, group, gr, grand = "0";//строки для считывания
    is>>surname>> name>> father_name>> group>> gr;//Считываем все до стипендии(возможно она не понадобится)
    if(!is_correct_name(surname) || !is_correct_name(name) || !is_correct_name(father_name)) {//Проверка на правильность ФИО
        std::cout<<"Bad info about fio student :"<<surname<<" "<<name<<" "<<father_name<<std::endl;
        return nullptr;//Студент не считан
    }
    if(!is_number(group)) { //Проверка на корректность номера группы (число)
        std::cout<<"Bad group "<<group<<std::endl;
        return nullptr;//Студент не считан
    }
    if(!(gr == "0" || gr == "1")) {//Проверка на корректность флага о наличии стипендии
        std::cout<<"Bad grand info (must be 0/1) "<<group<<std::endl;
        return nullptr;//Студент не считан
    }
    if(gr == "1")//Если есть стипендия, то ее нужно считать
        is>>grand;
    if(!is_number(grand)) {//Проверка на корректность стипендии (число)
        std::cout<<"BadGrand "<<grand;
        return nullptr;//Студент не считан
    }
    int * marks = new int[5];
    for(int i = 0; i < 5; i++) {//Считывание пяти оценок
        std::string mark;
        is>>mark;
        if(!is_number(mark)) {
            std::cout<<"Bad mark"<<std::endl;
            return nullptr;
        }
        marks[i] = std::stoi(mark);
    }
    //Создание нового студента
    Student * new_student = new Student(surname +" "+ name +" "+ father_name, std::stoi(group), marks, (bool)std::stoi(gr), std::stoi(grand));
    return new_student;//Студент создан
}

void Menu::print_menu_1(Stream & s) {
    std::cout<<"Enter F I O numGroup 0/1(is grant or no) grant without tabs"<<std::endl;
    std::cout<<"and five marks "<<std::endl;
    bool flag = true;//Флаг на желание пользователя ввести данные
    while (flag) {
        std::cout<<"continue enter? y/n"<<std::endl;
        std::string command;
        std::cin>>command;
        if(command == "y") {//y - да,
            Student *student = read_student(std::cin);
            if (student != nullptr) {
                s.add_student(student);
            }
        } else {//Любой другой символ - нет
            flag = false;
            print_menu_start(s);
        }
    }
    print_menu_start(s);//Возвращение к главному меню
}
void Menu::print_menu_2(Stream & s) {//считывание с файла
    std::cout<<"Enter filename_to_read :"<<std::endl;
    std::string filename;//Создание файлового потока ввода и его открытие
    std::cin>>filename;
    std::ifstream ifs;
    ifs.open(filename);
    if(ifs.is_open()) {
        while (ifs) {//Считывание с файла до конца
            Student * student = read_student(ifs);//Считывание студента
            if(student != nullptr)//Студент успешно считан и создан
                s.add_student(student);//Добавление студента в поток
        }
    } else {
        std::cout<<"bad file"<<std::endl;
    }
    ifs.close();
    print_menu_start(s);//Возвращение к глвному меню
}

void Menu::print_menu_3(Stream & s) { //печать потока
    std::cout<<s;
    print_menu_start(s);
}

void Menu::save_at_file(Stream &s) {
     std::cout<<"Enter fileName for save :";
     std::string filename;
     std::cin>>filename;
     std::ofstream ofs;//Создание и открытие файлового потока вывода
     ofs.open(filename);
     if(ofs.is_open()) {
         ofs<<s;//Вывод информации о потоке(оператор вывода перегружен в соответствии с правилами ввода)
     } else {
         std::cout<<"Bad file"<<std::endl;
     }
     print_menu_start(s);//Возвращение на главное меню
}
void Menu::delete_group(Stream &s) {
    std::string num_group;
    std::cin>>num_group;
    if(is_number(num_group)) {//Корректность введенного номера группы
        std::cout<<"Delete group "<<num_group<<std::endl;
        s.delete_group_number(std::stoi(num_group));//удаление группы из потока
        std::cout<<"Exelent"<<std::endl;
    }
    print_menu_start(s);//Возвращение к главному меню
}
void Menu::delete_student(Stream &s) {
    std::string f,i,o,fio;//Строки фамилия, имя, отчество, ФИО
    int group;
    std::cin>>f>>i>>o;
    fio = f+" "+i+" " + o;//Создание строки ФИО
    std::string num;//номер группы
    std::cin>>num;
    if(is_number(num)) {//Проверка на валидность данных
        s.delete_student(fio, std::stoi(num));//Удаление студента с номером группы num и ФИО fio
        std::cout<<"Exelent"<<std::endl;
    }
    print_menu_start(s);//Возвращение к стартовому меню
}
void Menu::print_variant(Stream & s) {
    std::cout<<"Enter min for count of students without grand: "<<std::endl;
    std::string min;//строка для записи минимального количества студентов без стипендии в группе
    std::cin>>min;
    if(is_number(min)) {//Проверка на валидность числа
        s.print_list_variant(std::stoi(min));//Печать студентов без стипендии из групп, в которыхколичество таковых не меньше min
    } else {
        std::cout<<"Bad number of min "<<std::endl;
    }
    print_menu_start(s);//Возвращение к стартовому меню
}

void Menu::print_menu_start(Stream & s) {
    //Инфо
    std::cout<<"What command do you need?"<<std::endl<<"1 - make stream by console\n2 - make stream by file\n3 - print stream 4 - save stream to file\n0 - exit\n";
    std::cout<<"5 <number> delete student with number\n6 <number> - delete group \n7 - for set min count"<<std::endl;
    std::string com;//Команда
    while (com != "1" && com != "2" && com != "3" && com != "0" && com != "4" && com != "5" && com != "6" && com != "7") {
        std::cin >> com;//Бесконечный ввод до тех пор, пока не будет выбрана опция из меню
    }
    switch (com[0]) { //"1" = {'1'};
        case '1':
            print_menu_1(s);
            break;
        case '2':
            print_menu_2(s);
            break;
        case '3':
            print_menu_3(s);
            break;
        case '4':
            save_at_file(s);
            break;
        case '5':
            delete_student(s);
            break;
        case '6':
            delete_group(s);
            break;
        case '7':
            print_variant( s);
            break;
        case '0':
            return;
    }
}