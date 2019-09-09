#ifndef Ex2_READER_H
#define Ex2_READER_H
#include <string>
#include <vector>
#include "interface.h"
#include "MyEmployee.h"
#include "MyCustomer.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyReservation.h"
using namespace std;
class Reader {
    map<string, MyEmployee*> employees;
    map<string, MyCustomer*> customers;
    map<string, MyPlane*> planes;
    map<string, MyFlight*> flights;
    map<string, MyReservation*> reservations;
public:
    vector<string> split(string line, char divide);
    string getNewID(string file);
    string findLineById(string file, string id, int place);
    vector<string> findLinesById(string file, string id, int place);
    MyEmployee* getEmployee(string id);
    MyCustomer* getCustomer(string id);
    MyPlane* getPlane(string id);
    MyFlight* getFlight(string id);
    MyReservation* getReservation(string id);
    list<Reservation*> getCustomerReservations(string id);
    list<Reservation*> getFlightReservations(string id);
    list<Employee*> getFlightEmployees(string id);
    ~Reader();
};



#endif //Ex2_READER_H