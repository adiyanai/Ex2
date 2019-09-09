#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "Reader.h"
using namespace std;

#define EMPLOYEES_FILE "employees.txt"
#define CUSTOMERS_FILE "customers.txt"
#define PLANES_FILE "planes.txt"
#define FLIGHTS_FILE "flights.txt"
#define RESERVATIONS_FILE "reservation.txt"
#define EMPLOYEE_FLIGHT_FILE "employee-flight.txt"
#define DIVIDE_CHAR ','
#define NEW_LINE '\n'

/**
 * split a line of information by a specific char
 * @param info - a line of information
 * @param divide - the char we want to divide by him
 * @return a string vector with the aplit information
 */
vector<string> Reader:: split(string info, char divide) {
    stringstream s(info);
    string part;
    vector<string> splitLine;

    while (getline(s, part, divide)) {
        splitLine.push_back(part);
    }

    return splitLine;
}

/**
 * get new id according to a file
 * @param file - a file
 * @return new id
 */
string Reader:: getNewID(string file) {

    ofstream write;
    write.open (file, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    write.close();

    ifstream readFile;
    readFile.open(file);
    if(!readFile.is_open()) {
        throw "can't create the file";
    }

    // read the last line of the file
    readFile.seekg(-2,ios_base:: end);
    string lastLine, ID;
    int nextId;

    bool keepLooping = true;
    while (keepLooping) {
        char ch;
        // Get current byte's data
        readFile.get(ch);
        // If the data was at or before the 0th byte
        if ((int) readFile.tellg() <= 1) {
            // The first line is the last line
            readFile.seekg(0);
            // So stop there
            keepLooping = false;
            // If the data was a newline
        } else if (ch == '\n') {
            // Stop at the current position.
            keepLooping = false;
            // If the data was neither a newline nor at the 0 byte
        } else {
            // Move to the front of that data, then to the front of the data before it
            readFile.seekg(-2, ios_base::cur);
        }
    }

    string lastGivenID = "";
    getline(readFile, lastLine);
    // if there is nothing in the file
    if (lastLine == "") {
        return "1";
    }

    for (int i = 0; i < lastLine.length(); ++i) {
        if(lastLine[i] == DIVIDE_CHAR || lastLine[i] == NEW_LINE) {
            break;
        }
        lastGivenID += lastLine[i];
    }
    // create the next id
    nextId = stoi(lastGivenID) + 1;
    ID = to_string(nextId);

    readFile.close();
    return ID;
}

/**
 * find line by the id we want.
 * the id need to be in the "place" that we send to the function
 * @param file - the file we want to read from
 * @param id - the id we search so we can get the line with her information
 * @param place - the place in the line that the id we search is located
 * @return the line with the id we want
 */
string Reader:: findLineById(string file, string id, int place) {
    ifstream readFile;
    readFile.open(file);
    string line;
    if(!readFile.is_open()) {
        throw "can't create the file";
    }

    while (getline(readFile, line)) {
        if (line.find(id, 0) != string::npos) {
            // if the id isn't in the place we want
            if (split(line, ',')[place] != id) {
                continue;
            }
            break;
        }
    }
    readFile.close();
    return line;
}

/**
 * find lines by the id we want.
 * the id need to be in the "place" that we send to the function
 * @param file - the file we want to read from
 * @param id - the id we search so we can get the lines with her information
 * @param place - the place in the line that the id we search is located
 * @return - vector<string> - the lines with the id we want
 */
vector<string> Reader:: findLinesById(string file, string id, int place) {
    ifstream readFile;
    readFile.open(file);
    string line;
    if(!readFile.is_open()) {
        throw "can't create the file";
    }
    vector<string> all, e;
    while (getline(readFile, line)) {
        if (line.find(id, 0) != string::npos) {
            // if the id isn't in the place we want
            if (split(line, ',')[place] != id) {
                continue;
            }
            e = split(line, ',');
            all.push_back(e[0]);
        }
    }
    readFile.close();
    return all;
}

/**
 * get employee from the employees's table (or from the employee's map)
 * @param id - the id of the employee we want
 * @return - the employee with the 'id' the function get
 */
MyEmployee* Reader:: getEmployee(string id) {
    MyEmployee* emp;

    // if the employee exist in the employees's map
    if (this->employees.find(id) != this->employees.end()) {
        // get the employee from the employees's map
        emp = this->employees.find(id)->second;
        return emp;
    } else {
        // find the employee on the employees's table
        string info = findLineById(EMPLOYEES_FILE, id, 0);
        vector<string> e;
        if (!info.empty()) {
            e = split(info, ',');
            Jobs job;

            if (e[1] == "MANAGER") {
                job = MANAGER;
            } else if (e[1] == "NAVIGATOR") {
                job = NAVIGATOR;
            } else if (e[1] == "FLY_ATTENDANT") {
                job = FLY_ATTENDANT;
            } else if (e[1] == "PILOT") {
                job = PILOT;
            } else {
                job = OTHER;
            }
            // create the employee
            emp = new MyEmployee(stoi(e[2]), stoi(e[3]), e[4], job, e[0], this);
            // add the employee to the employees's map
            this->employees.insert(pair<string, MyEmployee*>(id, emp));
            return emp;
        }
    }
    return nullptr;
}

/**
 * get customer from the customer's table (or from the customers's map)
 * @param id - the id of the customer we want
 * @return - the customer with the 'id' the function get
 */
MyCustomer* Reader:: getCustomer(string id) {
    MyCustomer* customer;
    // if the customer exist in the customers's map
    if (this->customers.find(id) != this->customers.end()) {
        // get the customer from the customers's map
        customer = this->customers.find(id)->second;
        return customer;
    } else {
        // find the customer on the customer's table
        string info = findLineById(CUSTOMERS_FILE, id, 0);
        vector<string> e;

        if (!info.empty()) {
            e = split(info, ',');
            // create the customer
            customer = new MyCustomer(e[1], stoi(e[2]), e[0], this);
            // add the customer to the customers's map
            this->customers.insert(pair<string, MyCustomer*>(id, customer));
            return customer;
        }
    }
    return nullptr;
}

/**
 * get plane from the planes's table (or from the plane's map)
 * @param id - the id of the plane we want
 * @return - the plane with the 'id' the function get
 */
MyPlane* Reader:: getPlane(string id) {
    MyPlane* plane;
    // if the plane exist in the planes's map
    if (this->planes.find(id) != this->planes.end()) {
        // get the customer from the customers's map
        plane = this->planes.find(id)->second;
        return plane;
    } else {
        // find the plane on the planes's table
        string info = findLineById(PLANES_FILE, id, 0);
        vector<string> e;

        if (!info.empty()) {
            map<Jobs, int> crewNeeded;
            map<Classes, int> max_passengers;
            e = split(info, ',');
            for (int i = 0; i <= OTHER; ++i) {
                crewNeeded.insert(pair<Jobs, int>((Jobs) i, stoi(e[5 + i])));
            }
            for (int i = 0; i <= SECOND_CLASS; ++i) {
                max_passengers.insert(pair<Classes, int>((Classes) i, stoi(e[2 + i])));
            }
            // create the plane
            plane = new MyPlane(stoi(e[1]), crewNeeded, max_passengers, e[0]);
            // add the plane to the planes's map
            this->planes.insert(pair<string, MyPlane*>(id, plane));
            return plane;
        }
    }
    return nullptr;
}

/**
 * get flight from the flights's table (or from the flight's map)
 * @param id - the id of the flight we want
 * @return - the flight with the 'id' the function get
 */
MyFlight* Reader:: getFlight(string id) {
    MyFlight* flight;
    // if the flight exist in the flights's map
    if (this->flights.find(id) != this->flights.end()) {
        // get the flight from the flights's map
        flight = this->flights.find(id)->second;
        return flight;
    } else {
        // find the flight on the flights's table
        string info = findLineById(FLIGHTS_FILE, id, 0);
        vector<string> e;

        if (!info.empty()) {
            e = split(info, ',');
            Date date = Date(e[2]);
            // create the flight
            flight = new MyFlight(stoi(e[1]), date, e[3], e[4], e[0], this);
            // add the flight to the flights's map
            this->flights.insert(pair<string, MyFlight*>(id, flight));
            return flight;
        }
    }
    return nullptr;
}

/**
 * get reservation from the reservations's table (or from the reservations's map)
 * @param id - the id of the reservation we want
 * @return - the reservation with the 'id' the function get
 */
MyReservation* Reader:: getReservation(string id) {
    MyReservation* reservation;
    // if the reservation exist in the reservations's map
    if (this->reservations.find(id) != this->reservations.end()) {
        // get the reservation from the reservations's map
        reservation = this->reservations.find(id)->second;
        return reservation;
    } else {
        // find the reservation on the reservations's table
        string info = findLineById(RESERVATIONS_FILE, id, 0);
        vector<string> e;

        if (!info.empty()) {
            e = split(info, ',');
            Classes cls;
            if (e[3] == "FIRST_CLASS") {
                cls = FIRST_CLASS;
            } else {
                cls = SECOND_CLASS;
            }
            // create the reservation
            reservation = new MyReservation(e[1], e[2], cls, stoi(e[4]), e[0], this);
            // add the reservation to the reservations's map
            this->reservations.insert(pair<string, MyReservation*>(id, reservation));
            return reservation;
        }
    }
    return nullptr;
}

/**
 * return list of reservation of a customer with the 'id' we get in the function
 * @param id - an id of the customer
 * @return list of reservation of a customer with the 'id' we get in the function
 */
list<Reservation*> Reader:: getCustomerReservations(string id) {
    vector<string> allReservation = findLinesById(RESERVATIONS_FILE, id, 1);
    list<Reservation*> listRes;
    vector<string> v;

    for (auto const& res: allReservation) {
        v = split(res, ',');
        Reservation *r = getReservation(v[0]);
        if (r != nullptr) {
            listRes.push_back(r);
        }
    }
    return listRes;
}

/**
 * return list of reservation of a flight with the 'id' we get in the function
 * @param id - an id of the flight
 * @return list of reservation of a flight with the 'id' we get in the function
 */
list<Reservation*> Reader:: getFlightReservations(string id) {
    vector<string> allReservation = findLinesById(RESERVATIONS_FILE, id, 2);
    list<Reservation*> listRes;
    vector<string> v;

    for (auto const& res: allReservation) {
        v = split(res, ',');
        Reservation *r = getReservation(v[0]);
        listRes.push_back(r);
    }

    return listRes;
}

/**
 * return list of employees of a flight with the 'id' we get in the function
 * @param id - an id of the flight
 * @return list of employees of a flight with the 'id' we get in the function
 */
list<Employee*> Reader:: getFlightEmployees(string id) {
    vector<string> allEmployees = findLinesById(EMPLOYEE_FLIGHT_FILE, id, 1);
    list<Employee*> listEmp;
    vector<string> v;

    for (auto const& emp: allEmployees) {
        v = split(emp, ',');
        Employee *e = getEmployee(v[0]);
        listEmp.push_back(e);
    }

    return listEmp;
}

/**
 * destructor
 */
Reader:: ~Reader() {
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
}