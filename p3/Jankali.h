#ifndef _JANKALI_H_
#define _JANKALI_H_

#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Util.h"

using namespace std;

class Jankali{

  friend ostream& operator<<(ostream &os,const Jankali &jankali);
  
  protected:
    string name;
    int power;
  public:
    Jankali(string name);
    string getName() const;
    int getPower() const;
    void hunt(vector<Betonski*> betonskis);
    bool setTrap(const Coordinate &coord);
    void spoil();
    void spoil(JunkType type);
    void spoil(int pos);
};

#endif
