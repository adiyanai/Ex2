#include <iostream>
#include <fstream>
#include "Writer.h"
using namespace std;

#define EMPLOYEES_FILE "employees.txt"
#define CUSTOMERS_FILE "customers.txt"
#define PLANES_FILE "planes.txt"
#define FLIGHTS_FILE "flights.txt"
#define RESERVATIONS_FILE "reservation.txt"
#define EMPLOYEE_FLIGHT_FILE "employee-flight.txt"

/**
 * write a new employee to the employee's table
 * @param employee - a new employee
 */
void Writer:: writeEmployee(MyEmployee* employee) {
    ofstream write;
    // get all the employee's details
    string id = employee->getID();
    int seniority = employee->getSeniority();
    int birthYear = employee->getBirthYear();
    string idEmployer = employee->getEmployerId();

    Jobs title = employee->getTitle();
    string job;

    if (title == MANAGER) {
        job = "MANAGER";
    } else if (title == NAVIGATOR) {
        job = "NAVIGATOR";
    } else if (title == FLY_ATTENDANT) {
        job = "FLY_ATTENDANT";
    } else if (title == PILOT) {
        job = "PILOT";
    } else {
        job = "OTHER";
    }

    write.open (EMPLOYEES_FILE, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    write <<id<<","<<job<<","<<seniority<<","<<birthYear<<","<<idEmployer<<endl;
    write.close();
}

/**
 * write a new customer to the customer's table
 * @param customer - a new customer
 */
void Writer:: writeCustomer(MyCustomer* customer) {
    ofstream write;

    // get all the customer's details
    string id = customer->getID();
    string fullName = customer->getFullName();
    int priority = customer->getPriority();

    write.open (CUSTOMERS_FILE, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    write <<id<<","<<fullName<<","<<priority<<endl;
    write.close();
}

/**
 * write a new plane to the plane's table
 * @param plane - a new plane
 */
void Writer:: writePlane(MyPlane* plane) {
    ofstream write;

    // get all the plane's details
    string id = plane->getID();
    int modelNumber = plane->getModelNumber();
    map<Jobs, int> crewNeeded = plane->getCrewNeeded();
    int maxFirstClass = plane->getMaxFirstClass();
    int maxEconomyClass = plane->getMaxEconomyClass();

    write.open (PLANES_FILE, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    write <<id<<","<<modelNumber<<","<<maxFirstClass<<","<<maxEconomyClass<<",Crew needed:";

    // write all the crew that needed
    for (auto const& crew : crewNeeded) {
        write <<","<< crew.second;
    }
    write<<"\n";
    write.close();
}

/**
 * write a new flight to the flight's table
 * @param flight - a new flight
 */
void Writer:: writeFlight(MyFlight* flight) {
    ofstream write;
    // get all the flight's details
    string id = flight->getID();
    int modelNumber = flight->getModelNumber();
    string date = flight->getDate().getDate();
    string source = flight->getSource();
    string destination = flight->getDestination();

    write.open (FLIGHTS_FILE, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    write <<id<<","<<modelNumber<<","<<date<<","<<source<<","<<destination<<endl;
    write.close();
}

/**
 * write new reservation to the reservation's table
 * @param reservation - a new reservation
 */
void Writer:: writeReservation(MyReservation* reservation) {
    ofstream write;
    // get all the reservation's details
    string id = reservation->getID();
    string customerId = reservation->getCustomerId();
    string flightId = reservation->getFlightId();
    Classes cls = reservation->getClass();
    string clas;

    if (cls == FIRST_CLASS) {
        clas = "FIRST CLASS";
    } else {
        clas = "SECOND CLASS";
    }

    int maxBaggage = reservation->getMaxBaggage();
    write.open (RESERVATIONS_FILE, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    write <<id<<","<<customerId<<","<<flightId<<","<<clas<<","<<maxBaggage<<endl;
    write.close();
}

/**
 * write employees and the flight they work in
 * @param num - how muck employees from the list we want to write
 * @param idEmployee - a list of employees
 * @param idFlight - the id of the flight
 */
void Writer:: writeEmployeeFlight(int num, list<string> idEmployee, string idFlight) {
    ofstream write;
    write.open (EMPLOYEE_FLIGHT_FILE, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    int count = 0;
    for (auto const& id : idEmployee) {
        if (count < num) {
            write <<id<<","<<idFlight<<endl;
            count++;
        } else {
            break;
        }
    }
    write.close();
}