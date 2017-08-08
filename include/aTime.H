/******************************************************************************
 * This is class aTime which implements a time with nanoosecond resolution    *
 ******************************************************************************/

#ifndef _ATIME_H_
#define _ATIME_H_

#include <string>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define BILLION 1000000000

class aTime{
public:
  aTime(); // Constructor sets time to current time
  ~aTime(); // Destructor
  void set(); // Set to current time
  void set(const struct timespec &t); // Set the time as a struct timeval
  void set(double t); // Set the time as a double
  void set(int yr, int mo, int dy, int hr=0, int mn=0, int se=0, long ns=0); 
  double get() const; // Get the time as a double
  void get(struct timespec &t) const; // Get the time as a struct timeval
  void get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se, long &ns) const;
  void get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se) const;
  void get(int &yr, int &mo, int &dy, int &hr, int &mn) const;
  void get(int &yr, int &mo, int &dy, int &hr) const;
  void get(int &yr, int &mo, int &dy) const;
  int size() const; // Get the size of time as written to memory
  int size2() const; // Get the size as written to memory, version 2
  void write(unsigned char *d) const; // Write time to memory area
  void write2(unsigned char *d) const; // Write to memory, version 2
  void read(unsigned char *d); // Read time from memory area
  void read2(unsigned char *d); // Read from memory, version2
  double secOfDay() const; // Returns seconds of the curent day
  void operator=(const struct timespec &t); // Set equal to this time
  void operator=(double t); // Set equal to this time
  void operator=(const aTime &t); // Set equal to this time
  void operator+=(double t); // Add this many seconds
  void operator+=(const aTime &t); // Add this time time value
  void operator-=(double t); // Subtract this many seconds
  void operator-=(const aTime &t); // Subtrct this time value
  double operator-(const aTime &t) const; // Return this - t as a double
  bool operator==(const aTime &t) const; // Return true if this is same time as t
  bool operator>(const aTime &t) const; // Return true of this is later than t;
  bool operator>=(const aTime &t) const; // Return true if this is later or equal to t
  bool operator<(const aTime &t) const; // Return true if this is earlier than t
  bool operator<=(const aTime &t) const; // Return true if this is earlier or equal to t
  aTime operator+(const double t) const; // Return this + t in new object
  aTime operator-(const double t) const; // Return this - t in new object
  std::string printHMS() const; // Print time in HH:MM:SS format ignoring nanoseconds
  std::string printYMD() const; // Print YYYY/MM/DD format time
  std::string printYMDHMS() const; // Print YYYY/MM/DD HH:MM:SS format time ignoring nanoseconds
private:
  struct timespec t;
};
  
#endif
