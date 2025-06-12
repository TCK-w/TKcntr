/*
 *  Tool for counting repeated elements.
 *
 *  gcc --version：gcc (Debian 10.2.1-6) 10.2.1 20210110
 *  Created on: 1/25/2024
 *  Author: TCK
 */

#ifndef WAVECNT_H_
#define WAVECNT_H_

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class WAVECNT{
private:
    void* WAVECNT_impl;
public:
    WAVECNT();
    ~WAVECNT();
	void debug(bool mode);
	void setPN(string allPN,const vector<string>& HiPN);
	vector<int> getPN();
	WAVECNT& input(const vector<string>& wave);
	WAVECNT& input(const vector<int>& wave);
	WAVECNT& input(const vector<double>& wave);
	vector<int> getCNT(int PN=0);
	void clear();
};

#endif /* WAVECNT_H_ */