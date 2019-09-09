#include "MyFlight.h"
#include "Reader.h"

/**
 * constructor
 * @param modelNumber - the model number of the plane that the flight uses
 * @param date - the date of the flight
 * @param source - the source of the flight
 * @param destination - the destination of the flight
 * @param id - the id of the flight
 * @param reader - a Reader*
 */
MyFlight::MyFlight(int modelNumber, Date date, string source, string destination, string id,
                   Reader* reader) :date(date){
    this->id = id;
    this->modelNumber = modelNumber;
    this->date = date;
    this->source = source;
    this->destination = destination;
    this->r = reader;
}

/**
 * return the model number of the plane that the flight uses
 * @return the model number of the plane that the flight uses
 */
int MyFlight:: getModelNumber() {
    return this->modelNumber;
}
/**
 * return the flight reservations
 * @return the flight reservations
 */
list<Reservation*> MyFlight:: getReservations() {
    return r->getFlightReservations(this->id);
}
/**
 * return the list of employees that on the flight
 * @return the list of employees that on the flight
 */
list<Employee*> MyFlight:: getAssignedCrew() {
    return r->getFlightEmployees(this->id);
}
/**
 * return the date of the flight
 * @return the date of the flight
 */
Date MyFlight:: getDate() {
    return this->date;
}
/**
 * return the source of the flight
 * @return the source of the flight
 */
string MyFlight:: getSource() {
    return this->source;
}
/**
 * return the destination of the flight
 * @return the destination of the flight
 */
string MyFlight:: getDestination() {
    return this->destination;
}
/**
 * return the flight id
 * @return the flight id
 */
string MyFlight:: getID() {
    return this->id;
}