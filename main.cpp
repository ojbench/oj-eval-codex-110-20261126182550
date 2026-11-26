#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date
{
private:
    int _year;
    int _month;
    int _day;

    static bool isLeapYear(int year)
    {
        return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    }

    static int daysInMonth(int year, int month)
    {
        return month_days[month] + (month == 2 && isLeapYear(year));
    }

    long long ordinal() const
    {
        const long long years = _year - 1LL;
        long long days = 365 * years + years / 4 - years / 100 + years / 400;
        for (int month = 1; month < _month; ++month)
            days += daysInMonth(_year, month);
        return days + _day;
    }

    Date shifted(long long days) const
    {
        Date result = *this;
        long long day = result._day + days;
        // Normalize across whole months, including changes of year.
        while (day > daysInMonth(result._year, result._month))
        {
            day -= daysInMonth(result._year, result._month);
            if (++result._month == 13)
            {
                result._month = 1;
                ++result._year;
            }
        }
        while (day < 1)
        {
            if (--result._month == 0)
            {
                result._month = 12;
                --result._year;
            }
            day += daysInMonth(result._year, result._month);
        }
        result._day = static_cast<int>(day);
        return result;
    }

public:
    Date(int year = 1900, int month = 1, int day = 1)
        : _year(1900), _month(1), _day(1)
    {
        if (year >= 1 && month >= 1 && month <= 12 &&
            day >= 1 && day <= daysInMonth(year, month))
        {
            _year = year;
            _month = month;
            _day = day;
        }
    }

    Date operator+(int days) const { return shifted(days); }
    Date operator-(int days) const { return shifted(-static_cast<long long>(days)); }

    Date& operator++()
    {
        *this = shifted(1);
        return *this;
    }

    Date operator++(int)
    {
        Date previous = *this;
        ++*this;
        return previous;
    }

    Date& operator--()
    {
        *this = shifted(-1);
        return *this;
    }

    Date operator--(int)
    {
        Date previous = *this;
        --*this;
        return previous;
    }

    bool operator<(const Date& other) const
    {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    long long operator-(const Date& other) const
    {
        const long long difference = ordinal() - other.ordinal();
        return difference < 0 ? -difference : difference;
    }

    friend ostream& operator<<(ostream& stream, const Date& date)
    {
        return stream << date._year << '-' << date._month << '-' << date._day;
    }
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}
int main()
{
	Test();
	return 0;
}

