#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <vector>

class Student
{
private:
    static int member;
    int ID;
    std::string name;
    int point;
public:
    // Constructor có kiểm tra dữ liệu
    Student(const std::string& n, int p) ;
    ~Student();

    int getID() const ;
    std::string getName() const ;
    int getPoint() const ;

    void setName(const std::string& n) ;
    void setPoint(int p) ;

    void update(Student& st, const std::string& n, int p) ;

    // Nạp chồng toán tử == so sánh theo ID
    bool operator==(int ID) const ;

    //in thong tin sinh vien
    friend std::ostream& operator<<(std::ostream& os, const Student& st) ;
};

//----------------------------------------------------------------------
class StudentList
{
private:
    std::vector<Student> list;
public:
    void add(const Student& st) ;


    Student& operator[](size_t index) ;

    const Student& operator[](size_t index) const ;

    const std::vector<Student>& operator()() const;

    // in danh sach sinh vien
    friend std::ostream& operator<<(std::ostream& os, const StudentList& sl) ;

    // Tinh diem trung binh
    float averge() const ;
};

bool findStudentById(const std::vector<Student>& list, int id);
void formatHeader();

#endif // STUDENT_H