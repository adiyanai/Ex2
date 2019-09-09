#include "interface.h"
using namespace std;

/**
 * constructor.
 * check if the date is valid
 * @param date - a string of date
 */
Date:: Date (string date) {
    string year, month, day;

    if (date.length() != 10) {
        __throw_invalid_argument("Not in the right length");
    }

    // divide the date to year, month, day
    year = date.substr(0,4);
    month = date.substr(5,2);
    day = date.substr(8,2);

    // check validity of year
    for (int i = 0; i < 4; i++) {
        if (year.at(i) < 48 || year.at(i) > 57) {
            __throw_invalid_argument("not a number");
        }
    }

    // check validity of month
    for (int i = 0; i < 2; i++) {
        if (month.at(i) < 48 || month.at(i) > 57) {
            __throw_invalid_argument("not a number");
        }
    }

    // check validity of day
    for (int i = 0; i < 2; i++) {
        if (day.at(i) < 48 || day.at(i) > 57) {
            __throw_invalid_argument("not a number");
        }
    }

    if (stoi(year) < 1 || stoi(year) > 9999 || stoi(month) < 1 || stoi(month) > 12
        || stoi(day) < 1 || stoi(day) > 31) {
        __throw_invalid_argument("not in the range");
    }
    this->date = date;
}

/**
 * check if this date is smaller than the 'd' date
 * @param d - a date
 * @return - true if this date smaller than 'd' date, else return false
 */
bool Date:: operator<(const Date& d) const {
    string year1, year2, month1, month2, day1, day2;
    // divide the dates to year, month, day
    year1 = this->date.substr(0,4);
    month1 = this->date.substr(5,2);
    day1 = this->date.substr(8,2);
    year2 = d.getDate().substr(0,4);
    month2 = d.getDate().substr(5,2);
    day2 = d.getDate().substr(8,2);

    if (year1 < year2) {
        return true;
    } else if (year1 == year2) {
        if (month1 < month2) {
            return true;
        } else if (month1 == month2) {
            if (day1 < day2) {
                return true;
            }
        }
    }
    return false;
}

/**
 * check if this date is bigger than the 'd' date
 * @param d - a date
 * @return - true if this date bigger than 'd' date, else return false
 */
bool Date:: operator>(const Date& d) const {
    string year1, year2, month1, month2, day1, day2;
    // divide the dates to year, month, day
    year1 = this->date.substr(0,4);
    month1 = this->date.substr(5,2);
    day1 = this->date.substr(8,2);
    year2 = d.getDate().substr(0,4);
    month2 = d.getDate().substr(5,2);
    day2 = d.getDate().substr(8,2);

    if (year1 > year2) {
        return true;
    } else if (year1 == year2) {
        if (month1 > month2) {
            return true;
        } else if (month1 == month2) {
            if (day1 > day2) {
                return true;
            }
        }
    }
    return false;
}

/**
 * check if this date and 'd' date are the same
 * @param d - a date
 * @return - true if this date and 'd' date are the same, else return false
 */
bool Date:: operator==(const Date& d) const {
    return !(*this > d) && !(*this < d);
}