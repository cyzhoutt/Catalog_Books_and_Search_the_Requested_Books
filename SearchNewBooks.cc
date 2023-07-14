#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <chrono>
#include <algorithm>

//class Clock{
// public:
  std::chrono::high_resolution_clock::time_point start(){
    std::chrono::high_resolution_clock::time_point startTime;
    startTime = std::chrono::high_resolution_clock::now();
    return startTime;
  }
  void stop(std::chrono::high_resolution_clock::time_point startTime){
    std::chrono::high_resolution_clock::time_point stopTime;
    stopTime = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>(stopTime - startTime).count();
    std::cout << "CPU time: " << elapsed_us << " microseconds";
  }
//};

char get_valid_char(const std::string& prompt) {
  std::string line;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, line); //grabs the entire line
    std::stringstream line2parse(line);
    char tempChoice;
    line2parse >> tempChoice;
    if (line2parse) { //if I was able to read the number
      std::string what_is_left;
      line2parse >> what_is_left;
      if (not line2parse) { //if there is nothing left we will fail to read it
        return tempChoice;
      }
    }
  }
}


class Book{
 public:
  void setIsbn (int num) {
    isbn = num;
  }
  int getIsbn() const{
    return isbn;
  }
  void setLan(std::string lang){
    language = lang;
  }
  std::string getLan() const{
    return language;
  }
  void setType(std::string typ){
    type=typ;
  }
  std::string getTy() const{
    return type;
  }

 private:
  int isbn=0;
  std::string language=" ";
  std::string type=" ";

};

bool typeCompare(const std::string& lhs, const std::string& rhs){
  if(lhs=="new"&&rhs=="used"){
    return true;
  }
  if(lhs=="used"&&rhs=="digital"){
    return true;
  }
  if(lhs=="new"&&rhs=="digital"){
    return true;
  }
  else{return false;}
}

bool operator<(const Book& lhs,const Book& rhs){
  if(lhs.getIsbn() != rhs.getIsbn()){
    return (lhs.getIsbn() < rhs.getIsbn());
  }else {
    if(lhs.getTy() != rhs.getTy()) {
      return typeCompare(lhs.getTy(),rhs.getTy());
    }else{
      if(lhs.getLan() != rhs.getLan()){
        return (lhs.getLan() < rhs.getLan());
      }
    }
  }
  return false;
}

bool operator==(const Book& lhs,const Book& rhs){
  if(lhs.getIsbn()==rhs.getIsbn() && lhs.getLan()==rhs.getLan() && lhs.getTy()==rhs.getTy()){
    return true;
  }else{return false;}
}

int linearSearch(const Book& target, const std::vector<Book>& list){
  for (const auto & i : list){
    if (i==target){
      return 1;
    }
  }
  return 0;
}

int numLinear(const std::vector<Book>& listWant, const std::vector<Book>& listSearch){
  int numFindLin=0;
  int tempNumFindLin=0;
  for(const auto & i : listWant){
    tempNumFindLin = linearSearch(i, listSearch);
    numFindLin=tempNumFindLin+numFindLin;
  }
  return numFindLin;
}

//implement
int binarySearch(const Book& target, const std::vector<Book>& list){
  // int totalNum = list.size();
  // int tempStart =0;
  int i=0;
  int j=list.size();
  while(i < j) {
    int m = (i + j) / 2;
    if (list[m] < target) {
      i = m + 1;
    } else {
      j = m;
    }
  }
  if(target==list[i]){
    return 1;
  }else{
    return 0;
  }
}


int numBinary(const std::vector<Book>& listWant, const std::vector<Book>& listSearch){
  int numFindLin=0;
  int tempNumFindLin=0;
  for(const auto & i : listWant){
    tempNumFindLin = binarySearch(i, listSearch);
    numFindLin=tempNumFindLin+numFindLin;
  }
  return numFindLin;
}

