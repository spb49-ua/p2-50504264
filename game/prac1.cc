// 50504264J Samuel Padilla Belvis
#include <iostream>
#include <cstring>
#include <cstdlib> // Para rand(), srand() y atoi()

using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado
const int AXOLOTL_ATTACK=40;
const int AXOLOTL_DEFENSE=40;
const int TROLL_ATTACK=60;
const int TROLL_DEFENSE=80;
const int ORC_ATTACK=80;
const int ORC_DEFENSE=120;
const int HELLHOUND_ATTACK=120;
const int HELLHOUND_DEFENSE=100;
const int DRAGON_ATTACK=160;
const int DRAGON_DEFENSE=140;

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

Hero nombreHero(Hero player){
  int n;
  bool name_error;
  do{
  name_error=false;
  cout<<"Enter hero name: ";
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

Hero attack_defense(Hero player){
  bool error;
  int n1,n2;
  char c;
  do{
  error=false;
  cout<<"Enter attack/defense: ";
  cin>>n1>>c>>n2;
  if(n1<=0){
    cout<<"ERROR: wrong distribution"<<endl;
    error=true;
   }
  if(n2<=0){
    cout<<"ERROR: wrong distribution"<<endl;
    error=true;
    }
  if((n1+n2)!=100){
    cout<<"ERROR: wrong distribution"<<endl;
    error=true;
   }
  }while(error);
  player.features.attack=n1*KPOINTS/100;
  player.features.defense=n2*KPOINTS/100;
  player.features.hp=2*player.features.defense;
  
  return player;
}

Hero createHero(Hero player){
  player=nombreHero(player);
  player=attack_defense(player);
  return player;
}

Enemy selectEnemy(Enemy enemigo){
  int n;
  n=rollDice();
  switch(n){
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      enemigo.name=AXOLOTL;
    break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
      enemigo.name=TROLL;
    break;
    case 12:
    case 13:
    case 14:
    case 15:
      enemigo.name=ORC;
    break;
    case 16:
    case 17:
    case 18:
      enemigo.name=HELLHOUND;
    break;
    case 19:
    case 20:
      enemigo.name=DRAGON;
    break;
  }
  return enemigo;
}

Enemy enemyStats(Enemy enemigo){
  cout<<"[Enemy]"<<endl;
  cout<<"Breed: ";
  switch(enemigo.name){
    case 0:
      cout<<"Axolotl";
      enemigo.features.attack=AXOLOTL_ATTACK;
      enemigo.features.defense=AXOLOTL_DEFENSE;
      enemigo.features.hp=2*AXOLOTL_DEFENSE;
    break;
    case 1:
      cout<<"Troll";
      enemigo.features.attack=TROLL_ATTACK;
      enemigo.features.defense=TROLL_DEFENSE;
      enemigo.features.hp=2*TROLL_DEFENSE;
    break;
    case 2:
      cout<<"Orc";
      enemigo.features.attack=ORC_ATTACK;
      enemigo.features.defense=ORC_DEFENSE;
      enemigo.features.hp=2*ORC_DEFENSE;
    break;
    case 3:
      cout<<"Heallhound";
      enemigo.features.attack=HELLHOUND_ATTACK;
      enemigo.features.defense=HELLHOUND_DEFENSE;
      enemigo.features.hp=2*HELLHOUND_DEFENSE;
    break;
    case 4:
        cout<<"Dragon";
      enemigo.features.attack=DRAGON_ATTACK;
      enemigo.features.defense=DRAGON_DEFENSE;
      enemigo.features.	hp=2*DRAGON_DEFENSE;
    break;
    }
    cout<<endl;
    cout<<"Attack: "<<enemigo.features.attack<<endl;
    cout<<"Defense: "<<enemigo.features.defense<<endl;
    cout<<"Health points: "<<enemigo.features.hp<<endl;
    return enemigo;
}

Enemy createEnemy(Enemy enemigo){
  enemigo=selectEnemy(enemigo);
  enemigo=enemyStats(enemigo);
  return enemigo;
}

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

void fight(){
}

void menu(){
char op='q';
do{
  if(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='q')
    cout<<"ERROR: wrong option"<<endl;
  showMenu();
  cin>>op;
  }while(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='q');
  
  switch(op){
    case '1':
    fight();
    break;
    case '2':
    break;
    case '3':
    break;
    case '4':
    break;
    case 'q':
    break;
  }
}

int main(int argc,char *argv[]){
  Hero player;
  Enemy enemigo;
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
    
  player=createHero(player);
  enemigo=createEnemy(enemigo);
  menu();
  
  
    
    
  }
}

