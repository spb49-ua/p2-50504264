#include "Map.h"
#include "Util.h"
#include "Coordinate.h"
#include "Junk.h"
#include <vector>
using namespace std;

Map::Map(int rows, int columns){
  
  if(rows>=5 && columns>=5){
    for(int i=0;i<rows;i++){
      Junk junk;
      vector<Junk> junkVector;
      for(int j=0;j<columns;j++)
       junkVector.push_back(junk);
      junks.push_back(junkVector);
    }
  }
  else
    throw EXCEPTION_SIZE;
}

bool Map::isInside(const Coordinate &coord) const{
  if(coord.getColumn()>0 && coord.getRow()>0 && coord.getColumn()<=columns && coord.getRow()<=rows)
    return true;
  else
    return false;
}

void Map::putJunk(const Junk &junk, const Coordinate &coord){
  if(isInside(coord))
    junks[coord.getRow()][coord.getColumn()]=junk;
  else
    throw EXCEPTION_OUTSIDE;
}

Junk Map::getJunk(const Coordinate &coord) const{
  if(isInside(coord))
    return junks[coord.getRow()][coord.getColumn()];
  else
    throw EXCEPTION_OUTSIDE;
}

Junk Map::collectJunk(const Coordinate &coord){
  if(isInside(coord)){
    Junk aux;
    aux=junks[coord.getRow()][coord.getColumn()];
    junks[coord.getRow()][coord.getColumn()]=Junk();
    return aux;
  }
  else
    throw EXCEPTION_OUTSIDE;
}

ostream& operator<<(ostream &os,const Map &map){
  Coordinate coord;
  for(int k=0;k<=map.rows+1;k++){
      for(int l=0;l<=map.columns;l++){
        if(l==0 && k==0) os<<"   ";
        else if(l==0){
          if(k-1>=10)
            os<<k-1<<" ";
          else
            os<<'0'<<k-1<<" ";
        }
        if(k==0){
          if(l>=10)
            os<<l<<" ";
          else
            os<<'0'<<l<<" ";
        }
        else{/*
          switch(map.junks[coord.getRow()][coord.getColumn()]){
            case WASTELAND: os<<"W ";
              break;
            case GOLD: os<<"G ";
              break;
            case METAL: os<<"M ";
              break;
            case FOOD: os<<"F ";
              break;
            case STONE: os<<"S ";
              break;
          }*/
          os<<map.junks[coord.getRow()][coord.getColumn()].getTypeChar()<<' ';
        }
      }
      os<<endl;
    }
  return os;
}