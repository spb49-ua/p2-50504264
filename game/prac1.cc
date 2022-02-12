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
const int AXOLOTL_EXP=100;
const int TROLL_EXP=150;
const int ORC_EXP=200;
const int HELLHOUND_EXP=300;
const int DRAGON_EXP=400;

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
  player.special=true;
  player.runaways=3;
  player.exp=0;
  for(int i =0;i<KENEMIES;i++){
    player.kills[i]=0;
  }
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
      cout<<"Hellhound";
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

void enemyKilled(Hero &player,Enemy &enemigo){
    player.kills[enemigo.name]++;
    switch(enemigo.name){
      case 0:
      player.exp=player.exp + AXOLOTL_EXP;
      break;
      case 1:
      player.exp=player.exp + TROLL_EXP;
      break;
      case 2:
      player.exp=player.exp + ORC_EXP;
      break;
      case 3:
      player.exp=player.exp + HELLHOUND_EXP;
      break;
      case 4:
      player.exp=player.exp + DRAGON_EXP;
      break;
    }
}

void heroToEnemy(Hero &player,Enemy &enemigo,int extra){
  int n1,n2;
  n1=rollDice()*5*extra;
  n2=rollDice()*5;
  cout<<"[Hero -> Enemy]"<<endl;
  cout<<"Attack: "<<player.features.attack<<" + "<<n1<<endl;
  cout<<"Defense: "<<enemigo.features.defense<<" + "<<n2<<endl;
  cout<<"Hit points: ";
  if((player.features.attack+n1-(enemigo.features.defense+n2))>0){
    cout<<player.features.attack+n1-(enemigo.features.defense+n2);
    enemigo.features.hp=enemigo.features.hp-(player.features.attack+n1-(enemigo.features.defense+n2));
    }
  else
  	cout<<"0";
  cout<<endl;
  cout<<"Enemy health points: ";
  if(enemigo.features.hp<0)
    enemigo.features.hp=0;
  cout<<enemigo.features.hp<<endl;
  if(enemigo.features.hp==0){
    cout<<"Enemy killed"<<endl;
    enemyKilled(player,enemigo);
  }
}

void enemyToHero(Hero &player,Enemy &enemigo){
  int n1,n2;
  n1=rollDice()*5;
  n2=rollDice()*5;
  cout<<"[Enemy -> Hero]"<<endl;
  cout<<"Attack: "<<enemigo.features.attack<<" + "<<n1<<endl;
  cout<<"Defense: "<<player.features.defense<<" + "<<n2<<endl;
  cout<<"Hit points: ";
  if((enemigo.features.attack+n1-(player.features.defense+n2))>0){
    cout<<enemigo.features.attack+n1-(player.features.defense+n2);
    player.features.hp=player.features.hp-(enemigo.features.attack+n1-(player.features.defense+n2));
    }
  else
  	cout<<"0";
  cout<<endl;
  cout<<"Hero health points: ";
  if(player.features.hp<0)
    player.features.hp=0;
  cout<<player.features.hp<<endl;
}

void fight(Hero &player,Enemy &enemigo,bool &runawayAvailable){
  runawayAvailable=true;
  heroToEnemy(player,enemigo,1);
  if(enemigo.features.hp>0)
    enemyToHero(player,enemigo);
  else{
    enemigo=createEnemy(enemigo);
  }
}

void runaway(Hero &player,Enemy &enemigo,bool &runawayAvailable){
  if(player.runaways==0||runawayAvailable==false)
    cout<<"ERROR: cannot run away"<<endl;
  else{
    runawayAvailable=false;
    cout<<"You run away"<<endl;
    player.runaways--;
    enemigo=createEnemy(enemigo);
    
  }
}

void special(Hero &player,Enemy &enemigo){
  if(player.special){
    player.special=false;
    heroToEnemy(player,enemigo,3);
    if(enemigo.features.hp>0)
      enemyToHero(player,enemigo);
    else{
      enemigo=createEnemy(enemigo);
    }
  }
  else
    cout<<"ERROR: special not avaliable"<<endl;
}

void report(const Hero &player){
  int totalKills=0;
  cout<<"[Report]"<<endl;
  cout<<"Name: "<<player.name<<endl;
  cout<<"Attack: "<<player.features.attack<<endl;
  cout<<"Defense: "<<player.features.defense<<endl;
  cout<<"Health points: "<<player.features.hp<<endl;
  cout<<"Special: ";
  if(player.special)
    cout<<"yes";
   else
     cout<<"no";
   cout<<endl;
   cout<<"Runaways: "<<player.runaways<<endl;
   cout<<"Exp: "<<player.exp<<endl;
   cout<<"Enemies killed:"<<endl;
   cout<<"- Axolotl: "<<player.kills[0]<<endl;
   cout<<"- Troll: "<<player.kills[1]<<endl;
   cout<<"- Orc: "<<player.kills[2]<<endl;
   cout<<"- Hellhound: "<<player.kills[3]<<endl;
   cout<<"- Dragon: "<<player.kills[4]<<endl;
   cout<<"- Total: ";
   for(int j=0;j<5;j++){
     totalKills=totalKills+player.kills[j];
   }
   cout<<totalKills<<endl;
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


char menu(Hero &player,Enemy &enemigo,bool &runawayAvailable){
char op='q';
do{
  if(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='q')
    cout<<"ERROR: wrong option"<<endl;
  showMenu();
  cin>>op;
  }while(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='q');
  
  switch(op){
    case '1':
    fight(player,enemigo,runawayAvailable);
    break;
    case '2':
    runaway(player,enemigo,runawayAvailable);
    break;
    case '3':
    special(player,enemigo);
    break;
    case '4':
    report(player);
    break;
    case 'q':
    break;
  }
  return op;
}

int main(int argc,char *argv[]){
  Hero player;
  Enemy enemigo;
  char op;
  bool runawayAvailable=true;
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
    
  player=createHero(player);
  enemigo=createEnemy(enemigo);
  do{
  op=menu(player,enemigo,runawayAvailable);
  }while(player.features.hp>0 && op!='q');
  if(op!='q'){
    cout<<"You are dead"<<endl;
    report(player);	
  }
    
  }
}
