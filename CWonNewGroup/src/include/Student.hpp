#pragma once

#include <ostream>
#include <string>
#include "Group.hpp"
class Group;
class Student {
private:
	std::string FIO;
	int group;
	int * marks;
	bool granded;
	unsigned int grand;
public:
	Student(std::string FIO, int group, int * marks, bool granded, unsigned int grand);
    ~Student();
	std::string get_FIO();
	void set_FIO(std::string FIO);

	int* get_marks();
	void set_marks(int * marks);

	bool is_granded();
	void set_granded(bool granded);
    void print_marks();//Печать оценок студента
	unsigned int get_grand();
	void set_grand(unsigned int grand);
    int get_group() {return group;}
};
std::ostream& operator << (std::ostream &os, Student &s); 
