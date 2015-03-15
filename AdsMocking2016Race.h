//
//  AdsMocking2016Race.h
//  Team Project 22C
//
//  Created by Davis Dulin on 2/18/15.
//  Copyright (c) 2015 Liam Purvis. All rights reserved.
//ATTEMPT!!!!!!

#ifndef __Team_Project_22C__AdsMocking2016Race__
#define __Team_Project_22C__AdsMocking2016Race__

#include <stdio.h>
#include <iostream>

using namespace std;

class AdsMocking2016Race {
private:
    string name;
    string slogan;
    string misleadingStat;
    double statistic;
    
public:
    AdsMocking2016Race();
    AdsMocking2016Race(string n, string slo, string m, double stat)             //constructor
    {setName(n); setSlogan(slo); setMisleadingStat(m); setStatistic(stat);}
    void setName(string n) {name = n;}                                          //setters:
    void setSlogan(string s) {slogan = s;}
    void setMisleadingStat(string m) {misleadingStat = m;}
    void setStatistic(double s) {statistic = s;}
    string getName() const {return name;}                                       //getters:
    string getSlogan() const {return slogan;}
    string getMisledingStat() const {return misleadingStat;}
    double getStatistic() const {return statistic;}
    
    bool operator != (const AdsMocking2016Race &compAd) const{                  //operator overloaders of <,>, !=, <=, & >=:
        if (name != compAd.getName())
            return true;
        else
            return false;
    }
    
    bool operator <= (const AdsMocking2016Race &compAd) const{
        if (name <= compAd.getName())
            return true;
        else
            return false;
    }
    
    bool operator == (const AdsMocking2016Race &compAd) const{
        if (name == compAd.getName())
            return true;
        else
            return false;
    }
    bool operator >= (const AdsMocking2016Race &compAd) const{
        if (name >= compAd.getName())
            return true;
        else
            return false;
    }
    
    bool operator < (const AdsMocking2016Race &compAd) const{
        if (name < compAd.getName())
            return true;
        else
            return false;
    }
    
    bool operator > (const AdsMocking2016Race &compAd) const{
        if (name > compAd.getName())
            return true;
        else
            return false;
    }
    
    string write() const
    {
        string output = name + "\n" + slogan + "\n" + misleadingStat + " " + statistic;
        return output;
    }

};

#endif /* defined(__Team_Project_22C__AdsMocking2016Race__) */
