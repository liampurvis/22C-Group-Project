//
//  main.cpp
//  Team Project 22C
//
//  Created by Liam Purvis on 2/18/15.
//  Copyright (c) 2015 Liam Purvis. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "UndoDeleteStack.h"
#include "BinarySearchTree.h"
#include "HashLP.h"
#include "AdsMocking2016Race.h"


using namespace std;

typedef AdsMocking2016Race* PTR_ADS;

void welcomeFunction(); // welcomes user to the program
bool openInputFile(ifstream &ifs);                                                    // Function opens input File
void readInData(HashLP<PTR_ADS> &, BinarySearchTree<PTR_ADS> &, ifstream &inputFile); // Function reads in data from file,
                                                                            // and assigns it to both the BST and the HashLP.
bool menu(HashLP<PTR_ADS>&, BinarySearchTree<PTR_ADS>&, UndoDeleteStack<PTR_ADS>&);      // Function displays menu and allows
                                                                            // user to choose options.
void addData(HashLP<PTR_ADS>&, BinarySearchTree<PTR_ADS>&);  // these are all options from menu and are pretty self-explanatory
void deleteData (HashLP<PTR_ADS>&, BinarySearchTree<PTR_ADS>&, UndoDeleteStack<PTR_ADS>&);
void findAndDisplayData (HashLP<PTR_ADS>& );
void listDataInHash (HashLP<PTR_ADS>&);
void listDataInKey(BinarySearchTree<PTR_ADS>&);
void printIndentedKey(BinarySearchTree<PTR_ADS>&);
void printStatistics(HashLP<PTR_ADS>&);
bool writeDataToFile(BinarySearchTree<PTR_ADS>&, UndoDeleteStack<PTR_ADS> trash);
void emptyTrash(UndoDeleteStack<PTR_ADS> trash);
void undoDelete(HashLP<PTR_ADS>&, BinarySearchTree<PTR_ADS>&, UndoDeleteStack<PTR_ADS>&);
void quit(UndoDeleteStack<PTR_ADS> trash);

int compareNames (const PTR_ADS &left, const PTR_ADS &right);                           //function that compares objects
void displayPTR_ADS (PTR_ADS &toDisplay);
int HashName(const PTR_ADS & adsMocking2016Race);




// We try and keep main pretty skeletal
int main() {
    
    HashLP<PTR_ADS> adsHashLP(HashName, compareNames); //declares HashLP
    BinarySearchTree<PTR_ADS> adsBST(compareNames); // declares BST
    UndoDeleteStack<PTR_ADS> trash;
    
    ifstream inputFile; // declares file object
    if (!openInputFile( inputFile ) ) { // tests/ checks that file opens
        cout << "Unable to open the input file\n";
        return -1;
    }
    
    readInData(adsHashLP, adsBST, inputFile); //reads in data from file into dynamically allocated object and sends it to
                                              //HashLP and BST
    inputFile.close(); // Closes input file
    
    menu(adsHashLP, adsBST, trash);
    
    cout << "Thank you for using our program. It is now closing.";
    
    
    return 0;
}
//      **********************************************************
//      Functions listed in order called from main or sub-fuctions:
//      **********************************************************

// welcomes user to the program
void welcomeFunction() {
    cout << "Welcome to Kartik Vats', Vinitra Swami's, and Liam Purvis' CIS 22C Final Project program." << endl;
    cout << "You will be guided through the process of opening a file with mock-2016-presidential-race advertisements, " << endl;
    cout << "you will be able to choose how to manipulate the data, " << endl;
    cout << "and then the program will allow you to print out the altered advertisements to another file. " << endl;
    cout << "Thank you for taking the time to play with our team project." << endl;
}

//reads in data from file into dynamically allocated object and sends it to HashLP and BST
bool openInputFile(ifstream &ifs)
{
    string filename;
    //filename = "/Users/davisdulin/Documents/22C/Homework #1 CIS 22B/Homework #1 CIS 22B/test1.txt";
    //Needed for Xcode!
    
    cout << "Enter the input filename: ";
    getline(cin, filename);
    ifs.open(filename.c_str());
    return ifs.is_open();
}


// Function reads in data from file, and assigns it to both the BST and the HashLP.
void readInData(HashLP<PTR_ADS> &adsHashLP, BinarySearchTree<PTR_ADS> &adsBST, ifstream &inputFile){
    
    string name, slogan, vStatistic; // names variables
    double stat;
    
    while (getline(inputFile,name)) { // gets variables
        getline(inputFile, slogan);
        getline(inputFile, vStatistic);
        inputFile >> stat;
        PTR_ADS holder; // creates object
        holder = new AdsMocking2016Race(name, slogan, vStatistic, stat); //dynamic object created

        adsHashLP.insert(holder); // inserts into HashLP
        adsBST.insert(holder); // inserts into BST
    }
    
}

// Function displays menu and allows user to choose options.

