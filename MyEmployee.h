#ifndef Ex2_MYEMPLOYEE_H
#define Ex2_MYEMPLOYEE_H

#include "interface.h"
class Reader;

class MyEmployee: public Employee {

    string id;
    int seniority;
    int birthYear;
    string employerId;
    Jobs title;
    Reader* r;

public:
    MyEmployee(int seniority, int birthYear, string employer_id, Jobs title, string id,
               Reader* reader);
    int getSeniority();
    int getBirthYear();
    Employee* getEmployer();
    Jobs getTitle();
    const string &getEmployerId() const;
    string getID();
};


#endif //Ex2_MYEMPLOYEE_H