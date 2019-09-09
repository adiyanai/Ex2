#ifndef Ex2_WRITER_H
#define Ex2_WRITER_H

#include "MyEmployee.h"
#include "MyCustomer.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyReservation.h"
#include "Reader.h"
class Writer {

public:
    void writeEmployee(MyEmployee* employee);
    void writeCustomer(MyCustomer* customer);
    void writePlane(MyPlane* plane);
    void writeFlight(MyFlight* flight);
    void writeReservation(MyReservation* reservation);
    void writeEmployeeFlight(int num, list<string> idEmployee, string idFlight);

};
#endif //Ex2_WRITER_H