bool menu(HashLP<PTR_ADS> &adsHashLP, BinarySearchTree<PTR_ADS> &adsBST, UndoDeleteStack<PTR_ADS> &trash) {
    
    int command = -1; // variable that the user enters
    
    cout << "**********************************     Welcome to the menu function      ******************************" << endl;
    cout << "*****************     Listed below are the data manipulations you have at your disposal     ***********" << endl;
    cout << "********************     Please enter the number associated with the options below     ****************" << endl;
    cout << endl;
    cout << "1) To add an advertisement please enter...............................................................1" << endl;
    cout << "2) To move an advertisement to the trash please enter.................................................2" << endl;
    cout << "3) To find and display an advertisement please enter..................................................3" << endl;
    cout << "4) To see the advertisements printed in the Hash table order please enter.............................4" << endl;
    cout << "5) To see the advertisements printed in alphabetial order by candidates name please enter.............5" << endl;
    cout << "6) To see the advertisements printed in the indented Binary Search tree structure please enter........6" << endl;
    cout << "7) To see the statistics regarding this program's data structure efficiency please enter..............7" << endl;
    cout << "8) To put the item from the top of the trash back into the data structures please enter...............8" << endl;
    cout << "9) To empty the trash please enter....................................................................9" << endl;
    cout << "10) To write the data to an external file please enter...............................................10" << endl;
    cout << "11) To quit this program please enter................................................................11" << endl;
    
    while (command != 11){
        cin >> command;
        
        while (command < 1 || command > 11){ // Idiot-proofing while-loop
            cout << "Oops! Unreadable input, please enter a number between 1-11:" << endl;
            cin >> command;
        }
        
        switch (command) { // Switch siphons user off to their choice of data manipulation
            case 1:
                addData(adsHashLP, adsBST);
                break;
            case 2:
                deleteData(adsHashLP, adsBST, trash);
                break;
            case 3:
                findAndDisplayData(adsHashLP);
                break;
            case 4:
                listDataInHash(adsHashLP);
                break;
            case 5:
                listDataInKey(adsBST);
                break;
            case 6:
                printIndentedKey(adsBST);
                break;
            case 7:
                printStatistics(adsHashLP);
                break;
            case 8:
                undoDelete(adsHashLP, adsBST, trash);
                break;
            case 9:
                emptyTrash(trash);
                break;
            case 10:
                writeDataToFile(adsBST, trash);
                break;
            case 11:
                return true;
        }
        cout << "Please enter your next command." << endl;
    }
    return false;
}

void addData(HashLP<PTR_ADS &adsHashLP, BinarySearchTree<PTR_ADS> &adsBST){
    
    string name, slogan, vStatistic; // names variables
    double stat;
    
    cout << "You have chose to add a new advetisement." << endl;
    cout << "Please enter the name of the politicain: " << endl;
    getline(cin, name);
    cout << "Please enter the politicians political slogan:" << endl;
    getline(cin, slogan);
    cout << "Please enter the misleading statistical fact for the advertisement: " << endl;
    getline(cin, vStatistic);
    cout << "Please enter the numerical statistic, with no % sign: " << endl;
    cin >> stat;
    
    AdsMocking2016Race *holder;
    holder = new AdsMocking2016Race(name, slogan, vStatistic, stat);
    
    adsHashLP->insert(holder);
    adsBST->insert(holder);

}

void deleteData (HashLP<PTR_ADS &adsHashLP, BinarySearchTree<PTR_ADS> &adsBST, UndoDeleteStack<PTR_ADS> &trash) {
    
}

void findAndDisplayData (HashLP<PTR_ADS &adsHashLP){
    
}

void listDataInHash (HashLP<PTR_ADS &adsHashLP)
{
    adsHashLP->write(cout);
}

void listDataInKey(BinarySearchTree<PTR_ADS> &adsBST) {
    adsBST->_inorder(displayPTR_ADS);
    cout << endl;
}

void printIndentedKey(BinarySearchTree<PTR_ADS>& adsBST){
    adBST->print();
}

void printStatistics(HashLP<PTR_ADS& adsHashLP)
{
    adsHashLP->displayStatistics();
}

bool writeDataToFile(HashLP<PTR_ADS>& adsHashLP, UndoDeleteStack<PTR_ADS> trash)
{
       
        adsHashLP->write(file); //file is ostream of the text file we want to write to
}

void emptyTrash(UndoDeleteStack<PTR_ADS> trash){
    trash->clear();
}

void undoDelete(HashLP<PTR_ADS &adsHashLP, BinarySearchTree<PTR_ADS> &adsBST, UndoDeleteStack<PTR_ADS> &trash){
    
}

void quit(UndoDeleteStack<PTR_ADS> trash){
    emptyTrash(trash);
}



int compareNames (const PTR_ADS &left, const PTR_ADS &right) {
    if (left->getName() < right->getName())
        return -1;
    else if ( left->getName() == right->getName())
        return 0;
    else
        return 1;
}

void displayPTR_ADS (PTR_ADS &toDisplay) {
    toDisplay->writeAdsMocking2016Race(cout);
    cout << endl;
}



int HashName(const PTR_ADS & adsMocking2016Race)
{
    return HashString(AdsMocking2016Race->getName());
}

int HashString( const string & key )
{
    unsigned int k, retVal = 0;
    
    for(k = 0; k < key.length( ); k++ )
        retVal = 37 * retVal + key[k];
    
    
    return retVal;
}






