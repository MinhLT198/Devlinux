#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <string>
#include "student.h"

int Student::member = 0;

int main() {
    StudentList sl;
    int id, point;
    std::string name;

    sl.add(Student("Alice", 8));
    sl.add(Student("Bob", 7));
    sl.add(Student("Charlie", 9));
    
    // In header
    std::cout << "DANH SACH SINH VIEN\n";
    formatHeader();
    std::cout << sl;  // in toàn bộ danh sách

    // Cập nhật thông tin sinh viên 
    std::cout << "\nThay doi thong tin sinh vien ( ID Name Point )\n";
    std::cin >> id >> name >> point;
    if(findStudentById(sl(), id)) {
        sl[id-1].update(sl[id-1], name, point);
    } else {
        std::cout << "Khong tim thay sinh vien co ID = " << id << std::endl;
    }
    
    std::cout << "\nDanh sach sinh vien sau khi cap nhat:\n";
    formatHeader();
    std::cout << sl;

    std::cout << "\nDiem trung binh: " << sl.averge() << std::endl;
    return 0;
}