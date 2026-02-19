#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    int id;
    std::string name;
    std::string program;

public:
    Student(int id, std::string name, std::string program);

    int getId() const;
    std::string getName() const;
    std::string getProgram() const;

    void display() const;
};

#endif