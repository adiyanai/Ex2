#ifndef Ex2_MYCUSTOMER_H
#define Ex2_MYCUSTOMER_H
#include "interface.h"
class Reader;

class MyCustomer : public Customer {
    string id;
    string fullName;
    int priority;
    Reader* r;
public:
    MyCustomer(string fullName, int priority, string id, Reader* reader);
    string getFullName();
    int getPriority();
    list<Reservation*> getReservations();
    string getID();
};


#endif //Ex2_MYCUSTOMER_H