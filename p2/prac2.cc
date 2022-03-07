// Programación 2 - Práctica 2
// DNI: 50504264J
// Nombre: Samuel Padilla Belvis

#include <iostream>
#include <vector>
#include <cctype>
#include <cstring>

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
  
  for(unsigned i=0;i<titulo.size();i++){
    if(titulo[0]=='-'){
      for(unsigned j=0;j<titulo.size();j++){
        titulo[j]=titulo[j+1];
        titulo[j+1]=' ';
      }
    }
    if(isalpha(titulo[i])!=0)
      titulo[i]=tolower(titulo[i]);
    else if(isalnum(titulo[i])==0){
      titulo[i]='-';
      }
  }
  
  for(unsigned h=0;h<titulo.size();h++){
    if(titulo[h]=='-' && titulo[h+1]=='-'){
      for(unsigned b=h;b<titulo.size();b++){
        titulo[b]=titulo[b+1];
      }
      h--;
    }
  }
  
  for(int l=titulo.size();l>=0;l--){
    if(isalnum(titulo[l])!=0)
      break;
    else if(titulo[l]=='-')
       titulo[l]=' ';
  }
  /*string slug;
  for(unsigned c=0;c<titulo.size();c++){
    if(isalpha(titulo[c])!=0 || isalnum(titulo[c])!=0 || titulo[c]=='-')
      slug[c]=titulo[c];
    cout<<titulo[c];
  }
  //strcpy(titulo,slug);
  cout<<slug<<endl;*/
  return titulo;
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
  for(unsigned i=0;i<bookStore.nextId-1;i++){
    if(bookStore.books[i].year!=0)
      cout<<bookStore.books[i].id<<". "<<bookStore.books[i].title<<" ("<<bookStore.books[i].year<<"), "<<bookStore.books[i].price<<endl;
  }
}

void showExtendedCatalog(const BookStore &bookStore) {
  for(unsigned i=0;i<bookStore.nextId-1;i++){
    if(bookStore.books[i].year!=0){
      cout<<'"'<<bookStore.books[i].title<<'"'<<','<<'"'<<bookStore.books[i].authors<<'"'<<','<<bookStore.books[i].year<<','<<'"';
      for(unsigned j=0;j<bookStore.books[i].slug.length();j++){
        if(isalnum(bookStore.books[i].slug[j])!=0)
          cout<<bookStore.books[i].slug[j];
      }
      cout<<'"'<<','<<bookStore.books[i].price<<endl;
    }
  }
}

void addBook(BookStore &bookStore) {
  Book libro;
  libro.id=bookStore.nextId;
  bookStore.nextId++;
  string yearS,priceS;
  do{
    cout<<"Enter book title: ";
    getline(cin,libro.title);
    if(errorName(libro.title))
      error(ERR_BOOK_TITLE);
  }while(errorName(libro.title));
  
  do{
    cout<<"Enter author(s): ";
    getline(cin,libro.authors);
    if(errorName(libro.authors))
      error(ERR_BOOK_AUTHORS);
  }while(errorName(libro.authors));
  
  do{
    
    cout<<"Enter publication year: ";
    getline(cin,yearS);
    
    if(yearS.size()!=0)
      libro.year=stoi(yearS);
    if (yearS.size()==0 || libro.year<1440 || libro.year>2022)
      error(ERR_BOOK_DATE);
  }while(yearS.size()==0 || libro.year<1440 || libro.year>2022);
  
  do{
    cout<<"Enter price: ";
    getline(cin,priceS);
    if(priceS.size()!=0)
      libro.price=stof(priceS);
      
    if (priceS.size()==0 || libro.price<0)
      error(ERR_BOOK_PRICE);
  }while(priceS.size()==0 || libro.price<0);
  
  libro.slug=generarSlug(libro.title);
  
  bookStore.books.push_back(libro);
}

void deleteBook(BookStore &bookStore) {
  bool erasedBook=false;
  unsigned int id;
  string idS;
  cout<<"Enter book id: ";
  getline(cin,idS);
  if(idS.size()==0)
    error(ERR_ID);
  else{
    id=stoi(idS);
    for(unsigned i=0;i<bookStore.nextId-1;i++){
      if(id==bookStore.books[i].id && bookStore.books[i].year!=0){
        erasedBook=true;
        bookStore.books[i].title="";
        bookStore.books[i].authors="";
        bookStore.books[i].year=0;
        bookStore.books[i].slug="";
        bookStore.books[i].price=0;
      }
    }
    if(!erasedBook)
      error(ERR_ID);
  }
}

void importExportMenu(BookStore &bookStore) {
  cout << "[Import/export options]" << endl
       << "1- Import from CSV" << endl
       << "2- Export to CSV" << endl
       << "3- Load data" << endl	
       << "4- Save data" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
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
















