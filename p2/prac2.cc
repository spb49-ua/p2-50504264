// Programación 2 - Práctica 2
// DNI: 50504264J
// Nombre: Samuel Padilla Belvis

#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

const int KMAXSTRING = 50;

enum Error {
  ERR_OPTION,
  ERR_BOOK_TITLE,
  ERR_BOOK_AUTHORS,
  ERR_BOOK_DATE,
  ERR_BOOK_PRICE,
  ERR_ID,
  ERR_FILE,
  ERR_ARGS
};

struct Book {
  unsigned int id;
  string title;
  string authors;
  int year;
  string slug;
  float price;
};

struct BinBook {
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
};

struct BookStore {
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBookStore {
  char name[KMAXSTRING];
  unsigned int nextId;
};

void error(Error e) {
  switch (e) {
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_BOOK_TITLE:
      cout << "ERROR: wrong book title" << endl;
      break;
    case ERR_BOOK_AUTHORS:
      cout << "ERROR: wrong author(s)" << endl;
      break;
    case ERR_BOOK_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_BOOK_PRICE:
      cout << "ERROR: wrong price" << endl;
      break;
    case ERR_ID:
      cout << "ERROR: wrong book id" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
      break;
  }
}

bool errorName(string palabra){
  if(palabra.size()==0)
  	return true;
  for(unsigned i=0;i<palabra.size();i++){
    if ( palabra[i]!='-' && palabra[i]!=':' && palabra[i]!=' ' && palabra[i]!=',' && isalnum(palabra[i])==0 )
    	return true;
  }
  
  return false;
}

string generarSlug(string titulo){
  string slug;
  
  for(unsigned i=0;i<titulo.size();i++){
    if(titulo[0]=='-'){
      for(unsigned j=0;j<titulo.size();j++){
        titulo[j]=titulo[j+1];
        titulo[j+1]=' ';
      }
    }
    if(isalpha(titulo[i])!=0)
      titulo[i]=tolower(titulo[i]);
    else if(isalnum(titulo[i])==0)
      titulo[i]='-';
    
    if(titulo[i-1]=='-' && titulo[i]=='-'){
      for(unsigned k=i-1;k<titulo.size();k++){
        titulo[k-1]=titulo[k];
        titulo[k]=' ';
      }
    }
  }
  
  for(unsigned l=titulo.size();l>=0;l--){
    if(isalnum(titulo[l])!=0)
      break;
    else if(titulo[l]=='-')
       titulo[l]=' ';
  }
  
  slug=titulo;
  cout<<slug<<endl;
  return slug;
}

void showMainMenu() {
  cout << "[Options]" << endl
       << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl
       << "3- Add book" << endl	
       << "4- Delete book" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void showCatalog(const BookStore &bookStore) {

}

void showExtendedCatalog(const BookStore &bookStore) {
}

void addBook(BookStore &bookStore) {
  string titulo,author,slug;
  string yearS,priceS;
  int year;
  float price;
  do{
    cout<<"Enter book title: ";
    getline(cin,titulo);
    if(errorName(titulo))
      error(ERR_BOOK_TITLE);
  }while(errorName(titulo));
  
  do{
    cout<<"Enter author(s): ";
    getline(cin,author);
    if(errorName(author))
      error(ERR_BOOK_AUTHORS);
  }while(errorName(author));
  
  do{
    
    cout<<"Enter publication year: ";
    getline(cin,yearS);
    
    if(yearS.size()!=0)
      year=stoi(yearS);
    if (yearS.size()==0 || year<1440 || year>2022)
      error(ERR_BOOK_DATE);
  }while(yearS.size()==0 || year<1440 || year>2022);
  
  do{
    cout<<"Enter price: ";
    getline(cin,priceS);
    
    if(priceS.size()!=0)
      price=stof(priceS);
      
    if (priceS.size()==0 || price<0)
      error(ERR_BOOK_PRICE);
  }while(priceS.size()==0 || price<0);
  
  slug=generarSlug(titulo);
}

void deleteBook(BookStore &bookStore) {
}

void importExportMenu(BookStore &bookStore) {
}

void importFromCsv(BookStore &bookStore){
}

void exportToCsv(const BookStore &bookStore){
}

void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}

int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;

  char option;
  do {
    showMainMenu();
    cin >> option;
    cin.get();

    switch (option) {
      case '1':
        showCatalog(bookStore);
        break;
      case '2':
        showExtendedCatalog(bookStore);
        break;
      case '3':
        addBook(bookStore);
        break;
      case '4':
        deleteBook(bookStore);
        break;
      case '5':
        importExportMenu(bookStore);
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}
















