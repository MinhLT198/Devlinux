/**
 * @file student.cpp
 * @brief Triển khai chi tiết các phương thức của lớp Student và StudentList.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "student.h"

//======================================================================
//  Triển khai class Student
//======================================================================

int Student::member = 0;

/**
 * @brief Constructor khởi tạo đối tượng Student.
 * @param n Tên sinh viên (không được rỗng).
 * @param p Điểm sinh viên (0 ≤ p ≤ 10).
 * @throw std::invalid_argument Nếu tên rỗng.
 * @throw std::out_of_range Nếu điểm ngoài khoảng [0, 10].
 */
Student::Student(const std::string& n, int p) : name(n), point(p) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    if (p < 0 || p > 10) {
        throw std::out_of_range("Point must be between 0 and 10");
    }
    ID = ++member;
}

/**
 * @brief Destructor mặc định.
 */
Student::~Student() {}

/**
 * @brief Lấy ID của sinh viên.
 * @return Mã số sinh viên.
 */
int Student::getID() const { return ID; }

/**
 * @brief Lấy tên sinh viên.
 * @return Chuỗi tên.
 */
std::string Student::getName() const { return name; }

/**
 * @brief Lấy điểm sinh viên.
 * @return Điểm (0–10).
 */
int Student::getPoint() const { return point; }

/**
 * @brief Cập nhật ID cho sinh viên.
 * @param id Mã số mới.
 */
void Student::setID(int id) { ID = id; }

/**
 * @brief Cập nhật tên sinh viên.
 * @param n Tên mới.
 */
void Student::setName(const std::string& n) { name = n; }

/**
 * @brief Cập nhật điểm sinh viên.
 * @param p Điểm mới.
 */
void Student::setPoint(int p) { point = p; }

/**
 * @brief Cập nhật thông tin sinh viên khác.
 * @param st Đối tượng Student cần cập nhật.
 * @param n Tên mới.
 * @param p Điểm mới.
 */
void Student::update(Student& st, const std::string& n, int p) {
    st.setName(n);
    st.setPoint(p);
}

/**
 * @brief So sánh Student với ID.
 * @param ID Mã số cần so sánh.
 * @return true nếu ID trùng khớp, false nếu không.
 */
bool Student::operator==(int ID) const {
    return this->ID == ID;
}

/**
 * @brief Xuất thông tin sinh viên ra luồng.
 * @param os Luồng đầu ra.
 * @param st Sinh viên cần in.
 * @return Tham chiếu đến luồng đầu ra.
 */
std::ostream& operator<<(std::ostream& os, const Student& st) {
    os << std::left
       << std::setw(6)  << st.ID
       << std::setw(15) << st.name
       << std::setw(6)  << st.point;
    return os;
}

//======================================================================
//  Triển khai class StudentList
//======================================================================

/**
 * @brief Thêm một sinh viên vào danh sách.
 * @param st Sinh viên cần thêm.
 */
void StudentList::add(const Student& st) { list.push_back(st); }

/**
 * @brief Truy cập phần tử theo chỉ số (phiên bản có thể sửa).
 * @param index Vị trí phần tử.
 * @return Tham chiếu đến Student tại vị trí index.
 * @throw std::out_of_range Nếu index không hợp lệ.
 */
Student& StudentList::operator[](size_t index) { return list.at(index); }

/**
 * @brief Truy cập phần tử theo chỉ số (phiên bản const).
 * @param index Vị trí phần tử.
 * @return Tham chiếu hằng đến Student tại vị trí index.
 * @throw std::out_of_range Nếu index không hợp lệ.
 */
const Student& StudentList::operator[](size_t index) const { return list.at(index); }

/**
 * @brief Lấy toàn bộ danh sách sinh viên (phiên bản có thể sửa).
 * @return Tham chiếu đến vector<Student>.
 */
std::vector<Student>& StudentList::operator()() { return list; }

/**
 * @brief Lấy toàn bộ danh sách sinh viên (phiên bản const).
 * @return Tham chiếu hằng đến vector<Student>.
 */
const std::vector<Student>& StudentList::operator()() const { return list; }

/**
 * @brief Xuất toàn bộ danh sách sinh viên.
 * @param os Luồng đầu ra.
 * @param sl Danh sách sinh viên.
 * @return Tham chiếu đến luồng đầu ra.
 */
std::ostream& operator<<(std::ostream& os, const StudentList& sl) {
    for (const auto& st : sl.list) {
        os << st << std::endl;
    }
    return os;
}

/**
 * @brief Tính điểm trung bình của danh sách sinh viên.
 * @return Điểm trung bình, hoặc 0 nếu danh sách rỗng.
 */
float StudentList::averge() const {
    if (list.empty()) return 0;
    float sum = 0;
    for (const auto& st : list) {
        sum += st.getPoint();
    }
    return sum / list.size();
}

/**
 * @brief Tìm sinh viên theo ID.
 * @param list Vector sinh viên.
 * @param id ID cần tìm.
 * @return true nếu tồn tại sinh viên có ID, false nếu không.
 */
bool StudentList::findID(const std::vector<Student>& list, int id) {
    if (id <= 0 || list.empty()) return false;
    for (const auto& st : list) {
        if (st == id) {
            return true;
        }
    }
    return false;
}

/**
 * @brief In tiêu đề bảng danh sách sinh viên.
 */
void StudentList::formatHeader() {
    std::cout << std::string(30, '-') << "\n";
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(15) << "Name"
              << std::setw(6)  << "Point"
              << "\n";
    std::cout << std::string(30, '-') << "\n";
}

/**
 * @brief In hướng dẫn sử dụng các lệnh.
 */
void StudentList::Help() {
    std::cout << std::string(30, '-') << "\n";
    std::cout << std::left
              << std::setw(30) << "'a' -> them sinh vien"
              << std::setw(30) << "'r' -> xoa sinh vien"
              << std::setw(30) << "'u' -> cap nhat thong tin sinh vien\n"
              << std::setw(30) << "'l' -> in danh sach sinh vien"
              << std::setw(30) << "'m' -> diem trung binh"
              << std::setw(30) << "'q' -> thoat"
              << std::endl;
    std::cout << std::string(30, '-') << "\n";
}
