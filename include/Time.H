/******************************************************************************
 * This is class Time which implements a time with microsecond resolution     *
 ******************************************************************************/

#ifndef _TIME_H_
#define _TIME_H_

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define BILLION 1000000000

class Time{
public:
  Time(); // Constructor sets time to current time
  ~Time(); // Destructor
  void set(); // Set to current time
  void set(struct timeval &t); // Set the time as a struct timeval
  void set(double &t); // Set the time as a double
  double get(); // Get the time as a double
  void get(struct timeval &t); // Get the time as a struct timeval
  void operator=(Time &t); // Copy the time into this object
  int size(); // Get the size of time as written to memory
  void write(unsigned char *d); // Write time to memory
  void read(unsigned char *d); // Read time from memory
  void operator+=(double t); // Add this many seconds
  void operator+=(Time &t); // Add this time time value
  void operator-=(double t); // Subtract this many seconds
  void operator-=(Time &t); // Subtrct this time value
private:
  struct timespec t;
};
  
#endif
