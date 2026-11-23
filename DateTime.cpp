#include "DateTime.h"
#include <ostream>
#include <stdexcept>
using namespace std;

DateTime::DateTime() : DateTime("2000-01-01")
{
}

DateTime::DateTime(const string &date)
{
    if (date.length() != 10)
    {
        throw invalid_argument("Zla dlugosc daty, oczekiwano formatu rrrr-mm-dd");
    }
    if (date[4] != '-' || date[7] != '-')
    {
        throw invalid_argument("Brak myslnikow w odpowiednich miejscach");
    }
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
        {
            throw invalid_argument("Data zawiera niedozwolone znaki");
        }
    }

    year = stoi(date.substr(0, 4));
    month = stoi(date.substr(5, 2));
    day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12)
    {
        throw out_of_range("Miesiac musi byc od 1 do 12");
    }

    int dniWMiesiacu[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        dniWMiesiacu[1] = 29;
    }
    if (day < 1 || day > dniWMiesiacu[month - 1])
    {
        throw out_of_range("Zly dzien dla tego miesiaca");
    }
    this->date = date;
}

string DateTime::getDate() const
{
    return date;
}

int DateTime::getDay() const
{
    return day;
}

int DateTime::getMonth() const
{
    return month;
}

int DateTime::getYear() const
{
    return year;
}

bool DateTime::operator<(const DateTime &other) const
{
    return date < other.date;
}

bool DateTime::operator==(const DateTime &other) const
{
    return date == other.date;
}

ostream &operator<<(ostream &output, const DateTime &date)
{
    output << date.getDate();
    return output;
}