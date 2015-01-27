/******************************************************************************
 * This is class Time which implements a time with nanosecond resolution      *
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
  void set(int yr, int mo, int dy, int hr=0, int mn=0, int se=0, long
  ns=0) - set the time as year (yr), month (mo), day (dy), hour (hr),
  minute (mn), second (se), and nanosecond (ns)
  ============================================================================*/
void Time::set(int yr, int mo, int dy, int hr, int mn, int se, long ns){
  struct tm tm;
  tm.tm_sec=se;
  tm.tm_min=mn;
  tm.tm_hour=hr;
  tm.tm_mday=dy;
  tm.tm_mon=mo-1;
  tm.tm_year=yr-1900;
  
  t.tv_sec=timegm(&tm);
  t.tv_nsec=ns;
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
  void get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se, long
  &ns) - get the time as year (yr), month (mo), day(dy), hour (hr),
  minute (mn), second (se), nanosecond (ns)
  ============================================================================*/
void Time::get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se, long &ns){
  struct tm *tm;
  
  tm=gmtime(&t.tv_sec);
  yr=(*tm).tm_year+1900;
  mo=(*tm).tm_mon+1;
  dy=(*tm).tm_mday;
  hr=(*tm).tm_hour;
  mn=(*tm).tm_min;
  se=(*tm).tm_sec;
  
  ns=t.tv_nsec;
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se) - get
  the time as year (yr), month (mo), day(dy), hour (hr), minute (mn),
  second (se), ingoring nanosecond (ns)
  ============================================================================*/
void Time::get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se){
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy, int &hr, int &mn) - get the time
  as year (yr), month (mo), day(dy), hour (hr), minute (mn), ignoring
  second (se), nanosecond (ns)
  ============================================================================*/
void Time::get(int &yr, int &mo, int &dy, int &hr, int &mn){
  int se;
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy, int &hr) - get the time as year
  (yr), month (mo), day(dy), hour (hr), ignoring minute (mn), second
  (se), nanosecond (ns)
  ============================================================================*/
void Time::get(int &yr, int &mo, int &dy, int &hr){
  int mn,se;
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy) - get the time as year (yr),
  month (mo), day(dy), ignoring hour (hr), (mn), second (se),
  nanosecond (ns)
  ============================================================================*/
void Time::get(int &yr, int &mo, int &dy){
  int hr,mn,se;
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  int size() - get the size of time written to memory
  ============================================================================*/
int Time::size(){
  return 2*sizeof(int);
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
