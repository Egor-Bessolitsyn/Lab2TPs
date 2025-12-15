#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>


class Student {
private:
    char* fullName;
    int groupNumber;
    char** subjects;
    int* grades;
    int subjectCount;

public:
    // Конструкторы
    Student();
    Student(const char* name, int group, int subjCount);
    Student(const Student& other);

    // Деструктор
    ~Student();

    // Методы доступа (get)
    const char* getFullName() const;
    int getGroupNumber() const;
    int getSubjectCount() const;
    const char* getSubject(int index) const;
    int getGrade(int index) const;

    // Методы установки (set)
    void setFullName(const char* name);
    void setGroupNumber(int group);
    void setSubjectAndGrade(int index, const char* subject, int grade);

    // Вычисление среднего балла
    double getAverageGrade() const;

    // Проверка наличия двоек
    bool hasFailingGrade() const;

    // Перегрузка операторов
    friend std::ostream& operator<<(std::ostream& out, const Student& student);
    friend std::istream& operator>>(std::istream& in, Student& student);

    // Оператор присваивания
    Student& operator=(const Student& other);

    // Сравнение для сортировки
    bool operator<(const Student& other) const;
};

#endif