#include "Betonski.h"
#include "Util.h"
#include "Junk.h"
#include "Coordinate.h"
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

const int WASTELAND_VALUE=0;
const int GOLD_VALUE=500;
const int METAL_VALUE=100;
const int FOOD_VALUE=50;
const int STONE_VALUE=20;

Betonski::Betonski(string name){
  if(name.size()==0)
    throw EXCEPTION_NAME;
  else{
    this->name=name;
    captured=false;
    anger=0;
    position.setRow(-1);
    position.setColumn(-1);
  }
}

string Betonski::getName() const{
  return name;
}

int Betonski::getAnger() const{
  return anger;
}
bool Betonski::isCaptured() const{
  return captured;
}
Coordinate Betonski::getPosition() const{
  return position;
}

void Betonski::capture(){
  captured=true;
}

void Betonski::setPosition(const Coordinate &coord){
  position=coord;
}

int Betonski::calculateValue() const{
  int total=0;
  for(unsigned int i=0;i<bag.size();i++){
    switch(bag[i].getType()) {
      case WASTELAND: total+=WASTELAND_VALUE*bag[i].getQuantity();
          break;
      case GOLD: total+=GOLD_VALUE*bag[i].getQuantity();
          break;
      case METAL: total+=METAL_VALUE*bag[i].getQuantity();
          break;
      case FOOD: total+=FOOD_VALUE*bag[i].getQuantity();
          break;
      case STONE: total+=STONE_VALUE*bag[i].getQuantity();
          break;
    }
  }
  return total;
}

int Betonski::calculateValue(JunkType type) const{
  int total=0;
  for(unsigned int i=0;i<bag.size();i++){
    if(bag[i].getType()==type){
      switch(type) {
        case WASTELAND: total+=WASTELAND_VALUE*bag[i].getQuantity();
          break;
        case GOLD: total+=GOLD_VALUE*bag[i].getQuantity();
          break;
        case METAL: total+=METAL_VALUE*bag[i].getQuantity();
          break;
        case FOOD: total+=FOOD_VALUE*bag[i].getQuantity();
          break;
        case STONE: total+=STONE_VALUE*bag[i].getQuantity();
          break;
      }
    }
  }
  return total;
}

int Betonski::spoliation(){
  int totalValue=0;
  if(!captured)
    throw BETONSKI_NOT_CAPTURED;
  else if((calculateValue()+getAnger())>5000){
    captured=false;
    anger=0;
    throw EXCEPTION_REBELION;
  }
  else{
    totalValue=calculateValue();
    bag.clear();
    anger+=totalValue;
    return totalValue;
  }
}

int Betonski::spoliation(JunkType type){
  int totalValue=0;
  if(!captured)
    throw BETONSKI_NOT_CAPTURED;
  else if((calculateValue(type)+getAnger())>5000){
    captured=false;
    anger=0;
    throw EXCEPTION_REBELION;
  }
  else{
    totalValue=calculateValue(type);
    bag.clear();
    anger+=totalValue;
    return totalValue;
  }
}

int Betonski::extract(Map &map){
  Junk junk;
  if(map.isInside(position)){
    switch(map.getJunk(position).getType()){
      case WASTELAND: return WASTELAND_VALUE;
      case GOLD:  Junk(GOLD,junk.getQuantity());
                  bag.push_back(junk);
                  return GOLD_VALUE;
      case METAL: Junk(GOLD,junk.getQuantity());
                  bag.push_back(junk);
                  return METAL_VALUE;
      case FOOD:  Junk(GOLD,junk.getQuantity());
                  bag.push_back(junk);
                  return FOOD_VALUE;
      case STONE: Junk(GOLD,junk.getQuantity());
                  bag.push_back(junk);
                  return STONE_VALUE;
    }
  }
  else 
    return WASTELAND_VALUE;
  return WASTELAND_VALUE;
}

bool Betonski::move(const Map &map){
  Util util;
  Coordinate tryPosition;
  if(map.isInside(position)){
    switch(util.getRandomNumber(8)){
      case 0: tryPosition.setColumn(position.getColumn());
              tryPosition.setRow(position.getRow()-1);
              if(map.isInside(tryPosition)){
                position.setRow(position.getRow()-1);
                return true;
              }
              else
                return false;

      case 1: tryPosition.setColumn(position.getColumn()+1);
              tryPosition.setRow(position.getRow()-1);
              if(map.isInside(tryPosition)){
                position.setColumn(position.getColumn()+1);
                position.setRow(position.getRow()-1);
                return true;
              }
              else
                return false;

      case 2: tryPosition.setColumn(position.getColumn()+1);
              tryPosition.setRow(position.getRow());
              if(map.isInside(tryPosition)){
                position.setColumn(position.getColumn()+1);
                return true;
              }
              else
                return false;

      case 3: tryPosition.setColumn(position.getColumn()+1);
              tryPosition.setRow(position.getRow()+1);
              if(map.isInside(tryPosition)){
                position.setColumn(position.getColumn()+1);
                position.setRow(position.getRow()+1);
                return true;
              }
              else
                return false;

      case 4: tryPosition.setColumn(position.getColumn());
              tryPosition.setRow(position.getRow()+1);
              if(map.isInside(tryPosition)){
                position.setRow(position.getRow()+1);
                return true;
              }
              else
                return false;

      case 5: tryPosition.setColumn(position.getColumn()-1);
              tryPosition.setRow(position.getRow()+1);
              if(map.isInside(tryPosition)){
                position.setColumn(position.getColumn()-1);
                position.setRow(position.getRow()+1);
                return true;
              }
              else
                return false;

      case 6: tryPosition.setColumn(position.getColumn()-1);
              tryPosition.setRow(position.getRow());
              if(map.isInside(tryPosition)){
                position.setColumn(position.getColumn()-1);
                return true;
              }
              else
                return false;

      case 7: tryPosition.setColumn(position.getColumn()-1);
              tryPosition.setRow(position.getRow()-1);
              if(map.isInside(tryPosition)){
                position.setColumn(position.getColumn()-1);
                position.setRow(position.getRow()-1);
                return true;
              }
              else
                return false;
    }
  }
  else{
    throw EXCEPTION_OUTSIDE;
    return false;
  }
  return false;
}

ostream& operator<<(ostream &os,const Betonski &betonski){
  os<<"Betonski "<<'"'<<betonski.getName()<<'"'<<' ';
  if(betonski.isCaptured())
    os<<"Captured ";
  else
    os<<"Free ";
  os<<betonski.getAnger()<<" ["<<betonski.getPosition().getRow()<<','<<betonski.getPosition().getColumn()<<']'<<endl;
  if(betonski.bag.size()!=0){
    for(unsigned int i=0;i<betonski.bag.size();i++){
      os<<'[';
      switch(betonski.bag[i].getType()){
        case WASTELAND://el compilador da error si no lo pongo
          os<<"WASTELAND";
          break;
        case GOLD:  os<<"GOLD";
          break;
        case METAL: os<<"METAL";
          break;
        case FOOD:  os<<"FOOD";
          break;
        case STONE: os<<"STONE";
          break;
      }
      os<<':'<<betonski.bag[i].getQuantity()<<']';
    }
  }
  else
    cout<<endl;
  return os;
}