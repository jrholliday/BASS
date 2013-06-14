#ifndef __QUAKE__
#define __QUAKE__

class quake
{
 public:
  double m;  // Magnitude of earthquake
  double t;  // Time of earthquale
  double x;  // "x"-position (longitude) of earthquake
  double y;  // "x"-position (latitude) of earthquake

  unsigned int g;  // Generation number of earthquake (0=mainshock, N=aftershock)

  // Constructor
  quake(double _m=0.0, double _t=0.0, double _x=0.0, double _y=0.0, unsigned int _g=0)
    : m(_m) , t(_t) , x(_x) , y(_y) , g(_g) { };

  // Comparison operator (for sorting)
  bool operator < (const quake &eq) const { return (this->t < eq.t); };
};

#endif
