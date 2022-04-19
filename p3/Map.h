#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include "Coordinate.h"
#include "Junk.h"

using namespace std;

class Map{

  friend ostream& operator<<(ostream &os,const Map &map);
  
  protected:
    int rows;
    int columns;
    vector<vector<Junk>> junks;
  public:
    Map(int rows, int columns);
    bool isInside(const Coordinate &coord) const;
    void putJunk(const Junk &junk, const Coordinate &coord);
    Junk getJunk(const Coordinate &coord) const;
    Junk collectJunk(const Coordinate &coord);
};

#endif
