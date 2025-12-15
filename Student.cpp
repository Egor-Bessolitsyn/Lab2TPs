#include "Student.h"
#include <iostream>
#include <cstring>
#include <windows.h>


// Конструктор по умолчанию
Student::Student() : fullName(nullptr), groupNumber(0), subjects(nullptr), grades(nullptr), subjectCount(0) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "[Конструктор] Создан пустой объект Student" << std::endl;
}

// Конструктор с параметрами
Student::Student(const char* name, int group, int subjCount)
    : groupNumber(group), subjectCount(subjCount) {
    fullName = new char[strlen(name) + 1];
    #pragma warning(suppress : 4996)
    strcpy(fullName, name);

    subjects = new char* [subjectCount];
    grades = new int[subjectCount];

    for (int i = 0; i < subjectCount; i++) {
        subjects[i] = nullptr;
        grades[i] = 0;
    }

    std::cout << "[Конструктор с параметрами] Создан Student: " << name << std::endl;
}

// Конструктор копирования
Student::Student(const Student& other)
    : groupNumber(other.groupNumber), subjectCount(other.subjectCount) {
    setlocale(LC_ALL, "Russian");
    if (other.fullName) {
        fullName = new char[strlen(other.fullName) + 1];
        #pragma warning(suppress : 4996)
        strcpy(fullName, other.fullName);
    }
    else {
        fullName = nullptr;
    }

    if (other.subjectCount > 0) {
        subjects = new char* [subjectCount];
        grades = new int[subjectCount];

        for (int i = 0; i < subjectCount; i++) {
            if (other.subjects[i]) {
                subjects[i] = new char[strlen(other.subjects[i]) + 1];
                #pragma warning(suppress : 4996)
                strcpy(subjects[i], other.subjects[i]);
            }
            else {
                subjects[i] = nullptr;
            }
            grades[i] = other.grades[i];
        }
    }
    else {
        subjects = nullptr;
        grades = nullptr;
    }

    std::cout << "[Конструктор копирования] Скопирован Student: "
        << (fullName ? fullName : "без имени") << std::endl;
}

// Деструктор
Student::~Student() {
    setlocale(LC_ALL, "Russian");
    std::cout << "[Деструктор] Удаляется Student: "
        << (fullName ? fullName : "без имени") << std::endl;

    delete[] fullName;

    if (subjects) {
        for (int i = 0; i < subjectCount; i++) {
            delete[] subjects[i];
        }
        delete[] subjects;
    }

    delete[] grades;
}

// Методы get
const char* Student::getFullName() const {
    return fullName ? fullName : "";
}

int Student::getGroupNumber() const {
    return groupNumber;
}

int Student::getSubjectCount() const {
    return subjectCount;
}

const char* Student::getSubject(int index) const {
    if (index >= 0 && index < subjectCount && subjects[index]) {
        return subjects[index];
    }
    return "";
}

int Student::getGrade(int index) const {
    if (index >= 0 && index < subjectCount) {
        return grades[index];
    }
    return 0;
}

// Методы set
void Student::setFullName(const char* name) {
    delete[] fullName;
    fullName = new char[strlen(name) + 1];
    #pragma warning(suppress : 4996)
    strcpy(fullName, name);
}

void Student::setGroupNumber(int group) {
    if (group <= 0) {
        throw std::invalid_argument("Номер группы должен быть положительным числом!");
    }
    groupNumber = group;
}

void Student::setSubjectAndGrade(int index, const char* subject, int grade) {
    if (index < 0 || index >= subjectCount) {
        throw std::out_of_range("Индекс предмета вне допустимого диапазона!");
    }

    if (grade < 2 || grade > 5) {
        throw std::invalid_argument("Оценка должна быть от 2 до 5!");
    }

    delete[] subjects[index];
    subjects[index] = new char[strlen(subject) + 1];
    #pragma warning(suppress : 4996)
    strcpy(subjects[index], subject);
    grades[index] = grade;
}

// Вычисление среднего балла
double Student::getAverageGrade() const {
    if (subjectCount == 0) return 0.0;

    int sum = 0;
    for (int i = 0; i < subjectCount; i++) {
        sum += grades[i];
    }
    return static_cast<double>(sum) / subjectCount;
}

// Проверка наличия двоек
bool Student::hasFailingGrade() const {
    for (int i = 0; i < subjectCount; i++) {
        if (grades[i] == 2) {
            return true;
        }
    }
    return false;
}

// Оператор присваивания
Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;

    // Освобождение старой памяти
    delete[] fullName;
    if (subjects) {
        for (int i = 0; i < subjectCount; i++) {
            delete[] subjects[i];
        }
        delete[] subjects;
    }
    delete[] grades;

    // Копирование
    groupNumber = other.groupNumber;
    subjectCount = other.subjectCount;

    if (other.fullName) {
        fullName = new char[strlen(other.fullName) + 1];
        #pragma warning(suppress : 4996)
        strcpy(fullName, other.fullName);
    }
    else {
        fullName = nullptr;
    }

    if (other.subjectCount > 0) {
        subjects = new char* [subjectCount];
        grades = new int[subjectCount];

        for (int i = 0; i < subjectCount; i++) {
            if (other.subjects[i]) {
                subjects[i] = new char[strlen(other.subjects[i]) + 1];
                #pragma warning(suppress : 4996)
                strcpy(subjects[i], other.subjects[i]);
            }
            else {
                subjects[i] = nullptr;
            }
            grades[i] = other.grades[i];
        }
    }
    else {
        subjects = nullptr;
        grades = nullptr;
    }

    return *this;
}

// Оператор сравнения для сортировки
bool Student::operator<(const Student& other) const {
    return getAverageGrade() < other.getAverageGrade();
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, const Student& student) {
    out << "ФИО: " << student.getFullName() << "\n";
    out << "Группа: " << student.getGroupNumber() << "\n";
    out << "Предметы и оценки:\n";
    for (int i = 0; i < student.subjectCount; i++) {
        out << "  " << student.getSubject(i) << ": " << student.getGrade(i) << "\n";
    }
    out << "Средний балл: " << student.getAverageGrade();
    return out;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& in, Student& student) {
    char buffer[256];

    std::cout << "Введите ФИО: ";
    in.ignore();
    in.getline(buffer, 256);
    student.setFullName(buffer);

    int group;
    std::cout << "Введите номер группы: ";
    in >> group;
    student.setGroupNumber(group);

    std::cout << "Введите количество предметов: ";
    int count;
    in >> count;

    if (count <= 0) {
        throw std::invalid_argument("Количество предметов должно быть положительным!");
    }

    // Пересоздание массивов
    if (student.subjects) {
        for (int i = 0; i < student.subjectCount; i++) {
            delete[] student.subjects[i];
        }
        delete[] student.subjects;
    }
    delete[] student.grades;

    student.subjectCount = count;
    student.subjects = new char* [count];
    student.grades = new int[count];

    for (int i = 0; i < count; i++) {
        std::cout << "Предмет " << (i + 1) << ": ";
        in.ignore();
        in.getline(buffer, 256);
        student.subjects[i] = new char[strlen(buffer) + 1];
        #pragma warning(suppress : 4996)
        strcpy(student.subjects[i], buffer);

        int grade;
        std::cout << "Оценка по предмету " << buffer << " (2-5): ";
        in >> grade;

        if (grade < 2 || grade > 5) {
            throw std::invalid_argument("Оценка должна быть от 2 до 5!");
        }

        student.grades[i] = grade;
    }

    return in;
}