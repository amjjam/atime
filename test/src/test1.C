/******************************************************************************
 * A test program which exercises a few of the features of class Time         *
 ******************************************************************************/

#include <iostream>
#include "../../include/aTime.H"

int main(int argc, char *argv[]){
  
  aTime t;

  int yr,mo,dy,hr,mn,se;
  long ns;

  t.set(1970,1,1,1);
  t.get(yr,mo,dy,hr,mn,se,ns);
  std::cout << yr << "/" << mo << "/" << dy << " " << hr << ":" << mn << ":"
	    << se << " " << ns << std::endl;
  std::cout << t.get() << std::endl;

  t.set(1997,1,10,3,4);
  t.get(yr,mo,dy,hr,mn,se,ns);
  std::cout << yr << "/" << mo << "/" << dy << " " << hr << ":" << mn << ":"
	    << se << " " << ns << std::endl;

  t+=100000.0003;

  t.get(yr,mo,dy,hr,mn,se,ns);
  std::cout << yr << "/" << mo << "/" << dy << " " << hr << ":" << mn << ":"
	    << se << " " << ns << std::endl;

  // Notice here that when adding years they are counted from the
  // start of the Epoch, not from year zero.
  t+=t;
  t.get(yr,mo,dy,hr,mn,se,ns);
  std::cout << yr << "/" << mo << "/" << dy << " " << hr << ":" << mn << ":"
	    << se << " " << ns << std::endl;

  return 0;
}


