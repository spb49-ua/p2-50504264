#include "Junk.h"
#include "Util.h"
using namespace std;

const int WASTELAND_VALUE=0;
const int GOLD_VALUE=500;
const int METAL_VALUE=100;
const int FOOD_VALUE=50;
const int STONE_VALUE=20;

Junk::Junk(){
  type=WASTELAND;
  quantity=0;
}

Junk::Junk(JunkType type, int quantity){
  this->type=type;
  if(quantity>=0)
   this->quantity=quantity;
  else
    throw EXCEPTION_QUANTITY;
}

JunkType Junk::getType() const{
  return type;
}

int Junk::getQuantity() const{
  return quantity;
}

char Junk::getTypeChar() const{
  char letra;
  switch(type){
    case WASTELAND: letra='W';
      break;
    case GOLD: letra='G';
      break;
    case METAL: letra='M';
      break;
    case FOOD: letra='F';
      break;
    case STONE: letra='S';
      break;
  }
  return letra;
}

int Junk::getValue() const{
  switch(type) {
    case WASTELAND: return WASTELAND_VALUE*quantity;
    case GOLD: return GOLD_VALUE*quantity;
    case METAL: return METAL_VALUE*quantity;
    case FOOD: return FOOD_VALUE*quantity;
    case STONE: return STONE_VALUE*quantity;
  }
  return 0;
}

ostream& operator<<(ostream &os,const Junk &junk){
  string tipo;
  switch(junk.type) {
    case WASTELAND: tipo="WASTELAND";
      break;
    case GOLD: tipo="GOLD";
      break;
    case METAL: tipo="METAL";
      break;
    case FOOD: tipo="FOOD";
      break;
    case STONE: tipo="STONE";
      break;
  }
  os<<'['<<tipo<<':'<<junk.quantity<<']';
  return os;
}