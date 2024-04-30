#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
const int BUFF_SIZE = 100;
char password[BUFF_SIZE];
char passwordSavingFileName[] = "fileSave/passwordSaving.temp";

void menu(void){
    cout << "******** PASSWORD MANAGEMENT ******** \n";
    cout << "1. Print menu \n";
    cout << "2. Change Password \n";
    cout << "3. Add new password \n";
    cout << "4. Delete your password \n";
    cout << "5. Show all password \n";
    cout << "0. Quit \n";  
    cout << "---------------------------------\n" ;
}

void copyBinaryFile(char* fileInName, char* fileOutName){
    fstream fileIn(fileInName, ios::in | ios::binary);
    if (!fileIn.is_open()){
        cout << "Can not open file !!!";
        return;
    }
    fstream fileOut(fileOutName, ios::out | ios::binary);
    if (!fileOut.is_open()){
        cout << "Can not open file !!!";
        return;
    }
    char *buff = new char [BUFF_SIZE];
    fileIn.seekg(0,ios::end);
    int numOfBytes = fileIn.tellg();
    fileIn.seekg(0,ios::beg);
    
    while(numOfBytes > BUFF_SIZE){
        numOfBytes -= BUFF_SIZE;
        fileIn.read(buff,BUFF_SIZE);
        fileOut.write(buff,BUFF_SIZE);
    }
    if (numOfBytes > 0){
        fileIn.read(buff,numOfBytes);
        fileOut.write(buff,numOfBytes);
    }    
    delete buff;
    fileIn.close();
    fileOut.close();
}

void readFiles(char *fileName){
    fstream fileIn(fileName, ios::in);
    if (!fileIn.is_open()){
        cout << "Can not open temp file !!! \n";
        return;
    }
    fileIn.seekg(0,ios::end);
    int numOfBytes = fileIn.tellg();
    fileIn.seekg(0,ios::beg);
    char *buff = new char [numOfBytes];
    fileIn.read(buff,numOfBytes);
    for (int i = 0; buff[i] != '\0'; ++i){
        password[i] = buff[i];
    }
    delete buff;
    fileIn.close();
}

void writeFiles(char* content, char *fileName){
    fstream fileOut(fileName, ios::out);
    if (!fileOut.is_open()){
        cout << "Can not open temp file !!! \n";
        return;
    }
    fileOut.write(content, BUFF_SIZE);
    fileOut.close();
}

bool cmpString(char* a, char* b){
    if (strlen(a) != strlen(b)) return false;
    for (int i = 0; a[i] != '\0'; ++i){
        if (a[i] != b[i]) return false;
    }
    return true;
}

void logIn(void){
    bool isLogIn = false;
    readFiles(passwordSavingFileName);
    while(isLogIn == false){
        char tmp[BUFF_SIZE];
        cout << "Please enter your password: ";
        cin.getline(tmp,BUFF_SIZE);
        if (cmpString(tmp,password)) isLogIn = true;
    }
}

void myProgram(void){
    bool running = true;
    int type;
    while(running){
        cout << "Please enter your choice: ";
        cin >> type;
        if (type == 1) menu();
        else if (type == 2){
            char tmp[BUFF_SIZE];
            cout << "Enter your new password: \n";
            cin.getline(tmp,BUFF_SIZE);
            writeFiles(tmp, passwordSavingFileName);
        }
        else if (type == 3){
            char tmp[BUFF_SIZE];
            cout << "Name the password for: ";
            cin.getline(tmp,BUFF_SIZE);
            cout << "Enter the password: ";
               
        }
        else if (type == 4){

        }
        else if (type == 5){

        }
        else{
            running = false;
        }
    }
}

int main(){
    logIn();
    menu();
    myProgram();
}