//implement
int reBinarySearch(const Book& target,const int& s, const int& e, const std::vector<Book>& list){
  int i=s;
  int j=e;
  const Book want = target;
  const std::vector<Book> search = list;
  if(i<j){
    int m = (i+j)/2;
//    if(list[m]==target){
//      return 1;
//    }
    if (list[m]<target) {
      i = m + 1;
      return reBinarySearch(want, i, j, search);
    }else{
      j=m;
      return reBinarySearch(target, i, j, list);
    }
  }else{
    if(list[i]==target){
      return 1;
    }else{
    return 0;
    }
  }
}

int numReBinary(const std::vector<Book>& listWant, const std::vector<Book>& listSearch){
  int numFindLin=0;
  int tempNumFindLin=0;
  for(const auto & i : listWant){
    tempNumFindLin = reBinarySearch(i,0,listSearch.size(), listSearch);
    numFindLin=tempNumFindLin+numFindLin;
  }
  return numFindLin;
}

int main(int argc, char** argv) {
  std::ifstream inFile;
  int Isnum;
  std::string lan;
  std::string ty;
  std::string templine;
  std::vector<Book> newBook;
  std::vector<Book> requiredBook;

  inFile.open(argv[1]);
  if (!inFile.is_open()) {
    return 1;
  }
  //inFile >> word;
  if(inFile){
//    while(inFile >> Isnum >> lan >> ty){
    inFile >> Isnum;
      do{
        std::getline(inFile, templine);
        std::stringstream line(templine);
        std::getline(line, templine, ',');
        std::getline(line, templine, ',');
        lan = templine;
        std::getline(line, templine, '\n');
        ty = templine;
        Book tempBook;
        tempBook.setIsbn(Isnum);
        tempBook.setLan(lan);
        tempBook.setType(ty);
        newBook.push_back(tempBook);
      }while(inFile >> Isnum);
    inFile.close();
  }


  inFile.open(argv[2]);
  if (!inFile.is_open()) {
    return 1;
  }
  if(inFile){
//    while(inFile >> Isnum >> lan >> ty){
    inFile >> Isnum;
    do{
      std::getline(inFile, templine);
      std::stringstream line(templine);
      std::getline(line, templine, ',');
      std::getline(line, templine, ',');
      lan = templine;
      std::getline(line, templine, '\n');
      ty = templine;
      Book tempBook;
      tempBook.setIsbn(Isnum);
      tempBook.setLan(lan);
      tempBook.setType(ty);
      requiredBook.push_back(tempBook);
    }while(inFile >> Isnum);
    inFile.close();
  }

//  Clock time;

//  std::chrono::high_resolution_clock::time_point start;
//  start = std::chrono::high_resolution_clock::now();



  char choice=' ';
  do {
    choice = get_valid_char("Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary)?\n");
  }while(!(choice=='l'||choice=='b'||choice=='r'));

  std::chrono::high_resolution_clock::time_point beginTime = start();

  int finalNum = 0;
  if(choice=='l'){
    finalNum= numLinear(requiredBook,newBook);
  }
  else if(choice=='b'){
    std::sort(newBook.begin(),newBook.end());
    std::sort(requiredBook.begin(),requiredBook.end());
    finalNum = numBinary(requiredBook,newBook);
  }
  else {
    std::sort(newBook.begin(),newBook.end());
    std::sort(requiredBook.begin(),requiredBook.end());
    finalNum = numReBinary(requiredBook,newBook);
  }

  stop(beginTime);

  if(argc==3){ //must use argc to check, can't use .open if the string is null
//    std::cout << "inside"<<std::endl;
    std::ofstream resultFile("found.dat");//can't write mode here
    resultFile << finalNum;
    resultFile.close();
  }else{
    std::ofstream resultFile;
    resultFile.open(argv[3]);
    if (resultFile.is_open()) {
      resultFile << finalNum;
      resultFile.close();
    }else{
      return 1;
    }
  }
  return 0;
}
