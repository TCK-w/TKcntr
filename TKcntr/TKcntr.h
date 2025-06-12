/*
 *  Tool for TK container.
 *
 *  gcc --version：gcc (Debian 10.2.1-6) 10.2.1 20210110
 *  Created on: 3/17/2024
 *  Author: TCK
 */

#ifndef TKCNTR_H_
#define TKCNTR_H_
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class WT{
public:
	WT();
	~WT();
};

class TKR{
private:
	void* TKR_imp;
public:
	TKR(string& TK_name,vector<string>& item_s,vector<string>& item_i,vector<string>& item_d);
	~TKR();
	int len();
	vector<string> getString(string item_name);
	vector<int> getInt(string item_name);
	vector<double> getDouble(string item_name);
	string& getString(string item_name, int n);
	int& getInt(string item_name, int n);
	double& getDouble(string item_name, int n);
	bool find(string item_name);
	string err();
	bool state();
	void showItem();
};

class TKcntr{
private:
	void* TKcntr_imp;
public:
	TKcntr();
	~TKcntr();
	void setItem(string type, vector<string>& Item_name);// valid type: "String" or "Integer" or "Double"
	TKR& tkr(string tk_name);
	WT& wt(string subdie_name, int n);
	bool findWt(string subdie_name, int n);
};

#endif /* TKCNTR_H_ */