#ifndef __ETAS__
#define __ETAS__

#include <vector>
#include "quake.h"

class ETAS
{
 private:
  // Parameters
  const double _Mm;
  const double _dM;
  const double _b;

  const double _c;
  const double _p;

  const double _d;
  const double _q;

  // Member data
  std::vector<quake> events;

  // Work horse function
  unsigned int generateAftershocks(quake seed);

 public:
  // Constructor/Destructor
  ETAS();
  ~ETAS();

  // Add "seed" event to generator
  void addSeed(quake eq);

  // Generate aftershocks
  void generate(unsigned int numGenerationsMax=9);

  // Data output method
  void print(FILE* file);
};

#endif
