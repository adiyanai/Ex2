#include "MyImplementation.h"
#define EMPLOYEES_FILE "employees.txt"
#define CUSTOMERS_FILE "customers.txt"
#define PLANES_FILE "planes.txt"
#define FLIGHTS_FILE "flights.txt"
#define RESERVATIONS_FILE "reservation.txt"

/**
 * check the correction of the information about the new employee
 * @param id - the id of the employee's employer
 * @param birth_year - the birth year of the employee
 * @return true if the information about the new employee is ok
 */
bool MyImplementation:: correctEmployee (string employer_id, int birth_year) {

    // check that the id of the employer consists only numbers
    for (int i = 0; i < employer_id.length(); i++) {
        if (employer_id[i] < 48 || employer_id[i] > 57) {
            __throw_invalid_argument("not a number");
        }
    }
    // check that the birth year is bigger than 0
    if (birth_year < 0) {
        __throw_invalid_argument("There is no such a year");
    }

    return true;
}


/**
 * the function add new employee to the employees's table and return the new employee.
 * if the employer_id is "0" it means that the employee doesn't has an employer
 * @param seniority - the seniority of the employee
 * @param birth_year - the birth year of the employee
 * @param employer_id - the id of the employer of the employee
 * @param title - the title job of the employee
 * @return - the new employee
 */
Employee* MyImplementation:: addEmployee(int seniority, int birth_year, string employer_id,
                                         Jobs title) {
    Writer w;
    // create id to the new employee
    string id = reader->getNewID(EMPLOYEES_FILE);

    // if the id of the employer is an empty string
    if (employer_id == "") {
        employer_id = "0";
    }

    // if everything about the new employee's information is ok
    if (correctEmployee(employer_id, birth_year)) {
        /*
         * if the id of the employer is bigger than the new employee,
         * it means that there is no employer with this id so we put 0
         * to represent that this employee doesn't has an employer
         */
        if (stoi(employer_id) >= stoi(id)) {
            employer_id = "0";
        }
    }
    // create new employee
    MyEmployee *newEmp = new MyEmployee(seniority, birth_year, employer_id, title, id,
                                        this->reader);

    // add the new employee to the employees's map
    if (newEmp != nullptr) {
        this->employees.insert(pair<string, MyEmployee*>(id, newEmp));
    }

    // write the new employee on the table
    w.writeEmployee(newEmp);
    return newEmp;
}

/**
 * get Employee from the employee's table (or from the employees's table)
 * @param id - the id of the employee
 * @return - the employee from the employee's table with the 'id' that the function get
 */
Employee* MyImplementation:: getEmployee(string id) {
    MyEmployee *employee;
    // if the employee exist in the employee's map
    if (this->employees.find(id) != this->employees.end()) {
        // get the employee from the employee's map
        employee = this->employees.find(id)->second;
    } else {
        // get the employee from the employee's table
        employee = reader->getEmployee(id);
    }
    return employee;
}

/**
 * create new plane, add him to the plane's table and return him
 * @param model_number - the model number of the new plane
 * @param crew_needed - the crew that this plane needed
 * @param max_passangers - the max passengers that the plan could carry
 * @return a new plane
 */
Plane* MyImplementation:: addPlane(int model_number, map<Jobs, int> crew_needed,
                                   map<Classes, int> max_passangers) {
    Writer w;
    // if the jobs map not full, fill it
    for (int i = 0; i <= OTHER; ++i) {
        if (!crew_needed.count((Jobs)i)) {
            crew_needed.insert(pair<Jobs,int>((Jobs)i, 0));
        }
    }
    //if the classes map not full, fil it
    for (int i = 0; i <= SECOND_CLASS; ++i) {
        if (!max_passangers.count((Classes)i)) {
            max_passangers.insert(pair<Classes ,int>((Classes)i, 0));
        }
    }
    // create id to the new plane
    string id = reader->getNewID(PLANES_FILE);
    // create new plane
    MyPlane *newPlane = new MyPlane(model_number, crew_needed, max_passangers,id);
    // add the new plane to the planes's table
    if (newPlane != nullptr) {
        this->planes.insert(pair<string, MyPlane*>(id, newPlane));
    }
    // write the new plane on the plane's table
    w.writePlane(newPlane);
    return newPlane;
}

/**
 * get plane from the plane's table (or from the planes's map)
 * @param id - the id of the plane we want
 * @return a pointer to the plane with the id we want
 */
Plane* MyImplementation:: getPlane(string id){
    MyPlane *plane;
    // if the plane exist in the planes's map
    if (this->planes.find(id) != this->planes.end()) {
        // get the plane from the planes's map
        plane = this->planes.find(id)->second;
    } else {
        // get the plane from the planes's table
        plane = reader->getPlane(id);
    }
    return plane;
}

/**
 * create new flight, add him to the flight's table and return him
 * @param model_number - the model of the plane that the flight use
 * @param date - the date of the flight
 * @param source - the source of the flight
 * @param destination - the destination of the flight
 * @return - new flight
 */
