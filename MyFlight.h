#ifndef Ex2_MYFLIGHT_H
#define Ex2_MYFLIGHT_H
#include "interface.h"
class Reader;

class MyFlight : public Flight{
    string id;
    int modelNumber;
    Date date;
    string source;
    string destination;
    Reader* r;
public:
    MyFlight(int modelNumber, Date date, string source, string destination, string id,
             Reader* reader);
    int getModelNumber();
    list<Reservation*> getReservations();
    list<Employee*> getAssignedCrew();
    Date getDate();
    string getSource();
    string getDestination();
    string getID();
};


#endif //Ex2_MYFLIGHT_H