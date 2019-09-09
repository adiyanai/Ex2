#ifndef Ex2_VALIDCHECK_H
#define Ex2_VALIDCHECK_H
#include <string>
#include <vector>
#include "interface.h"
#include "MyEmployee.h"
#include "MyCustomer.h"
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyReservation.h"
#include "Reader.h"
using namespace std;

class ValidCheck {

public:
    bool customerExist(string id, Reader* r);
    bool flightExist(string id, Reader* r);
    bool planeAvailable(string id, Date date, Reader* r);
    bool crewNeededAvailable(string modelNumber, Date date, string idFlight, Reader* r);
    bool flightAvailable(string id, Classes cls, Reader* r);
};


#endif //Ex2_VALIDCHECK_H