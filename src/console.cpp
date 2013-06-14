#include <stdio.h>
#include <stdlib.h>

#include "quake.h"
#include "etas.cpp"

int main(int argc, char *argv[])
{
  double seed = 7.0;
  int    nGen = 999;

  // Grab command line parameters
  if (argc >= 2)  seed = atof(argv[1]);
  if (argc >= 3)  nGen = atoi(argv[2]);

  // Create ETAS generator
  ETAS generator;

  // Add seed event
  generator.addSeed( quake( seed ) );

  // Generate aftershock sequences
  generator.generate(nGen);

  // Output the events
  generator.print( stdout );

  return EXIT_SUCCESS;
}
