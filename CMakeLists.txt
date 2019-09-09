cmake_minimum_required(VERSION 3.12)
project(Ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex2 Date.cpp MyCustomer.cpp MyCustomer.h MyEmployee.cpp MyEmployee.h MyFlight.cpp MyFlight.h MyImplementation.cpp MyImplementation.h MyPlane.cpp MyPlane.h MyReservation.cpp MyReservation.h Reader.cpp Reader.h ValidCheck.cpp ValidCheck.h Writer.cpp Writer.h interface.h test.cpp)