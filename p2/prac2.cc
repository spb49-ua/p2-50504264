// Programación 2 - Práctica 2
// DNI: 50504264J
// Nombre: Samuel Padilla Belvis

#include <iostream>
#include <vector>
#include <cctype>
#include <cstring>
#include <fstream>

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

enum Pedir {
  TITLE,
  AUTHORS,
  DATE,
  PRICE,
  ID,
  FILENAME
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

void pedir(Pedir p) {
  switch (p) {
    case TITLE:
      cout << "Enter book title: ";
      break;
    case AUTHORS:
      cout << "Enter author(s): ";
      break;
    case DATE:
      cout<<"Enter publication year: ";
      break;
    case PRICE:
      cout<<"Enter price: ";
      break;
    case ID:
      cout<<"Enter book id: ";
      break;
    case FILENAME:
      cout<<"Enter filename: ";
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

bool errorDate(string yearS,int year){
  if(yearS.size()==0 || year<1440 || year>2022)
    return true;
  else 
    return false;
}

string generarSlug(string titulo){
  string slug;
  bool ponerGuion=false;
  for(unsigned i=0;i<titulo.size();i++){
    if(isalnum(titulo[i])){
      slug+=tolower(titulo[i]);
      ponerGuion=true;
      }
    else if (ponerGuion && isalnum(titulo[i+1])){
      slug+='-';
      ponerGuion=false;
    }
  }
  return slug;
}

int tamanoFichero(string filename){
  string aux;
  int tamano=0;
  ifstream fichero(filename);
  while(!fichero.eof()){
    getline(fichero,aux);
    tamano++;
  }
  fichero.close();
  return tamano-1;
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
      cout<<'"'<<bookStore.books[i].title<<'"'<<','<<'"'<<bookStore.books[i].authors<<'"'<<','<<bookStore.books[i].year<<','<<'"'<<bookStore.books[i].slug<<'"'<<','<<bookStore.books[i].price<<endl;
    }
  }
}

void addBook(BookStore &bookStore) {
  Book libro;
  libro.id=bookStore.nextId;
  bookStore.nextId++;
  string yearS,priceS;
  do{
    pedir(TITLE);
    getline(cin,libro.title);
    if(errorName(libro.title))
      error(ERR_BOOK_TITLE);
  }while(errorName(libro.title));
  
  do{
    pedir(AUTHORS);
    getline(cin,libro.authors);
    if(errorName(libro.authors))
      error(ERR_BOOK_AUTHORS);
  }while(errorName(libro.authors));
  
  do{
    
    pedir(DATE);
    getline(cin,yearS);
    
    if(yearS.size()!=0)
      libro.year=stoi(yearS);
    if (errorDate(yearS,libro.year))
      error(ERR_BOOK_DATE);
  }while(errorDate(yearS,libro.year));
  
  do{
    pedir(PRICE);
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
  pedir(ID);
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
  Book book;
  bool nombreValido,autorValido,anoValido,precioValido;
  string filename,linea;
  unsigned int tam;
  string ano,precio;
  book.title="",book.authors="",book.year=0,book.slug="",book.price=0;
  pedir(FILENAME);
  getline(cin,filename);
  ifstream fichero;
  fichero.open(filename);
  if(!fichero.is_open())
    error(ERR_FILE);
  else{
    fichero.close();
    tam=tamanoFichero(filename);
    ifstream fichero(filename);
    for(unsigned j=0;j<tam;j++){
      getline(fichero,linea);
      int comillas=0;
      for(unsigned k=0;k<linea.length();k++){       
        if(linea[k]=='"')
          comillas++;
        switch(comillas){
          case 1:
            if(linea[k]!='"')
              book.title+=linea[k];
            break;
          case 3:
            if(linea[k]!='"')
              book.authors+=linea[k];
            break;
          case 4:
            if(linea[k]!=',' && linea[k]!='"')
              ano+=linea[k];
            break;
          case 5:
            if(linea[k]!='"')
              book.slug+=linea[k];
            break;
          case 6:
            if(linea[k]!=','  && linea[k]!='"')
              precio+=linea[k];
            break;
        }  
      }
      book.id=bookStore.nextId;
      bookStore.nextId++;
      nombreValido=!errorName(book.title);
      autorValido=!errorName(book.authors);
      book.year=stoi(ano);
      anoValido=!errorDate(ano,book.year);
      book.price=stof(precio);
      if(book.price>0)
        precioValido=true;
      else
        precioValido=false;
      if(nombreValido && autorValido && anoValido && precioValido)
        bookStore.books.push_back(book);
      else if (!nombreValido)
        error(ERR_BOOK_TITLE);
        else if(!autorValido)
          error(ERR_BOOK_AUTHORS);
          else if(!anoValido)
            error(ERR_BOOK_DATE);
            else
              error(ERR_BOOK_PRICE);
      book.title="";
      book.authors="";
      ano="";
      book.slug="";
      precio="";
    }
    fichero.close();
  }
}

void exportToCsv(const BookStore &bookStore){
  string filename;
  pedir(FILENAME);
  getline(cin,filename);
  ofstream fichero;
  fichero.open(filename);
  if(!fichero.is_open())
    error(ERR_FILE);
  else{
    for(unsigned int i=0;i<bookStore.nextId-1;i++){
      if(bookStore.books[i].year!=0)
      fichero<<'"'<<bookStore.books[i].title<<'"'<<','
      <<'"'<<bookStore.books[i].authors<<'"'<<','
      <<bookStore.books[i].year<<','
      <<'"'<<bookStore.books[i].slug<<'"'<<','
      <<bookStore.books[i].price<<endl;
    }
  }
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
        do{
          importExportMenu(bookStore);
          cin>>option;
          cin.get();
          switch (option) {
            case '1':
              importFromCsv(bookStore);
              break;
            case '2':
              exportToCsv(bookStore);
              break;
            case '3':
              loadData(bookStore);
              break;
            case '4':
              saveData(bookStore);
              break;
            case 'b':
              break;
            default:
              error(ERR_OPTION);
          }
        }while(option != 'b');
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}
















