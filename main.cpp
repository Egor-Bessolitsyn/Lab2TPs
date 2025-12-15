#include <iostream>
#include <fstream>
#include <sstream>
#include "Student.h"

using namespace std;

// Глобальные переменные
Student** students = nullptr;
int studentCount = 0;

// Прототипы функций
void showMenu();
void addStudent();
void removeStudent();
void editStudent();
void displayAllStudents();
void displayStudentsWithFailingGrades();
void sortStudentsByAverage();
void insertStudentAtPosition();
void saveToFile();
void loadFromFile();
void processTextFile();
void clearAllStudents();

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    cout << "=== Лабораторная работа №2. Вариант 3 ===" << endl;
    cout << "Система учёта студентов\n" << endl;

    try {
        while (true) {
            showMenu();
            cout << "\nВыберите действие: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nОшибка! Введите число.\n" << endl;
                continue;
            }

            try {
                switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    insertStudentAtPosition();
                    break;
                case 3:
                    editStudent();
                    break;
                case 4:
                    removeStudent();
                    break;
                case 5:
                    displayAllStudents();
                    break;
                case 6:
                    displayStudentsWithFailingGrades();
                    break;
                case 7:
                    sortStudentsByAverage();
                    break;
                case 8:
                    saveToFile();
                    break;
                case 9:
                    loadFromFile();
                    break;
                case 10:
                    processTextFile();
                    break;
                case 0:
                    cout << "\nЗавершение работы программы..." << endl;
                    clearAllStudents();
                    return 0;
                default:
                    cout << "\nНеверный выбор! Попробуйте снова.\n" << endl;
                }
            }
            catch (const exception& e) {
                cout << "\n[ИСКЛЮЧЕНИЕ] " << e.what() << "\n" << endl;
            }
        }
    }
    catch (...) {
        cout << "Критическая ошибка!" << endl;
        clearAllStudents();
        return 1;
    }

    return 0;
}

void showMenu() {
    setlocale(LC_ALL, "Russian");
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║           ГЛАВНОЕ МЕНЮ                 ║" << endl;
    cout << "╠════════════════════════════════════════╣" << endl;
    cout << "║ 1. Добавить студента                   ║" << endl;
    cout << "║ 2. Добавить студента на позицию        ║" << endl;
    cout << "║ 3. Редактировать студента              ║" << endl;
    cout << "║ 4. Удалить студента                    ║" << endl;
    cout << "║ 5. Показать всех студентов             ║" << endl;
    cout << "║ 6. Показать студентов с двойками       ║" << endl;
    cout << "║ 7. Сортировать по среднему баллу       ║" << endl;
    cout << "║ 8. Сохранить в файл                    ║" << endl;
    cout << "║ 9. Загрузить из файла                  ║" << endl;
    cout << "║ 10. Обработать текстовый файл          ║" << endl;
    cout << "║ 0. Выход                               ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
}

void addStudent() {
    setlocale(LC_ALL, "Russian");
    cout << "\n--- Добавление нового студента ---" << endl;

    Student* newStudent = new Student();

    try {
        cin >> *newStudent;

        Student** temp = new Student * [studentCount + 1];
        for (int i = 0; i < studentCount; i++) {
            temp[i] = students[i];
        }
        temp[studentCount] = newStudent;

        delete[] students;
        students = temp;
        studentCount++;

        cout << "\nСтудент успешно добавлен!" << endl;
    }
    catch (const exception& e) {
        delete newStudent;
        throw;
    }
}

void insertStudentAtPosition() {
    setlocale(LC_ALL, "Russian");
    if (studentCount == 0) {
        cout << "\nСписок пуст. Добавьте первого студента через пункт 1." << endl;
        return;
    }

    int position;
    cout << "\nВведите позицию для вставки (1-" << (studentCount + 1) << "): ";
    cin >> position;

    if (position < 1 || position > studentCount + 1) {
        throw out_of_range("Недопустимая позиция!");
    }

    Student* newStudent = new Student();

    try {
        cin >> *newStudent;

        Student** temp = new Student * [studentCount + 1];

        for (int i = 0; i < position - 1; i++) {
            temp[i] = students[i];
        }

        temp[position - 1] = newStudent;

        for (int i = position - 1; i < studentCount; i++) {
            temp[i + 1] = students[i];
        }

        delete[] students;
        students = temp;
        studentCount++;

        cout << "\nСтудент успешно добавлен на позицию " << position << "!" << endl;
    }
    catch (const exception& e) {
        delete newStudent;
        throw;
    }
}

void editStudent() {
    setlocale(LC_ALL, "Russian");
    if (studentCount == 0) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }

    displayAllStudents();

    int index;
    cout << "\nВведите номер студента для редактирования (1-" << studentCount << "): ";
    cin >> index;

    if (index < 1 || index > studentCount) {
        throw out_of_range("Недопустимый номер студента!");
    }

    cout << "\n--- Редактирование студента ---" << endl;
    cin >> *students[index - 1];

    cout << "\nДанные студента успешно обновлены!" << endl;
}

