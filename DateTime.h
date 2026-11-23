#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <iosfwd>
using namespace std;

class DateTime
{
private:
    string date;
    int day;
    int month;
    int year;

public:
    DateTime();
    explicit DateTime(const string& date);
    string getDate() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    bool operator<(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
};

ostream& operator<<(ostream& output, const DateTime& date);

#endif