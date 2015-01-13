/******************************************************************************
 * This is class Time which implements a time with microsecond resolution     *
 ******************************************************************************/

#ifndef _TIME_H_
#define _TIME_H_

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "../../MessageQueue/include/Buffer.H"

#define BILLION 1000000000

class Time{
public:
  Time(); // Constructor sets time to current time
  ~Time(); // Destructor
  void set(); // Set to current time
  void set(struct timespec &t); // Set the time as a struct timeval
  void set(double t); // Set the time as a double
  double get(); // Get the time as a double
  void get(struct timespec &t); // Get the time as a struct timeval
  void operator=(Time &t); // Copy the time into this object
  int size(); // Get the size of time as written to memory
  void write(unsigned char *d); // Write time to memory
  void write(Buffer &b); // Write time to a buffer
  void read(unsigned char *d); // Read time from memory
  void read(Byffer &b); // Read time from a buffer
  void operator+=(double t); // Add this many seconds
  void operator+=(Time &t); // Add this time time value
  void operator-=(double t); // Subtract this many seconds
  void operator-=(Time &t); // Subtrct this time value
  double operator-(Time &t); // Return this - t as a double
private:
  struct timespec t;
};
  
#endif