void removeStudent() {
    setlocale(LC_ALL, "Russian");
    if (studentCount == 0) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }

    displayAllStudents();

    int index;
    cout << "\nВведите номер студента для удаления (1-" << studentCount << "): ";
    cin >> index;

    if (index < 1 || index > studentCount) {
        throw out_of_range("Недопустимый номер студента!");
    }

    delete students[index - 1];

    Student** temp = new Student * [studentCount - 1];

    for (int i = 0; i < index - 1; i++) {
        temp[i] = students[i];
    }

    for (int i = index; i < studentCount; i++) {
        temp[i - 1] = students[i];
    }

    delete[] students;
    students = temp;
    studentCount--;

    cout << "\nСтудент успешно удалён!" << endl;
}

void displayAllStudents() {
    setlocale(LC_ALL, "Russian");
    if (studentCount == 0) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }

    cout << "\n=== Список всех студентов ===" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << "\n[" << (i + 1) << "] ";
        cout << *students[i] << endl;
        cout << "-----------------------------------" << endl;
    }
}

void displayStudentsWithFailingGrades() {
    setlocale(LC_ALL, "Russian");
    if (studentCount == 0) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }

    cout << "\n=== Студенты с хотя бы одной оценкой 2 ===" << endl;

    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i]->hasFailingGrade()) {
            cout << "\nФИО: " << students[i]->getFullName() << endl;
            cout << "Группа: " << students[i]->getGroupNumber() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "\nСтуденты с двойками отсутствуют." << endl;
    }
}

void sortStudentsByAverage() {
    setlocale(LC_ALL, "Russian");
    if (studentCount == 0) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }

    // Сортировка пузырьком
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j + 1]->getAverageGrade() < students[j]->getAverageGrade()) {
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    cout << "\nСтуденты отсортированы по возрастанию среднего балла!" << endl;
    displayAllStudents();
}

void saveToFile() {
    setlocale(LC_ALL, "Russian");
    char filename[256];
    cout << "\nВведите имя файла для сохранения: ";
    cin.ignore();
    cin.getline(filename, 256);

    ofstream file(filename);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для записи!");
    }

    file << studentCount << "\n";

    for (int i = 0; i < studentCount; i++) {
        file << students[i]->getFullName() << "\n";
        file << students[i]->getGroupNumber() << "\n";
        file << students[i]->getSubjectCount() << "\n";

        for (int j = 0; j < students[i]->getSubjectCount(); j++) {
            file << students[i]->getSubject(j) << "\n";
            file << students[i]->getGrade(j) << "\n";
        }
    }

    file.close();
    cout << "\nДанные успешно сохранены в файл " << filename << "!" << endl;
}

void loadFromFile() {
    setlocale(LC_ALL, "Russian");
    char filename[256];
    cout << "\nВведите имя файла для загрузки: ";
    cin.ignore();
    cin.getline(filename, 256);

    ifstream file(filename);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для чтения!");
    }

    clearAllStudents();

    file >> studentCount;
    file.ignore();

    students = new Student * [studentCount];

    for (int i = 0; i < studentCount; i++) {
        char buffer[256];

        file.getline(buffer, 256);
        int group;
        file >> group;
        int subjCount;
        file >> subjCount;
        file.ignore();

        students[i] = new Student(buffer, group, subjCount);

        for (int j = 0; j < subjCount; j++) {
            file.getline(buffer, 256);
            int grade;
            file >> grade;
            file.ignore();

            students[i]->setSubjectAndGrade(j, buffer, grade);
        }
    }

    file.close();
    cout << "\nДанные успешно загружены из файла " << filename << "!" << endl;
    cout << "Загружено студентов: " << studentCount << endl;
}

void processTextFile() {
    setlocale(LC_ALL, "Russian");
    char filename[256];
    cout << "\nВведите имя текстового файла: ";
    cin.ignore();
    cin.getline(filename, 256);

    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("Не удалось открыть файл для чтения!");
    }

    cout << "\n=== Строки, содержащие двузначные числа ===" << endl;

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string word;
        bool hasTwoDigitNumber = false;

        while (ss >> word) {
            // Проверка на двузначное число
            if (word.length() >= 2) {
                bool isNumber = true;
                int digitCount = 0;

                for (size_t i = 0; i < word.length(); i++) {
                    if (isdigit(word[i])) {
                        digitCount++;
                    }
                    else if (word[i] != ',' && word[i] != '.' &&
                        word[i] != '!' && word[i] != '?' &&
                        word[i] != ';' && word[i] != ':') {
                        isNumber = false;
                        break;
                    }
                }

                if (digitCount == 2) {
                    hasTwoDigitNumber = true;
                    break;
                }
            }
        }

        if (hasTwoDigitNumber) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Строки с двузначными числами не найдены." << endl;
    }

    inFile.close();
}

void clearAllStudents() {
    for (int i = 0; i < studentCount; i++) {
        delete students[i];
    }
    delete[] students;
    students = nullptr;
    studentCount = 0;
}