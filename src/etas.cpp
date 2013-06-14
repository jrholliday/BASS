#include <math.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include "quake.h"
#include "etas.h"


#define RAND() ((double)rand()/RAND_MAX)


ETAS::ETAS()
  : _Mm(1.0) , _dM(1.25) , _b(1.0) , _c(0.1) ,_p(1.25) , _d(0.004) , _q(1.35)
{
  // Seed RNG
  srand( time(NULL) );
}

ETAS::~ETAS()
{
}

///////////////////////////////////////////////////////////////////////////////
void
ETAS::addSeed(quake seed)
{
  events.push_back(seed);

  return;
}

///////////////////////////////////////////////////////////////////////////////
void
ETAS::generate(unsigned int numGenerationsMax)
{
  unsigned int genNum = 0;

  unsigned int start = 0;
  unsigned int stop  = events.size();

  unsigned int count = 0;

  // Loop over N generations of aftershocks
  do
  {
    count = 0;

    for (unsigned int i=start; i<stop; i++)
      count += generateAftershocks( events[i] );

    start = stop;
    stop  = events.size();
  }
  while ( (++genNum < numGenerationsMax) && (count > 0) );

  // Sort the events (into time order)
  std::sort( events.begin() , events.end() );

  return;
}

///////////////////////////////////////////////////////////////////////////////
void
ETAS::print(FILE* file)
{
  // Output the events
  for (unsigned int i=0; i<events.size(); i++)
  {
    fprintf(file,
            "%f\t%f\t%f\t%f\t%i\n",
            events[i].t,
            events[i].x,
            events[i].y,
            events[i].m,
            events[i].g
            );
  }

  return;
}

///////////////////////////////////////////////////////////////////////////////
inline
unsigned int
ETAS::generateAftershocks(quake seed)
{
  double Ms = seed.m;

  // Calc number of aftershocks
  unsigned int N = (int)pow( 10 , _b*(Ms - _dM - _Mm) );

  // Loop over N aftershocks
  for (unsigned int i=0; i<N; i++)
  {
    quake aftershock;

    // Calc aftershock generation number
    aftershock.g = seed.g + 1;

    // Calc aftershock mag
    aftershock.m = _Mm - log10(RAND())/_b;

    // Calc aftershock time
    double t = 0.0;

//    do
      t = _c*pow(RAND() , -1.0/(_p-1.0)) - _c;
//    while (t > 365.0);

    aftershock.t = seed.t + t;

    // Calc aftershock postion;
    double r = 0.0;

//    do
      r = _d*pow(10,0.5*Ms)*pow(RAND() , -1.0/(_q-1.0)) - _d*pow(10,0.5*Ms);
//    while ( r > 100000 );

    double theta = 2.0 * M_PI * RAND();

    aftershock.x = seed.x + r*cos(theta);
    aftershock.y = seed.y + r*sin(theta);

    // Add the aftershock to our list
    events.push_back(aftershock);
  }

  return N;
}

#undef RAND
