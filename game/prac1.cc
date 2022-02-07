// 50504264J Samuel Padilla Belvis
#include <iostream>
#include <cstring>
#include <cstdlib> // Para rand(), srand() y atoi()

using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado

struct Core{
  int attack;
  int defense;
  int hp;
};

enum Breed{
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
};

struct Enemy{
  Breed name;
  Core features;
};

struct Hero{
  char name[KNAME];
  Core features;
  bool special;
  int runaways;
  int exp;
  int kills[KENEMIES];
};

int rollDice(){
  return rand()%KDICE+1;
}

Hero nombreHero(){
  Hero player;
  int n;
  bool name_error;
  do{
  name_error=false;
  cout<<"Enter hero name:\t";
  cin.getline(player.name,KNAME-1);
  n=strlen(player.name);
  if(isalpha(player.name[0])==0)
  	name_error=true;
  for(int i=0;i<n;i++){
  	if((isalnum(player.name[i])==0)&&(player.name[i]!=' ')){
  		name_error=true;
  	}
  }
  if(name_error)
  	cout<<"ERROR: wrong name"<<endl;
  }while(name_error);
  return player;
}

Hero attack_defense(){
  Hero player;
  bool error;
  int n1,n2;
  char c;
  do{
  error=false;
  cout<<"Enter attack/defense:\t";
  cin>>n1>>c>>n2;
  if((n1+n2)!=100){
    cout<<"ERROR: wrong distribution"<<endl;
    error=true;
   }
  }while(error);
  player.features.attack=n1*KPOINTS/100;
  player.features.defense=n2*KPOINTS/100;
  player.features.hp=n2*player.features.defense;
  return player;
}

Hero createHero(){
  Hero player;
  player=nombreHero();
  player=attack_defense();
  return player;
}

/*Enemy createEnemy(){
}*/

void fight(Hero &hero,Enemy &enemy){
}

void report(const Hero &hero){
}

void showMenu(){
  cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

int main(int argc,char *argv[]){
  createHero();
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
  }
}
