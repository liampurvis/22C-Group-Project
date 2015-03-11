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
    void promptForInput(ifstream& inputStream);
    void promptForOutput(ofstream& outputStream);
    
};

void Prompt::promptForInput(ifstream & inputStream) //function that takes in the reference of an ifstream and will prompt the user for a file name and then will try to open the file.
{
    string file;
    cout<<endl<<"Enter the input file name: ";
    getline(cin, file);
    string directory = "/Users/Kartik/Desktop/Kartik/School/De Anza/Winter Quarter/CIS 22C/Assignment 1/Assignment 1/";
    directory += file;
    inputStream.open(directory.c_str());
}

void Prompt::promptForOutput(ofstream& outputStream) //function that takes in the reference of an ofstream and will prompt the user for a file name and then create/open the file.
{
    string file;
    cout<<endl<<"Enter the output file name: ";
    getline(cin,file);
    string directory = "/Users/Kartik/Desktop/Kartik/School/De Anza/Winter Quarter/CIS 22C/Assignment 1/Assignment 1/";
    directory += file;
    outputStream.open(directory.c_str());
}


#endif
