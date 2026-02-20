#include <iostream>
#include <vector>
#include <limits>
#include "../include/Student.h"
#include "../include/AttendanceSession.h"

int readInt(const std::string& prompt) {
    int x;
    while (true) {
        std::cout << prompt;
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Invalid number. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

bool idExists(const std::vector<Student>& students, int id) {
    for (const auto& s : students) {
        if (s.getId() == id) return true;
    }
    return false;
}

int findSessionIndex(const std::vector<AttendanceSession>& sessions,
                     const std::string& date,
                     const std::string& title) {
    for (int i = 0; i < (int)sessions.size(); i++) {
        if (sessions[i].getDate() == date && sessions[i].getTitle() == title) {
            return i;
        }
    }
    return -1;
}

void addStudent(std::vector<Student>& students) {
    int id = readInt("Enter student ID: ");
    if (idExists(students, id)) {
        std::cout << "That ID already exists. Student not added.\n";
        return;
    }
    std::string name = readLine("Enter student name: ");
    std::string program = readLine("Enter program: ");

    students.push_back(Student(id, name, program));
    std::cout << "Student added successfully.\n";
}

void viewStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students added yet.\n";
        return;
    }
    std::cout << "\n--- Student List (" << students.size() << ") ---\n";
    for (const auto& s : students) s.display();
}

void createSession(std::vector<AttendanceSession>& sessions) {
    std::string date = readLine("Enter session date (e.g., 2026-02-20): ");
    std::string title = readLine("Enter session title (e.g., DCN Lecture): ");

    if (findSessionIndex(sessions, date, title) != -1) {
        std::cout << "Session already exists.\n";
        return;
    }

    sessions.push_back(AttendanceSession(date, title));
    std::cout << "Session created successfully.\n";
}

void listSessions(const std::vector<AttendanceSession>& sessions) {
    if (sessions.empty()) {
        std::cout << "No sessions created yet.\n";
        return;
    }
    std::cout << "\n--- Sessions (" << sessions.size() << ") ---\n";
    for (int i = 0; i < (int)sessions.size(); i++) {
        std::cout << (i + 1) << ". ";
        sessions[i].displaySummary();
    }
}

void markAttendance(const std::vector<Student>& students,
                    std::vector<AttendanceSession>& sessions) {
    if (students.empty()) {
        std::cout << "Add students first.\n";
        return;
    }
    if (sessions.empty()) {
        std::cout << "Create a session first.\n";
        return;
    }

    listSessions(sessions);
    int pick = readInt("Choose session number: ");
    if (pick < 1 || pick > (int)sessions.size()) {
        std::cout << "Invalid session.\n";
        return;
    }

    AttendanceSession& session = sessions[pick - 1];

    std::cout << "\nMarking attendance for: " << session.getTitle()
              << " (" << session.getDate() << ")\n";
    std::cout << "Enter student IDs to mark PRESENT.\n";
    std::cout << "Type -1 to stop.\n\n";

    while (true) {
        int id = readInt("Student ID: ");
        if (id == -1) break;

        if (!idExists(students, id)) {
            std::cout << "No student with that ID.\n";
            continue;
        }

        if (session.isPresent(id)) {
            std::cout << "Already marked present.\n";
            continue;
        }

        session.markPresent(id);
        std::cout << "Marked present.\n";
    }
}

void viewSessionDetails(const std::vector<Student>& students,
                        const std::vector<AttendanceSession>& sessions) {
    if (sessions.empty()) {
        std::cout << "No sessions created yet.\n";
        return;
    }

    listSessions(sessions);
    int pick = readInt("Choose session number: ");
    if (pick < 1 || pick > (int)sessions.size()) {
        std::cout << "Invalid session.\n";
        return;
    }

    const AttendanceSession& session = sessions[pick - 1];
    session.displaySummary();

    const auto& present = session.getPresentIds();

    std::cout << "\nPresent students:\n";
    if (present.empty()) {
        std::cout << "None\n";
        return;
    }

    for (int id : present) {
        for (const auto& s : students) {
            if (s.getId() == id) {
                s.display();
                break;
            }
        }
    }

    int absentCount = (int)students.size() - (int)present.size();
    if (absentCount < 0) absentCount = 0; // safety
    std::cout << "\nAbsent count (auto): " << absentCount << "\n";
}

int main() {
    std::vector<Student> students;
    std::vector<AttendanceSession> sessions;

    int choice;
    do {
        std::cout << "\n===== Student Attendance System (Week 2) =====\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. View Students\n";
        std::cout << "3. Create Attendance Session\n";
        std::cout << "4. Mark Attendance (Present)\n";
        std::cout << "5. View Session Details\n";
        std::cout << "0. Exit\n";

        choice = readInt("Choose an option: ");

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: viewStudents(students); break;
            case 3: createSession(sessions); break;
            case 4: markAttendance(students, sessions); break;
            case 5: viewSessionDetails(students, sessions); break;
            case 0: std::cout << "Goodbye.\n"; break;
            default: std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}