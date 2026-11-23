#ifndef DATETIME_H
#define DATETIME_H

#include <string>
using namespace std;

struct DateTime
{
public:
    string date;
    int day;
    int month;
    int year;
    DateTime(string date);
};

#endif