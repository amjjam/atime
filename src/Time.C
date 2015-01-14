/******************************************************************************
 * This is class Time which implements a time with microsecond resolution     *
 ******************************************************************************/

#include "../include/Time.H"

/*=============================================================================
  Time() - constructor, set to current time
  ============================================================================*/
Time::Time(){
  clock_gettime(CLOCK_REALTIME,&t);
}


/*=============================================================================
  ~Time() - destructor
  ============================================================================*/
Time::~Time(){

}


/*=============================================================================
  void set() - set the time to the current time
  ============================================================================*/
void Time::set(){
  clock_gettime(CLOCK_REALTIME,&t);
}


/*=============================================================================
  void set(struct timespec &t) - set the time from a struct timespec
  ============================================================================*/
void Time::set(struct timespec &time){
  t.tv_sec=time.tv_sec;
  t.tv_nsec=time.tv_nsec;
}


/*=============================================================================
  void set(double t) - set the time from a double
  ============================================================================*/
void Time::set(double time){
  t.tv_sec=(int)time;
  t.tv_nsec=(int)round((time-t.tv_sec)*BILLION);
  if(t.tv_nsec==BILLION){
    t.tv_sec++;
    t.tv_nsec=0;
  }
}


/*=============================================================================
  double get() - get the time as a double, in seconds
  ============================================================================*/
double Time::get(){
  return (double)t.tv_sec+(double)t.tv_nsec/BILLION;
}


/*=============================================================================
  void get(struct timespec &t) - get the time in a timeval structure
  ============================================================================*/
void Time::get(struct timespec &time){
  time.tv_sec=t.tv_sec;
  time.tv_nsec=t.tv_nsec;
}


/*=============================================================================
  int size() - get the size of time written to memory
  ============================================================================*/
int Time::size(){
  return 2*sizeof(int);
}


/*=============================================================================
  void write(unsigned char *d) - write time to memory
  ============================================================================*/
void Time::write(unsigned char *d){
  int tmp;
  tmp=t.tv_sec;
  memcpy(d,&tmp,sizeof(int));
  tmp=t.tv_nsec;
  memcpy(d+sizeof(int),&tmp,sizeof(int));
}


/*=============================================================================
  void write(Buffer &b) - write time to a buffer
  ============================================================================*/
void Time::write(Buffer &b){
  int tmp;
  tmp=t.tv_sec;
  b.writeInt(tmp);
  tmp=t.tv_nsec;
  b.writeInt(tmp);
}


/*=============================================================================
  void read(unsigned char *d) - read time from memory
  ============================================================================*/
void Time::read(unsigned char *d){
  int tmp;
  memcpy(&tmp,d,sizeof(int));
  t.tv_sec=tmp;
  memcpy(&tmp,d+sizeof(int),sizeof(int));
  t.tv_nsec=tmp;
}


/*=============================================================================
  void read(Buffer &b) - read time from a buffer
  ============================================================================*/
void Time::read(Buffer &b){
  int tmp;
  tmp=b.readInt();
  t.tv_sec=tmp;
  tmp=b.readInt();
  t.tv_nsec=tmp;
}


/*=============================================================================
  void operator=(struct timespec &t) - set time from a timespec structure
  ============================================================================*/
void Time::operator=(struct timespec &t){
  set(t);
}


/*=============================================================================
  void operator=(double t) - set time from a double
  ============================================================================*/
void Time::operator=(double t){
  set(t);
}


/*=============================================================================
  void operator=(Time &t) - set the time
  ============================================================================*/
void Time::operator=(Time &time){
  t.tv_sec=time.t.tv_sec;
  t.tv_nsec=time.t.tv_nsec;
}


/*=============================================================================
  void operator+=(double t) - add the time, in decimal seconds, to this time. 

  The time may be positive or negative
  ============================================================================*/
void Time::operator+=(double t){
  set(get()+t);
}


/*=============================================================================
  void operator+=(Time &t) - add the time to this time. 
  
  Time t - value can only be positive. Negative time not defined. 
  ============================================================================*/
void Time::operator+=(Time &t){
  set(get()+t.get());
}


/*=============================================================================
  void operator-=(Time &t) - subtract the time, in decimal seconds,
  from this time.
  
  The time can be positive or negative
  ============================================================================*/
void Time::operator-=(double t){
  set(get()-t);
}


/*=============================================================================
  void operator-=(Time &t) - subtract the time from this time.

  The time to subtract can only be positive
  ============================================================================*/
void Time::operator-=(Time &t){
  set(get()-t.get());
}


/*=============================================================================
  double operator-(Time &t) - subtract the time from this time and
  return the difference as a double
  ============================================================================*/
double Time::operator-(Time &t){
  return get()-t.get();
}
