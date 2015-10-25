/******************************************************************************
 * This is class Time which implements a time with nanosecond resolution      *
 ******************************************************************************/

#include "../include/aTime.H"

/*=============================================================================
  aTime() - constructor, set to current time
  ============================================================================*/
aTime::aTime(){
  clock_gettime(CLOCK_REALTIME,&t);
}


/*=============================================================================
  ~aTime() - destructor
  ============================================================================*/
aTime::~aTime(){

}


/*=============================================================================
  void set() - set the time to the current time
  ============================================================================*/
void aTime::set(){
  clock_gettime(CLOCK_REALTIME,&t);
}


/*=============================================================================
  void set(struct timespec &t) - set the time from a struct timespec
  ============================================================================*/
void aTime::set(struct timespec &time){
  t.tv_sec=time.tv_sec;
  t.tv_nsec=time.tv_nsec;
}


/*=============================================================================
  void set(double t) - set the time from a double
  ============================================================================*/
void aTime::set(double time){
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
void aTime::set(int yr, int mo, int dy, int hr, int mn, int se, long ns){
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
double aTime::get(){
  return (double)t.tv_sec+(double)t.tv_nsec/BILLION;
}


/*=============================================================================
  void get(struct timespec &t) - get the time in a timeval structure
  ============================================================================*/
void aTime::get(struct timespec &time){
  time.tv_sec=t.tv_sec;
  time.tv_nsec=t.tv_nsec;
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se, long
  &ns) - get the time as year (yr), month (mo), day(dy), hour (hr),
  minute (mn), second (se), nanosecond (ns)
  ============================================================================*/
void aTime::get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se, long &ns){
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
void aTime::get(int &yr, int &mo, int &dy, int &hr, int &mn, int &se){
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy, int &hr, int &mn) - get the time
  as year (yr), month (mo), day(dy), hour (hr), minute (mn), ignoring
  second (se), nanosecond (ns)
  ============================================================================*/
void aTime::get(int &yr, int &mo, int &dy, int &hr, int &mn){
  int se;
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy, int &hr) - get the time as year
  (yr), month (mo), day(dy), hour (hr), ignoring minute (mn), second
  (se), nanosecond (ns)
  ============================================================================*/
void aTime::get(int &yr, int &mo, int &dy, int &hr){
  int mn,se;
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  void get(int &yr, int &mo, int &dy) - get the time as year (yr),
  month (mo), day(dy), ignoring hour (hr), (mn), second (se),
  nanosecond (ns)
  ============================================================================*/
void aTime::get(int &yr, int &mo, int &dy){
  int hr,mn,se;
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);
}


/*=============================================================================
  int size() - get the size of time written to memory, writen in the
  standard version. The standard version is two integers, seconds of
  unix time and nanoseconds of the second.
  ============================================================================*/
int aTime::size(){
  return 2*sizeof(int);
}


/*=============================================================================
  int size2() - get the size of the time written to memory, written in
  version 2. Version 2 is as follows: unsigned short int (2 bytes) of
  year, unsigned char (1 byte) of month, unsigned char (1 byte) of
  day, double (8 bytes) seconds of day.
  ============================================================================*/
int aTime::size2(){
  return sizeof(unsigned short)+2*sizeof(unsigned char)+sizeof(double);
}

/*=============================================================================
  void write(unsigned char *d) - write the time to a memory area
  ============================================================================*/
void aTime::write(unsigned char *d){
  int tmp;
  tmp=t.tv_sec;
  memcpy(d,&tmp,sizeof(int));
  tmp=t.tv_nsec;
  memcpy(d+sizeof(int),&tmp,sizeof(int));
}


/*=============================================================================
  void write2(unsigned char *d) - write the time as version 2 to a memory area
  ============================================================================*/
void aTime::write2(unsigned char *d){
  int xyr,xmo,xdy;
  unsigned short yr;
  unsigned char mo,dy;
  double se;
  get(xyr,xmo,xdy);
  se=secOfDay();
  yr=xyr;
  mo=xmo;
  dy=xdy;
  memcpy(d,&yr,sizeof(unsigned short));
  memcpy(d+sizeof(unsigned short),&mo,sizeof(unsigned char));
  memcpy(d+sizeof(unsigned short)+sizeof(unsigned char),&dy,
	 sizeof(unsigned char));
  memcpy(d+sizeof(unsigned short)+2*sizeof(unsigned char),&se,sizeof(double));
}


/*=============================================================================
  void read(unsigned char *d) - read the time from a memory area
  ============================================================================*/
void aTime::read(unsigned char *d){
  int tmp;
  memcpy(&tmp,d,sizeof(int));
  t.tv_sec=tmp;
  memcpy(&tmp,d+sizeof(int),sizeof(int));
  t.tv_nsec=tmp;
}


/*=============================================================================
  void read2(unsigned char *d) - read the time as version 2 from a memory area
  ============================================================================*/
void aTime::read2(unsigned char *d){
  int xyr,xmo,xdy;
  unsigned short yr;
  unsigned char mo,dy;
  double se;
  memcpy(&yr,d,sizeof(unsigned short));
  memcpy(&mo,d+sizeof(unsigned short),sizeof(unsigned char));
  memcpy(&dy,d+sizeof(unsigned short)+sizeof(unsigned char),
	 sizeof(unsigned char));
  memcpy(&se,d+sizeof(unsigned short)+2*sizeof(unsigned char),sizeof(double));
  xyr=yr;
  xmo=mo;
  xdy=dy;
  set(xyr,xmo,xdy);
  operator+=(se);
}


/*=============================================================================
  double secOfDay() - returns seconds of the current
  day. I.e. hour*3600+minute*60+seconds+ns/1e9
  =============================================================================*/
double aTime::secOfDay(){
  int yr,mo,dy,hr,mn,se;
  long ns;
  get(yr,mo,dy,hr,mn,se,ns);

  return (double)hr*3600+(double)mn*60+(double)se+((double)ns)/BILLION;
}


/*=============================================================================
  void operator=(struct timespec &t) - set time from a timespec structure
  ============================================================================*/
void aTime::operator=(struct timespec &t){
  set(t);
}


/*=============================================================================
  void operator=(double t) - set time from a double
  ============================================================================*/
void aTime::operator=(double t){
  set(t);
}


/*=============================================================================
  void operator=(aTime &t) - set the time
  ============================================================================*/
void aTime::operator=(aTime &time){
  t.tv_sec=time.t.tv_sec;
  t.tv_nsec=time.t.tv_nsec;
}


/*=============================================================================
  void operator+=(double t) - add the time, in decimal seconds, to this time. 

  The time may be positive or negative
  ============================================================================*/
void aTime::operator+=(double t){
  set(get()+t);
}


/*=============================================================================
  void operator+=(aTime &t) - add the time to this time. 
  
  aTime t - value can only be positive. Negative time not defined. 
  ============================================================================*/
void aTime::operator+=(aTime &t){
  set(get()+t.get());
}


/*=============================================================================
  void operator-=(double t) - subtract the time, in decimal seconds,
  from this time.
  
  The time can be positive or negative
  ============================================================================*/
void aTime::operator-=(double t){
  set(get()-t);
}


/*=============================================================================
  void operator-=(aTime &t) - subtract the time from this time.

  The time to subtract can only be positive
  ============================================================================*/
void aTime::operator-=(aTime &t){
  set(get()-t.get());
}


/*=============================================================================
  double operator-(aTime &t) - subtract the time from this time and
  return the difference as a double
  ============================================================================*/
double aTime::operator-(aTime &t){
  return get()-t.get();
}


/*============================================================================
  bool operator==(aTime &t) - return true if this time equals t. False
  otherwise
  ===========================================================================*/
bool aTime::operator==(aTime &tt){
  if(t.tv_sec==tt.t.tv_sec&&t.tv_nsec==tt.t.tv_nsec)
    return true;
  return false;
}


/*===========================================================================
  bool operator>(aTime &t) - return true if this time is later than
  t. False otherwise.
  ==========================================================================*/
bool aTime::operator>(aTime &tt){
  if(t.tv_sec>tt.t.tv_sec)
    return true;
  if(t.tv_sec==tt.t.tv_sec&&t.tv_nsec>tt.t.tv_nsec)
    return true;
  return false;
}


/*===========================================================================
  bool operator>=(aTime &t) - return true if this time later than of
  equal to t. Return false otherwise.
  ==========================================================================*/
bool aTime::operator>=(aTime &tt){
  if(t.tv_sec>tt.t.tv_sec)
    return true;
  if(t.tv_sec==tt.t.tv_sec&&t.tv_nsec>=tt.t.tv_nsec)
    return true;
  return false;
}


/*==========================================================================
  bool operator<(aTime &t) - return true if this time is earlier than
  t. Return false otherwise.
  =========================================================================*/
bool aTime::operator<(aTime &tt){
  if(t.tv_sec<tt.t.tv_sec)
    return true;
  if(t.tv_sec==tt.t.tv_sec&&t.tv_nsec<tt.t.tv_nsec)
    return true;
  return false;
}


/*==========================================================================
  bool operator<=(aTime &t) - return true if this time is earlier than
  or same time as t. Return false otherwise.
  =========================================================================*/
bool aTime::operator<=(aTime &tt){
  if(t.tv_sec<tt.t.tv_sec)
    return true;
  if(t.tv_sec==tt.t.tv_sec&&t.tv_nsec<=tt.t.tv_nsec)
    return true;
  return false;
}


/*==========================================================================
  std::string printHMS() - return a string with just the time of day
  printed as HH:MM:SS.
  =========================================================================*/
std::string aTime::printHMS(){
  int yr,mo,dy,hr,mn,se;
  get(yr,mo,dy,hr,mn,se);
    
  std::string t;
  for(int i=0;i<3;i++){
    int j;
    if(i==0)
      j=hr;
    else if(i==1)
      j=mn;
    else if(i==2)
      j=se;
    
    int tmp=j/10;
    t+=(char)('0'+tmp);
    t+=(char)('0'+(j-tmp*10));
    if(i<2)
      t+=':';
  }
  return t;
}
