/******************************************************************************
 * This is class Time which implements a time with microsecond resolution     *
 ******************************************************************************/

#ifndef _TIME_H_
#define _TIME_H_

class Time{
public:
  Time(); // Constructor sets time to current time
  ~Time(); // Destructor
  void set(); // Set to current time
  void get(struct timeval &t); // Get the time as a timeval
  double get(); // Get the time as a double
  int size(); // Get the size of time as written to memory
  void write(unsigned char *d); // Write time to memory
  void read(unsigned char *d); // Read time from memory
private:
  struct timeval t;
};
  
#endif
