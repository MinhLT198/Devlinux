#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "student.h"

Student::Student(const std::string& n, int p) : name(n), point(p) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    if (p < 0 || p > 10) {
        throw std::out_of_range("Point must be between 0 and 10");
    }
    
    ID = ++member;
}
Student::~Student(){};

int Student::getID() const { return ID; }
std::string Student::getName() const { return name; }
int Student::getPoint() const { return point; }

void Student::setName(const std::string& n) { name = n; }
void Student::setPoint(int p) { point = p; }

void Student::update(Student& st, const std::string& n, int p) {
    st.setName(n);
    st.setPoint(p);
}

bool Student::operator==(int ID) const {
    return this->ID == ID;
}

//in thong tin sinh vien
std::ostream& operator<<(std::ostream& os, const Student& st) {
    os << std::left
        << std::setw(6)  << st.ID
        << std::setw(15) << st.name
        << std::setw(6)  << st.point;
    return os;
}

//----------------------------------------------------------------------
void StudentList::add(const Student& st) { list.push_back(st); }

Student& StudentList::operator[](size_t index) { return list.at(index); } // an toan hon

const Student& StudentList::operator[](size_t index) const { return list.at(index); }

const std::vector<Student>& StudentList::operator()() const {return list; }

// in danh sach sinh vien
std::ostream& operator<<(std::ostream& os, const StudentList& sl) {
    for (const auto& st : sl.list) {
        os << st << std::endl;
    }
    return os;
}

// Tinh diem trung binh
float StudentList::averge() const {
    if(list.empty()) return 0;
    float sum = 0;
    for (const auto& st : list) {
        sum += st.getPoint();
    }
    return sum / list.size();
}

// Hàm tìm sinh viên trong vector
bool findStudentById(const std::vector<Student>& list, const int id) {
    if (id <= 0) return false;
    if (list.empty()) return false;

    for (const auto& st : list) {
        if (st == id) {
            return true;
        }
    }

    return false;
    //auto it = std::find_if(list.begin(), list.end(),
    //                       [id](const Student& st) { return st.getID() == id; });
    //return it != list.end();
}

// Hàm định dạng header
void formatHeader() {
    std::cout << std::string(30, '-') << "\n";
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(15) << "Name"
              << std::setw(6)  << "Point"
              << "\n";
    std::cout << std::string(30, '-') << "\n";
}

