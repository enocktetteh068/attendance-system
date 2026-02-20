#ifndef ATTENDANCESESSION_H
#define ATTENDANCESESSION_H

#include <string>
#include <vector>

class AttendanceSession {
private:
    std::string date;     // e.g. "2026-02-20"
    std::string title;    // e.g. "DCN Lecture"
    std::vector<int> presentIds;

public:
    AttendanceSession(std::string date, std::string title);

    std::string getDate() const;
    std::string getTitle() const;

    void markPresent(int studentId);
    bool isPresent(int studentId) const;

    const std::vector<int>& getPresentIds() const;
    void displaySummary() const;
};

#endif