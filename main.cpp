#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
const int BUFF_SIZE = 100;
char password[BUFF_SIZE];
char passwordSavingFileName[] = "fileSave/passwordSaving.temp";
char dataSavingFileName[] = "fileSave/data.temp";

struct Node{
    char name[BUFF_SIZE];
    char password[BUFF_SIZE];
    Node* prev;
    Node* nxt;
};

struct List{
    Node* head = NULL;
    Node* tail = NULL;
};
List L;

Node* createNode(char* NAME, char* PASSWORD){
    Node* newNode = new Node;
    if (newNode == NULL){
        cout << "Not enough data !!!";
        return NULL;
    }
    strcpy(newNode->name,NAME);
    strcpy(newNode->password,PASSWORD);
    newNode->prev = newNode->nxt = NULL;
    return newNode;    
}

void addNode(List& L, char* NAME, char* PASSWORD){
    Node* newNode = createNode(NAME,PASSWORD);
    if (L.head == NULL){
        L.head = L.tail = newNode;
    }
    else{
        newNode->prev = L.tail;
        L.tail->nxt = newNode;
        L.tail = newNode;
    }
}

void printListToScreen(List &L){
    cout << "------LIST PASSWORDS------\n";
    int cur = 0;
    for (Node* ptr = L.head; ptr; ptr = ptr->nxt){
        cout << cur++ <<". \n";
        cout << "Name: " << ptr->name <<'\n';
        cout << "Password: " << ptr->password <<'\n';
        cout << "-------------------------- \n \n";
    }
}

void printListToFile(char *fileName, List& L){
    fstream fileOut(fileName, ios::out | ios::binary);
    if (!fileOut.is_open()){
        cout << "Can not open file !!!";
        return;
    }
    for (Node* ptr = L.head; ptr; ptr = ptr->nxt){
        fileOut.write(ptr->name,BUFF_SIZE);
        fileOut.write(ptr->password,BUFF_SIZE);
    }
    fileOut.close();
}

int Length(List &L){
    int res = 0;
    for (Node* ptr = L.head; ptr; ptr = ptr->nxt){
        res++;
    }
    return res;
}

void deleteNode(List& L, int pos){
    if (pos > Length(L) - 1 || pos < 0) return;
    if (L.head == L.tail){
        L.head = L.tail = NULL;
    }
    else if (pos == 0){
        Node* tmp = L.head;
        L.head = tmp->nxt;
        L.head->prev = NULL;
        delete tmp;
    }
    else if (pos == Length(L) - 1){
        Node* tmp = L.tail;
        L.tail = tmp->prev;
        L.tail->nxt = NULL;
        delete tmp;
    }
    else{
        for (Node* ptr = L.head; ptr; pos--,ptr = ptr->nxt){
            if (pos == 0){
                ptr->prev->nxt = ptr->nxt;
                ptr->nxt->prev = ptr->prev;
                delete ptr;
                return;
            }
        }
    }
}

void destroyList(List &L){
    while(L.head){
        Node* tmp = L.head;
        L.head = L.head->nxt;
        delete tmp;
    }
}

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

void readFilePassword(char *fileName){
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

void readFileData(char *fileName){
    fstream fileIn(fileName, ios::in);
    if (!fileIn.is_open()){
        cout << "Can not open temp file !!! \n";
        return;
    }
    fileIn.seekg(0,ios::end);
    int numOfBytes = fileIn.tellg();
    fileIn.seekg(0,ios::beg);
    char name[BUFF_SIZE];
    char password[BUFF_SIZE];
    while(fileIn.tellg() != numOfBytes){
        fileIn.read(name,BUFF_SIZE);
        fileIn.read(password,BUFF_SIZE);
        addNode(L,name,password);
    }
    fileIn.close();
}

void writeFilePassword(char* content, char *fileName){
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
    readFilePassword(passwordSavingFileName);
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
            cout << "Enter your new password: ";
            cin.getline(tmp,BUFF_SIZE);
            cin.getline(tmp,BUFF_SIZE);
            writeFilePassword(tmp, passwordSavingFileName);
        }
        else if (type == 3){
            char tmp_name[BUFF_SIZE], tmp_pass[BUFF_SIZE];
            cout << "Name the password for: ";
            cin.getline(tmp_name,BUFF_SIZE);
            cin.getline(tmp_name,BUFF_SIZE);
            cout << "Enter the password: ";
            cin.getline(tmp_pass,BUFF_SIZE);
            addNode(L,tmp_name,tmp_pass);
        }
        else if (type == 4){
            int pos;
            cout << "Please enter ID password (start from 0): ";
            cin >> pos;
            deleteNode(L,pos);
        }
        else if (type == 5){
            printListToScreen(L);
        }
        else{
            running = false;
        }
    }
}

int main(){
    logIn();
    readFileData(dataSavingFileName);
    menu();
    myProgram();
    printListToFile(dataSavingFileName,L);
    destroyList(L);
}