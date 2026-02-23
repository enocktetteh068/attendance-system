#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
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

    if (id <= 0) {
        std::cout << "Student ID must be positive.\n";
        return;
    }

    if (idExists(students, id)) {
        std::cout << "That ID already exists. Student not added.\n";
        return;
    }

    std::string name = readLine("Enter student name: ");
    if (name.empty()) {
        std::cout << "Name cannot be empty.\n";
        return;
    }

    std::string program = readLine("Enter program: ");
    if (program.empty()) {
        std::cout << "Program cannot be empty.\n";
        return;
    }

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
    if (date.empty()) {
        std::cout << "Date cannot be empty.\n";
        return;
    }

    std::string title = readLine("Enter session title: ");
    if (title.empty()) {
        std::cout << "Title cannot be empty.\n";
        return;
    }

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
    std::cout << "\n===== Session Details =====\n";
    session.displaySummary();

    const auto& present = session.getPresentIds();

    // Present list
    std::cout << "\nPresent students:\n";
    if (present.empty()) {
        std::cout << "None\n";
    } else {
        for (int id : present) {
            for (const auto& s : students) {
                if (s.getId() == id) {
                    s.display();
                    break;
                }
            }
        }
    }

    // Absent list (computed)
    std::cout << "\nAbsent students:\n";
    int absentCount = 0;
    for (const auto& s : students) {
        if (!session.isPresent(s.getId())) {
            s.display();
            absentCount++;
        }
    }
    if (absentCount == 0) std::cout << "None\n";

    int total = (int)students.size();
    int presentCount = (int)present.size();
    double rate = (total == 0) ? 0.0 : (presentCount * 100.0 / total);

    std::cout << "\nTotal: " << total
              << " | Present: " << presentCount
              << " | Absent: " << absentCount
              << " | Attendance: " << rate << "%\n";
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

void generateReport(const std::vector<Student>& students,
                    const std::vector<AttendanceSession>& sessions) {

    if (sessions.empty()) {
        std::cout << "No sessions available.\n";
        return;
    }

    listSessions(sessions);
    int pick = readInt("Choose session number: ");
    if (pick < 1 || pick > (int)sessions.size()) {
        std::cout << "Invalid session.\n";
        return;
    }

    const AttendanceSession& session = sessions[pick - 1];
    const auto& present = session.getPresentIds();

    int total = (int)students.size();
    int presentCount = (int)present.size();
    int absentCount = total - presentCount;
    double rate = (total == 0) ? 0.0 : (presentCount * 100.0 / total);

    std::cout << "\n===== ATTENDANCE REPORT =====\n";
    std::cout << "Session: " << session.getTitle()
              << " | Date: " << session.getDate() << "\n";
    std::cout << "Total Students: " << total << "\n";
    std::cout << "Present: " << presentCount << "\n";
    std::cout << "Absent: " << absentCount << "\n";
    std::cout << "Attendance Rate: " << rate << "%\n";
}

const std::string STUDENTS_FILE = "students.txt";

void saveStudents(const std::vector<Student>& students) {
    std::ofstream out(STUDENTS_FILE);
    if (!out) {
        std::cout << "Error: could not save students.\n";
        return;
    }

    for (const auto& s : students) {
        out << s.getId() << "|" << s.getName() << "|" << s.getProgram() << "\n";
    }
}

void loadStudents(std::vector<Student>& students) {
    students.clear();

    std::ifstream in(STUDENTS_FILE);
    if (!in) {
        // File doesn't exist yet (first run) — not an error.
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name, program;

        if (!std::getline(ss, idStr, '|')) continue;
        if (!std::getline(ss, name, '|')) continue;
        if (!std::getline(ss, program)) continue;

        try {
            int id = std::stoi(idStr);
            if (id > 0 && !name.empty() && !program.empty()) {
                students.push_back(Student(id, name, program));
            }
        } catch (...) {
            // skip bad lines
        }
    }
}

const std::string STUDENTS_FILE = "students.txt";

void saveStudents(const std::vector<Student>& students) {
    std::ofstream out(STUDENTS_FILE);
    if (!out) {
        std::cout << "Error: could not save students.\n";
        return;
    }

    for (const auto& s : students) {
        out << s.getId() << "|" << s.getName() << "|" << s.getProgram() << "\n";
    }
}

void loadStudents(std::vector<Student>& students) {
    students.clear();

    std::ifstream in(STUDENTS_FILE);
    if (!in) {
        // File doesn't exist yet (first run) — not an error.
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, name, program;

        if (!std::getline(ss, idStr, '|')) continue;
        if (!std::getline(ss, name, '|')) continue;
        if (!std::getline(ss, program)) continue;

        try {
            int id = std::stoi(idStr);
            if (id > 0 && !name.empty() && !program.empty()) {
                students.push_back(Student(id, name, program));
            }
        } catch (...) {
            // skip bad lines
        }
    }
}

const std::string SESSIONS_FILE = "sessions.txt";

std::string joinIds(const std::vector<int>& ids) {
    std::ostringstream out;
    for (size_t i = 0; i < ids.size(); i++) {
        out << ids[i];
        if (i + 1 < ids.size()) out << ",";
    }
    return out.str();
}

std::vector<int> splitIds(const std::string& s) {
    std::vector<int> ids;
    std::stringstream ss(s);
    std::string token;

    while (std::getline(ss, token, ',')) {
        if (token.empty()) continue;
        try {
            ids.push_back(std::stoi(token));
        } catch (...) {
            // skip bad token
        }
    }
    return ids;
}

void saveSessions(const std::vector<AttendanceSession>& sessions) {
    std::ofstream out(SESSIONS_FILE);
    if (!out) {
        std::cout << "Error: could not save sessions.\n";
        return;
    }

    for (const auto& session : sessions) {
        out << session.getDate() << "|"
            << session.getTitle() << "|"
            << joinIds(session.getPresentIds()) << "\n";
    }
}

void loadSessions(std::vector<AttendanceSession>& sessions) {
    sessions.clear();

    std::ifstream in(SESSIONS_FILE);
    if (!in) return;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string date, title, idsStr;

        if (!std::getline(ss, date, '|')) continue;
        if (!std::getline(ss, title, '|')) continue;
        std::getline(ss, idsStr); // may be empty

        if (date.empty() || title.empty()) continue;

        AttendanceSession session(date, title);

        auto ids = splitIds(idsStr);
        for (int id : ids) {
            session.markPresent(id); // prevents duplicates automatically
        }

        sessions.push_back(session);
    }
}

int main() {
    std::vector<Student> students;
    std::vector<AttendanceSession> sessions;

    loadStudents(students);
    loadSessions(sessions);

    std::cout << "Loaded " << students.size() << " students and "
          << sessions.size() << " sessions.\n";

    int choice;
    do {
        std::cout << "\n===== Student Attendance System (Week 2) =====\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. View Students\n";
        std::cout << "3. Create Attendance Session\n";
        std::cout << "4. Mark Attendance (Present)\n";
        std::cout << "5. View Session Details\n";
        std::cout << "6. Generate Session Report\n";
        std::cout << "0. Exit\n";

        choice = readInt("Choose an option: ");

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: viewStudents(students); break;
            case 3: createSession(sessions); break;
            case 4: markAttendance(students, sessions); break;
            case 5: viewSessionDetails(students, sessions); break;
            case 6: generateReport(students, sessions); break;
            case 0:
                saveStudents(students);
                saveSessions(sessions);
                std::cout << "Saved. Goodbye.\n";
                break;
            default: std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}