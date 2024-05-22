#include <iostream>
#include <stdexcept>
#include <string>

class InvalidDateException : public std::out_of_range {
public:
    InvalidDateException(int d, int m, int y)
            : std::out_of_range("Invalid date"), day(d), month(m), year(y) {}

    void printDetails() const {
        std::cout << "Invalid date: " << day << "/" << month << "/" << year << std::endl;
    }

private:
    int day, month, year;
};

class Date {
public:
    Date(int d, int m, int y) {
        if (!isValid(d, m, y)) {
            throw InvalidDateException(d, m, y);
        }
        day = d;
        month = m;
        year = y;
    }

    void printDate() const {
        std::cout << "Date: " << day << "/" << month << "/" << year << std::endl;
    }

private:
    int day, month, year;

    bool isValid(int d, int m, int y) const {
        if (y < 1 || m < 1 || m > 12 || d < 1) return false; // Проверка допустимости месяца и года
        if (m == 2) { // Проверка для февраля
            bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); // Определение високосного года
            return d <= (isLeap ? 29 : 28); // В феврале 29 дней в високосный год и 28 в невисокосный
        }
        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // Количество дней в месяцах
        return d <= daysInMonth[m - 1]; // Проверка допустимости дня для данного месяца
    }
};

int main() {
    try {
        Date validDate(15, 5, 2023);
        validDate.printDate();

        Date invalidDate(31, 2, 2023); // Это вызовет исключение
        invalidDate.printDate();
    } catch (const InvalidDateException& ex) {
        std::cout << "Caught an exception: " << ex.what() << std::endl;
        ex.printDetails();
    }

    return 0;
}