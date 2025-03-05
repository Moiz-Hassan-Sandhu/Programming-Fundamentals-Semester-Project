#include<iostream>
#include<fstream>
#include<iomanip>
#include<ctime>
#include<cstdlib>
extern char username[100];
using namespace std;

void mainMenu();
bool Signin(char []);
bool passStrength(char []);
bool isValidLenght(char[]);
bool hasUpperCase(char[]);
bool hasDigit(char[]);
bool userexist(char [], char []);
bool login( char []);
bool validatePass(char [], char [], char []);
bool isArraySame(char [], char []);
void copyarray(char arr1[], const char arr2[]);
int matchId(int pId, int c, int id[110]);
char* encrypt(char* pass);
char* decrypt(char* pass);
int generateOTP();
bool verifyOTP(int, int);
void printHeader();