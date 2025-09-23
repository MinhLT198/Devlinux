#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <vector>

/**
 * @file Student.h
 * @brief Định nghĩa lớp Student và StudentList để quản lý sinh viên.
 *
 * - Student: đại diện cho một sinh viên (ID, tên, điểm).
 * - StudentList: quản lý tập hợp sinh viên, hỗ trợ thêm, tìm kiếm, in danh sách.
 */

//======================================================================
//  Lớp Student
//======================================================================

/**
 * @brief Lớp đại diện cho một sinh viên.
 */
class Student
{
private: 
    int ID;             ///< Mã số sinh viên  
    std::string name;   ///< Tên sinh viên
    int point;          ///< Điểm sinh viên
public:
    static int member;  ///< Số lượng sinh viên hiện có

    /**
     * @brief Constructor có kiểm tra dữ liệu.
     * @param n Tên sinh viên (không được rỗng).
     * @param p Điểm sinh viên (từ 0 đến 10).
     */
    Student(const std::string& n, int p) ;

    /**
     * @brief Destructor, giảm biến đếm member.
     */
    ~Student();

    /// @return ID sinh viên.
    int getID() const ;

    /// @return Tên sinh viên.
    std::string getName() const ;

    /// @return Điểm sinh viên.
    int getPoint() const ;

    /// @brief Đặt ID cho sinh viên.
    void setID(int id) ;  

    /// @brief Đặt tên cho sinh viên.
    void setName(const std::string& n) ;

    /// @brief Đặt điểm cho sinh viên.
    void setPoint(int p) ;

    /**
     * @brief Cập nhật thông tin sinh viên khác.
     * @param st Sinh viên cần cập nhật.
     * @param n Tên mới.
     * @param p Điểm mới.
     */
    void update(Student& st, const std::string& n, int p) ;

    /**
     * @brief Nạp chồng toán tử == để so sánh với ID.
     * @param ID Mã số cần so sánh.
     * @return true nếu trùng ID.
     */
    bool operator==(int ID) const ;

    /**
     * @brief Toán tử << để in thông tin sinh viên.
     */
    friend std::ostream& operator<<(std::ostream& os, const Student& st) ;
};

//======================================================================
//  Lớp StudentList
//======================================================================

/**
 * @brief Lớp quản lý danh sách sinh viên bằng std::vector.
 */
class StudentList
{
private:
    std::vector<Student> list;  ///< Vector chứa danh sách sinh viên
public:
    /// @brief Thêm sinh viên vào danh sách.
    void add(const Student& st) ;

    /// @brief Truy cập phần tử theo chỉ số.
    Student& operator[](size_t index) ;

    /// @brief Truy cập phần tử theo chỉ số (const version).
    const Student& operator[](size_t index) const ;

    /// @brief Lấy toàn bộ danh sách (tham chiếu).
    std::vector<Student>& operator()() ;

    /// @brief Lấy toàn bộ danh sách (tham chiếu hằng).
    const std::vector<Student>& operator()() const ;

    /// @brief Toán tử << in danh sách sinh viên.
    friend std::ostream& operator<<(std::ostream& os, const StudentList& sl) ;
  
    /// @brief Tính điểm trung bình của tất cả sinh viên.
    float averge() const ;

    /// @brief Tìm sinh viên theo ID trong danh sách.
    bool findID(const std::vector<Student>& list, int id) ;

    /// @brief Hàm định dạng header khi in danh sách sinh viên.
    void formatHeader();

    /// @brief Hàm hiển thị hướng dẫn sử dụng.
    void Help();
};

#endif // STUDENT_H