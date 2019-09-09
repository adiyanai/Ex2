#ifndef Ex2_MYRESERVATION_H
#define Ex2_MYRESERVATION_H
#include "interface.h"
class Reader;

class MyReservation : public Reservation {

    string id;
    string customerId;
    string flightId;
    Classes cls;
    int maxBaggage;
    Reader* r;

public:
    MyReservation(string customerId, string flightId, Classes cls, int maxBaggage, string id,
                  Reader* reader);
    Customer* getCustomer();
    Flight* getFlight();
    Classes getClass();
    int getMaxBaggage();
    const string &getCustomerId() const;
    const string &getFlightId() const;
    string getID();
};


#endif //Ex2_MYRESERVATION_H