Flight* MyImplementation:: addFlight(int model_number, Date date, string source, string
destination){
    Writer w;
    ValidCheck v;
    // create id to the new flight
    string id = reader->getNewID(FLIGHTS_FILE);

    // check if there is plane with this model number that available
    if (!v.planeAvailable(to_string(model_number), date, this->reader)) {
        __throw_invalid_argument("There is no plane with this model number that is available");
    }
    // check if there is crew that is available
    if (!v.crewNeededAvailable(to_string(model_number), date, id, this->reader)) {
        __throw_invalid_argument("There is no crew that is available");
    }

    // create new flight
    MyFlight *newFlight = new MyFlight(model_number, date, source, destination, id,
                                       this->reader);
    // add the new flight to the flights's map
    if (newFlight != nullptr) {
        this->flights.insert(pair<string, MyFlight*>(id, newFlight));
    }
    // write the new plane on the plane's table
    w.writeFlight(newFlight);
    return newFlight;
}

/**
 * get flight from the flight's table (or from the flights's map)
 * @param id - the id of the flight we want
 * @return the flight with the 'id' the function get
 */
Flight* MyImplementation:: getFlight(string id){
    MyFlight *flight;
    // if the flight exist in the flights's map
    if (this->flights.find(id) != this->flights.end()) {
        // get the flight from the flights's map
        flight = this->flights.find(id)->second;
    } else {
        // get the flight from the flight's table
        flight = reader->getFlight(id);
    }
    return flight;
}

/**
 * create new customer, add him to the customer's table and return him
 * @param full_name - the full name of the customer
 * @param priority - the priority of the customer
 * @return - a new customer
 */
Customer* MyImplementation:: addCustomer(string full_name, int priority){
    Writer w;
    // create id to the new plane
    string id = reader->getNewID(CUSTOMERS_FILE);
    // check the validity of the priority
    if (priority < 1 || priority > 5) {
        __throw_invalid_argument("The priority of the customer has to be between 1 to 5");
    }
    // create new customer
    MyCustomer *newCustomer = new MyCustomer(full_name, priority, id, this->reader);
    // add the new customer to the customers's map
    if (newCustomer != nullptr) {
        this->customers.insert(pair<string, MyCustomer*>(id, newCustomer));
    }
    // write the new customer to the customer's table
    w.writeCustomer(newCustomer);
    return newCustomer;
}

/**
 * get customer from the customer's table (or from the customers's map)
 * @param id - the id of the customer we want
 * @return the customer with the 'id' the function get
 */
Customer* MyImplementation:: getCustomer(string id) {
    Customer *customer;
    // if the customer exist in the customers's map
    if (this->customers.find(id) != this->customers.end()) {
        // get the customer from the customers's map
        customer = this->customers.find(id)->second;
    } else {
        // get the customer from the customer's table
        customer = reader->getCustomer(id);
    }
    return customer;
}

/**
 * create new reservation, add him to the reservation's table and return him
 * @param customerId - the id of the customer
 * @param flightId - the id of the flight
 * @param cls - the class
 * @param max_baggage - the max baggage
 * @return - new reservation
 */
Reservation* MyImplementation:: addResevation(string customerId, string flightId,
                                              Classes cls, int max_baggage){
    Writer w;
    ValidCheck c;
    // if this customer doesn't exist
    if (!c.customerExist(customerId, this->reader)) {
        __throw_invalid_argument("Doesn't exist customer with this id");
    }
    // if this flight doesn't exist
    if (!c.flightExist(flightId, this->reader)) {
        __throw_invalid_argument("Doesn't exist flight with this id");
    }
    // if there is no place in this flight in this class
    if (!c.flightAvailable(flightId, cls, this->reader)) {
        __throw_invalid_argument("There is no place in this flight, in this class");
    }

    // create id to the new reservation
    string id = reader->getNewID(RESERVATIONS_FILE);

    // create new reservation
    MyReservation *newReservation = new MyReservation(customerId, flightId, cls,
                                                      max_baggage, id, this->reader);
    // add the new reservation to the reservation's map
    if (newReservation != nullptr) {
        this->reservations.insert(pair<string, MyReservation*>(id, newReservation));
    }
    // write the new reservation to the reservation's table
    w.writeReservation(newReservation);
    return newReservation;
}

/**
 * get reservation from the reservation's table (or from the reservations's map)
 * @param id - the id of the reservation we want
 * @return the reservation with the 'id' the function get
 */
Reservation* MyImplementation:: getReservation(string id){
    Reservation *reservation;
    // if the reservation exist in the reservations's map
    if (this->reservations.find(id) != this->reservations.end()) {
        // get the reservation from the reservations's map
        reservation = this->reservations.find(id)->second;
    } else {
        // get the reservation from the reservation's table
        reservation = reader->getReservation(id);
    }
    return reservation;
}

/**
 * exit
 */
void MyImplementation:: exit() {

}

/**
 * destructor
 */
MyImplementation:: ~MyImplementation() {
    for (auto const& employee : this->employees) {
        delete(employee.second);
    }
    for (auto const& customer : this->customers) {
        delete(customer.second);
    }
    for (auto const& plane : this->planes) {
        delete(plane.second);
    }
    for (auto const& flight : this->flights) {
        delete(flight.second);
    }
    for (auto const& reservation : this->reservations) {
        delete(reservation.second);
    }
    delete(reader);
}