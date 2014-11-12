/******************************************************************************
 * This is class Time which implements a time with microsecond resolution     *
 ******************************************************************************/

#include "../include/Time.H"

/*=============================================================================
  Time() - constructor, set to current time
  ============================================================================*/
Time::Time(){
  gettimeofday(&t,NULL);
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
  gettimeofday(&t,NULL);
}


/*=============================================================================
  void set(struct timeval &t) - set the time from a struct timeval
  ============================================================================*/
void Time::set(struct timeval &time){
  t.tv_sec=time.tv_sec;
  t.tv_usec=time.tv_usec;
}


/*=============================================================================
  void set(double t) - set the time from a double
  ============================================================================*/
void Time::set(double &time){
  t.tv_sec=(int)time;
  t.tv_usec=(int)round((time-t.tv_sec)*1000000);
  if(t.tv_usec==1000000){
    t.tv_sec++;
    t.tv_usec=0;
  }
}


/*=============================================================================
  void operator=(Time &t) - set the time
  ============================================================================*/
void Time::operator=(Time &time){
  t.tv_sec=time.t.tv_sec;
  t.tv_usec=time.t.tv_usec;
}


/*=============================================================================
  double get() - get the time as a double, in seconds
  ============================================================================*/
double Time::get(){
  return (double)t.tv_sec+(double)t.tv_usec/1000000;
}


/*=============================================================================
  void get(struct timeval &t) - get the time in a timeval structure
  ============================================================================*/
void Time::get(struct timeval &time){
  time.tv_sec=t.tv_sec;
  time.tv_usec=t.tv_usec;
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
  tmp=t.tv_usec;
  memcpy(d+sizeof(int),&tmp,sizeof(int));
}


/*=============================================================================
  void read(unsigned char *d) - read time from memory
  ============================================================================*/
void Time::read(unsigned char *d){
  int tmp;
  memcpy(&tmp,d,sizeof(int));
  t.tv_sec=tmp;
  memcpy(&tmp,d+sizeof(int),sizeof(int));
  t.tv_usec=tmp;
}

