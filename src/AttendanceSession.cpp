#include "../include/AttendanceSession.h"
#include <iostream>

AttendanceSession::AttendanceSession(std::string date, std::string title)
    : date(date), title(title) {}

std::string AttendanceSession::getDate() const { return date; }
std::string AttendanceSession::getTitle() const { return title; }

bool AttendanceSession::isPresent(int studentId) const {
    for (int id : presentIds) {
        if (id == studentId) return true;
    }
    return false;
}

void AttendanceSession::markPresent(int studentId) {
    if (!isPresent(studentId)) {
        presentIds.push_back(studentId);
    }
}

const std::vector<int>& AttendanceSession::getPresentIds() const {
    return presentIds;
}

void AttendanceSession::displaySummary() const {
    std::cout << "Session: " << title << " | Date: " << date
              << " | Present: " << presentIds.size() << "\n";
}