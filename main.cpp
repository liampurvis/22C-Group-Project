//
//  main.cpp
//  Team Project 22C
//
//  Created by Liam Purvis on 2/18/15.
//  Copyright (c) 2015 Liam Purvis. All rights reserved.
//

#include <iostream>
#include <string>
#include "AdsMocking2016Race.h"
#include <fstream>
#include "UndoDeleteStack.h"

using namespace std;

typedef AdsMocking2016Race* PTR_ADS;

void welcomeFunction(); // welcomes user to the program
bool openInputFile(ifstream &ifs);                                                    // Function opens input File
void readInData(HashLP<PTR_ADS> &, BinarySearchTree<PTR_ADS> &, ifstream &inputFile); // Function reads in data from file,
                                                                            // and assigns it to both the BST and the HashLP.
bool menu(HashLP<PTR_ADS>&, BinarySearchTree<PTR_ADS>&, UndoDeleteStack<PTR_ADS>&);      // Function displays menu and allows
                                                                            // user to choose options.
void addData();  // these are all options called from menu and are pretty self-explanatory
void deleteData();
void findAndDisplayData();
void listDataInHash();
void listDataInKey();
void printIndentedKey();
void printStatistics();
bool writeDataToFile();
void undoDelete();
void emptyTrash();
void quit();


// We try and keep main pretty skeletal
int main() {
    
    HashLP<PTR_ADS> adsHashLP; //declares HashLP
    BinarySearchTree<PTR_ADS> adsBST; // declares BST
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
    
    cout << "Thanks you for using our program. It is now closing.";
    
    
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
void readInData(HashLP<ItemType> &adsHashLP, BinarySearchTree<ItemType> &adsBST, ifstream &inputFile){
    
    string name, slogan, vStatistic; // names variables
    double stat;
    
    while (getline(inputfile,name)) { // gets variables
        getline(inputfile, slogan);
        getline(inputfile, vStatistic);
        inputfile >> stat;
        PTR_ADS holder; // creates object
        holder = new AdsMocking2016Race(string name, string slogan, string vStatistic, double stat); //dynamic object created

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
        
        switch (command) { // Switch siphons user off to their choice
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
                printStatistics(adsHashLP, adsBST, trash);
                break;
            case 8:
                undoDelete(adsHashLP, adsBST, trash);
                break;
            case 9:
                emptyTrash(trash)
                break;
            case 10:
                writeDataToFile(adsBST);
                break;
            case 11:
                return true;
        }

    }
    
}





