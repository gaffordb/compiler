#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("usage: driver <filename>");
  }
  ifstream infile;
  infile.open(argv[0]);
  if(infile.is_open()) {
    while(!infile.eof()) {
      cout << infile;
    }
  }
  infile.close();
}
