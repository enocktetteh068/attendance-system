#include "Student.h"
#include <iostream>

Student::Student(int id, std::string name, std::string program) {
    this->id = id;
    this->name = name;
    this->program = program;
}

int Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getProgram() const {
    return program;
}

void Student::display() const {
    std::cout << "ID: " << id
              << " | Name: " << name
              << " | Program: " << program
              << std::endl;
}