#ifndef Ex2_MYIMPLEMENTATION_H
#define Ex2_MYIMPLEMENTATION_H
#include "interface.h"
#include "Reader.h"
#include "Writer.h"
#include "ValidCheck.h"

class MyImplementation : public Ex2 {

    map<string, MyEmployee*> employees;
    map<string, MyCustomer*> customers;
    map<string, MyPlane*> planes;
    map<string, MyFlight*> flights;
    map<string, MyReservation*> reservations;
    Reader* reader;

    /**
     * check the correction of the information avout the new employee
     * @param id - the id of the employee's employer
     * @param birth_year - the birth year of the employee
     * @return true if the information about the new employee is ok
     */
    bool correctEmployee (string employer_id, int birth_year);

public:

    MyImplementation() {
        this->reader = new Reader;
    }
    /**
     * if the employer_id is "0" it means that the employee doesn't has an employer
     * @param seniority
     * @param birth_year
     * @param employer_id
     * @param title
     * @return
     */
    Employee* addEmployee(int seniority, int birth_year, string employer_id, Jobs title);

    /**
     * get Employee from the employee's table
     * @param id
     * @return
     */
    Employee* getEmployee(string id);

    /**
     * create new plane, add him to the plane's table and return him
     * @param model_number - the model number of the new plane
     * @param crew_needed - the crew that this plane needed
     * @param max_passangers - the max passengers that the plan could carry
     * @return a new plane
     */
    Plane* addPlane(int model_number, map<Jobs, int> crew_needed,
                    map<Classes, int> max_passangers);

    /**
     * get plane from the plane's table
     * @param id - the id of the plane we want
     * @return a pointer to the plane with the id we want
     */
    Plane* getPlane(string id);

    Flight* addFlight(int model_number, Date date, string source, string destination);

    Flight* getFlight(string id);

    Customer* addCustomer(string full_name, int priority);

    Customer* getCustomer(string id);

    Reservation* addResevation(string customerId, string flightId,
                               Classes cls, int max_baggage);

    Reservation* getReservation(string id);

    void exit();

    ~MyImplementation();

};
#endif //Ex2_MYIMPLEMENTATION_H