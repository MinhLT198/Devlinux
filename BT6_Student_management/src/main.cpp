/**
 * @file main.cpp
 * @brief Chương trình chính để quản lý danh sách sinh viên.
 *
 * Cung cấp menu thao tác:
 * - 'a' : thêm sinh viên
 * - 'r' : xóa sinh viên theo ID
 * - 'u' : cập nhật thông tin sinh viên
 * - 'l' : in danh sách sinh viên
 * - 'm' : tính điểm trung bình
 * - 'q' : thoát chương trình
 */

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include "student.h"

/**
 * @brief Hàm main, điểm bắt đầu của chương trình.
 * @return 0 nếu chạy thành công.
 */
int main() {
    StudentList sl;
    int id, point;
    std::string name;
    char mode;

    // Thêm dữ liệu ban đầu
    sl.add(Student("Alice", 8));
    sl.add(Student("Bob", 7));
    sl.add(Student("Charlie", 9));
    
    // In danh sách ban đầu
    std::cout << "DANH SACH SINH VIEN\n";
    sl.formatHeader();
    std::cout << sl;

    // Menu lặp
    while (true) {
        sl.Help();
        std::cout << "\nNhap mode: ";
        std::cin >> mode;

        if (mode == 'q') {
            std::cout << "Thoat chuong trinh.\n";
            break;
        }

        switch (mode) {
        case 'a': {
            std::cout << "\nNhap ten va diem: ";
            std::cin >> name >> point;
            try {
                sl.add(Student(name, point));
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            break;
        }
        case 'r': {
            std::cout << "\nNhap ID sinh vien can xoa: ";
            std::cin >> id;
            if (sl.findID(sl(), id)) {
                sl().erase(sl().begin() + (id - 1)); 
                // cập nhật lại ID
                for (size_t i = id - 1; i < sl().size(); ++i) {
                    sl()[i].setID(i + 1);
                }
                Student::member--; 
                std::cout << "Da xoa sinh vien co ID = " << id << std::endl;
            } else {
                std::cout << "Khong tim thay sinh vien co ID = " << id << std::endl;
            }
            break;
        }
        case 'u': {
            std::cout << "\nThay doi thong tin sinh vien ( ID Name Point )\n";
            std::cin >> id >> name >> point;
            if (sl.findID(sl(), id)) {
                sl[id - 1].update(sl[id - 1], name, point);
            } else {
                std::cout << "Khong tim thay sinh vien co ID = " << id << std::endl;
            }
            break;
        }
        case 'l':
            std::cout << "\nDANH SACH SINH VIEN\n";
            sl.formatHeader();
            std::cout << sl;
            break;
        case 'm':
            std::cout << "\nDiem trung binh: " << sl.averge() << std::endl;
            break;
        default:
            std::cout << "Lenh khong hop le!\n";
            break;
        }
    }

    return 0;
}
