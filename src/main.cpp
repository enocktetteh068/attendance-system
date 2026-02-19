#include <iostream>
#include <vector>
#include "../include/Student.h"

int main() {
    std::vector<Student> students;
    int choice;

    do {
        std::cout << "\n===== Student Attendance System =====\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. View Students\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int id;
            std::string name;
            std::string program;

            std::cout << "Enter ID: ";
            std::cin >> id;

            std::cin.ignore(); // clear newline

            std::cout << "Enter Name: ";
            std::getline(std::cin, name);

            std::cout << "Enter Program: ";
            std::getline(std::cin, program);

            Student s(id, name, program);
            students.push_back(s);

            std::cout << "Student added successfully!\n";
        }

        else if (choice == 2) {
            if (students.empty()) {
                std::cout << "No students available.\n";
            } else {
                for (const auto& s : students) {
                    s.display();
                }
            }
        }

        else if (choice == 0) {
            std::cout << "Exiting program...\n";
        }

        else {
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}