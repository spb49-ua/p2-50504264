#include "Betonski.h"
#include "Util.h"
#include "Junk.h"
#include "Coordinate.h"
#include "Jankali.h"
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

Jankali::Jankali(string name){
  if(name.size()!=0){
    this->name=name;
    power=300;
  }
  else
    throw EXCEPTION_NAME;
}

string Jankali::getName() const{
  return name;
}

int Jankali::getPower() const{
  return power;
}

void Jankali::hunt(vector<Betonski*> betonskis){
  for(unsigned int i=0;i<betonskis.size();i++){
    for(unsigned int j=0;j<traps.size();j++){
      if(betonskis[i]->getPosition().getColumn()==traps[j].getColumn()){
        if(betonskis[i]->getPosition().getRow()==traps[j].getRow()){
          if(!betonskis[i]->isCaptured()){
            betonskis[i]->capture();
            subdued.push_back(betonskis[i]);
          }
        }
      }
    }
  }
}

bool Jankali::setTrap(const Coordinate &coord){
  for(unsigned int i=0;i<traps.size();i++){
    if(coord.getColumn()==traps[i].getColumn()){
      if(coord.getRow()==traps[i].getRow()){
        if( power > ((coord.getRow()+2)*(coord.getColumn()+2)) ){
          return false;
        }
      }
    }
  }
  traps.push_back(coord);
  power=power-((coord.getRow()+2)*(coord.getColumn()+2));
  return true;
}

void Jankali::spoil(){
  for(unsigned int i=0;i<subdued.size();i++){
    /*if(subdued[i]->isCaptured()){
      power+=subdued[i]->spoliation();
    }
    else
      throw EXCEPTION_REBELION;*/
    try
      {
        power+=subdued[i]->spoliation();
      }
      catch(...)
      {
        subdued.erase(subdued.begin()+i);
      }
  }
}

void Jankali::spoil(JunkType type){
  for(unsigned int i=0;i<subdued.size();i++){
    //if(subdued[i]->isCaptured()){
      try
      {
        power+=subdued[i]->spoliation(type);
      }
      catch(...)
      {
        subdued.erase(subdued.begin()+i);
      }
      
    }
    //else
      //throw EXCEPTION_REBELION;
  //}
}

void Jankali::spoil(int pos){
  if(pos<(int)subdued.size()){
    //if(subdued[pos]->isCaptured()){
    //  power+=subdued[pos]->spoliation();
    //}
    //else
    //  throw EXCEPTION_REBELION;
    try
      {
        power+=subdued[pos]->spoliation();
      }
      catch(...)
      {
        subdued.erase(subdued.begin()+pos);
      }
  }
}

ostream& operator<<(ostream &os,const Jankali &jankali){
  os<<"Jankali "<<'"'<<jankali.getName()<<'"'<<" "<<jankali.getPower()<<endl;
  for(unsigned int i=0;i<jankali.subdued.size();i++){
    os<<*(jankali.subdued[i]);
    os<<endl;
  }
  os<<"Traps ";
  for(unsigned int j=0;j<jankali.traps.size();j++){
    os<<'['<<jankali.traps[j].getRow()<<','<<jankali.traps[j].getColumn()<<']';
  }
  return os;
}