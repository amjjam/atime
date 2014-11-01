/******************************************************************************
 * This is class Time which implements a time with microsecond resolution     *
 ******************************************************************************/

#include "../include/Time.H"

/*=============================================================================
  Time() - constructor, set to current time
  ============================================================================*/
Time::Time(){
  gettimeofday(&t);
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
  gettimeofday(&t);
}


/*=============================================================================
  void get(struct timeval &t) - get the time in a timeval structure
  ============================================================================*/
void Time::get(struct timeval &time){
  time.tv_sec=t.tv_sec;
  time.tv_usec=t.tv_usec;
}


/*=============================================================================
  double get() - get the time as a double, in seconds
  ============================================================================*/
double Time::get(){
  return (double)t.tv_sec+(double)t.tv_usec/1000000;
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

