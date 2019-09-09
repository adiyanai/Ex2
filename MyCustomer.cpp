#include "MyCustomer.h"
#include "Reader.h"

/**
 * constructor
 * @param fullName - the full name of the customer
 * @param priority - the priority of the customer
 * @param id - the id of the customer
 * @param reader - a Reader*
 */
MyCustomer:: MyCustomer(string fullName, int priority, string id, Reader* reader) {
    this->id = id;
    this->fullName = fullName;
    this->priority = priority;
    this->r = reader;
}
/**
 * return the full name of the customer
 * @return the full name of the customer
 */
string MyCustomer:: getFullName() {
    return this->fullName;
}
/**
 * return the priority of the customer
 * @return the priority of the customer
 */
int MyCustomer:: getPriority() {
    return this->priority;
}
/**
 * return the list of reservation of the customer
 * @return the list of reservation of the customer
 */
list<Reservation*> MyCustomer:: getReservations() {
    return r->getCustomerReservations(this->id);
}
/**
 * return the id of the customer
 * @return the id of the customer
 */
string MyCustomer:: getID() {
    return this->id;
}