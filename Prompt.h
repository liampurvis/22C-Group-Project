//
//  Prompt.h
//  File IO
//
//  Created by Kartik Vats on 3/11/15.
//  Copyright (c) 2015 Kartik Vats. All rights reserved.
//

#ifndef File_IO_Prompt_h
#define File_IO_Prompt_h

#include <iostream>
#include <string>
#include<fstream>
using namespace std;

class Prompt
{
public:
    void promptForInputFile(ifstream& inputStream);
    void promptForOutputFile(ofstream& outputStream);
    string promptForCommand();
    
};

void Prompt::promptForInputFile(ifstream & inputStream) //function that takes in the reference of an ifstream and will prompt the user for a file name and then will try to open the file.
{
    string file;
    cout<<endl<<"Enter the input file name: ";
    getline(cin, file);
    string directory = "/Users/Kartik/Desktop/Kartik/School/De Anza/Winter Quarter/CIS 22C/Assignment 1/Assignment 1/";
    directory += file;
    inputStream.open(directory.c_str());
}

void Prompt::promptForOutputFile(ofstream& outputStream) //function that takes in the reference of an ofstream and will prompt the user for a file name and then create/open the file.
{
    string file;
    cout<<endl<<"Enter the output file name: ";
    getline(cin,file);
    string directory = "/Users/Kartik/Desktop/Kartik/School/De Anza/Winter Quarter/CIS 22C/Assignment 1/Assignment 1/";
    directory += file;
    outputStream.open(directory.c_str());
}

string Prompt::promptForCommand()
{
    string file;
    cout<<endl<<"Enter a command: ";
    getline(cin,file);
    return file;
}

//Vinitra's getFile function
//**************************************************************
// Definition of function getFile:
// This function inputs the user's desired data file name or
// accepts the default file of "HW3 input.txt".
//**************************************************************
//string getFile()
//{
//
//	string fileName;
//	std::string exten = ".txt";
//
//	cout << "Welcome! What is the name of the input file you want to use?" << endl;
//	cout << "If the file name is 'HW3 Input' then press enter." << endl;
//	getline(cin, fileName);
//
//	if (fileName.empty())  //set default file to HW1 input.txt
//		fileName = "HW3 Input";
//	else
//		cout << endl;
//
//	fileName += exten;  //concatenate file name with extension
//
//	return fileName;
//}


#endif
