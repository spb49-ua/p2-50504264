#include "Coordinate.h"

using namespace std;

Coordinate::Coordinate(){
  row=-1;
  column=-1;
}

Coordinate::Coordinate(int row, int column){
  this->row=row;
  this->column=column;
}

int Coordinate::getRow() const{
  return row;
}

int Coordinate::getColumn() const{
  return column;
}

void Coordinate::setRow(int row){
  this->row=row;
}

void Coordinate::setColumn(int column){
  this->column=column;
}

bool Coordinate::compare(const Coordinate &coord) const{
  if(row==coord.row && column==coord.column)
    return true;
  else
    return false;
  return false;
}

ostream& operator<<(ostream &os,const Coordinate &coord){
  os<<'['<<coord.row<<','<<coord.column<<']';
  return os;
}
