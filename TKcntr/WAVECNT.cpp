/*
 *  Tool for counting repeated elements.
 *
 *  gcc --version：gcc (Debian 10.2.1-6) 10.2.1 20210110
 *  Created on: 1/25/2024
 *  Author: TCK
 */

#include<map>
#include<sstream>
#include "WAVECNT.h"

using namespace std;

class WAVECNT_IMPL{
private:
	bool mode = false;
	vector<int> diff;
	map<string,vector<int> > PNState;
    void* WAVECNT_impl;
public:
	void debug(bool mode){ this->mode=mode; }
	void setPN(string allPN,const vector<string>& HiPN){
        stringstream ss(allPN);
        string element;
        size_t len = HiPN.size();
        // get all PN
        this->PNState.clear();
        while(getline(ss, element, ',')){
            if(element.size()!=0){
                bool is_num = true;
                for(size_t i=0;i<element.size();i++){
                    if(!isdigit(element.at(i))){
                        is_num = false;
                        break;
                    }
                }
                if(is_num && element.compare("0")!=0){
                    vector<int> tmpState(len,0);
                    this->PNState.insert(pair<string,vector<int> > (element,tmpState));
                }
            }
        }
        // get Hi Low state
        if(this->mode==true){ cout<<"***** Set Hi Low PN Debug *****"<<endl; }
        int index;
        vector<string> get;
        map<string,vector<int> >::iterator itm;
        for(vector<string>::const_iterator it=HiPN.begin();it!=HiPN.end();it++){
            if(this->mode==true){ cout<<*it<<endl<<"Find: "; }
            stringstream ss(*it);
            index = it-HiPN.begin();
            get.clear();
            while(getline(ss, element, ',')){
                if(element.size()!=0){
                    for(itm=this->PNState.begin();itm!=this->PNState.end();itm++){
                        if((*itm).first.compare(element)==0){
                            (*itm).second.at(index)=1;
                            if(this->mode==true){ cout<<(*itm).first<<", "; }
                        }
                    }
                }
            }
            if(this->mode==true){ cout<<endl; }
        }
    }
	vector<int> getPN(){
        map<string,vector<int> >::iterator it;
        vector<int> PN;
        for(it=this->PNState.begin();it!=this->PNState.end();it++){ PN.push_back(stoi(it->first)); }
        return PN;
    }
	WAVECNT_IMPL& input(const vector<string>& wave){
        if(wave.size()!=0){
            if( this->diff.size()==0){this->diff.resize(wave.size(),0); }

            if(this->diff.size()==wave.size()){
                size_t index;
                if(this->mode==true){ cout<<"***** Input Debug *****"<<endl;}
                for(vector<string>::const_iterator it=wave.begin();it!=wave.end();it++){
                    if(wave.end()== it+1){
                        index = it-wave.begin();
                        this->diff.at(index)=1;
                        if(this->mode==true){ cout<<*it<<endl;}
                    }else{
                        if((*it).compare(*(it+1))!=0){
                            index = it-wave.begin();
                            this->diff.at(index)=1;
                            if(this->mode==true){ cout<<*it<<endl;}
                        }else{
                            if(this->mode==true){ cout<<*it<<", ";}
                        }
                    }
                }
            }
        }
        return *this;
    }
	WAVECNT_IMPL& input(const vector<int>& wave){
        if(wave.size()!=0){
            if( this->diff.size()==0){this->diff.resize(wave.size(),0); }

            if(this->diff.size()==wave.size()){
                size_t index;
                if(this->mode==true){ cout<<"***** Input Debug *****"<<endl;}
                for(vector<int>::const_iterator it=wave.begin();it!=wave.end();it++){
                    if(wave.end()== it+1){
                        index = it-wave.begin();
                        this->diff.at(index)=1;
                        if(this->mode==true){ cout<<*it<<endl;}
                    }else{
                        if(*it!= *(it+1)){
                            index = it-wave.begin();
                            this->diff.at(index)=1;
                            if(this->mode==true){ cout<<*it<<endl;}
                        }else{
                            if(this->mode==true){ cout<<*it<<", ";}
                        }
                    }
                }
            }
        }
        return *this;
    }
	WAVECNT_IMPL& input(const vector<double>& wave){
        if(wave.size()!=0){
            if( this->diff.size()==0){this->diff.resize(wave.size(),0); }

            if(this->diff.size()==wave.size()){
                size_t index;
                if(this->mode==true){ cout<<"***** Input Debug *****"<<endl;}
                for(vector<double>::const_iterator it=wave.begin();it!=wave.end();it++){
                    if(wave.end()== it+1){
                        index = it-wave.begin();
                        this->diff.at(index)=1;
                        if(this->mode==true){ cout<<*it<<endl;}
                    }else{
                        if(*it!= *(it+1)){
                            index = it-wave.begin();
                            this->diff.at(index)=1;
                            if(this->mode==true){ cout<<*it<<endl;}
                        }else{
                            if(this->mode==true){ cout<<*it<<", ";}
                        }
                    }
                }
            }
        }
        return *this;
    }
	vector<int> getCNT(int PN=0){
        vector<int> result;
        string PNs = to_string(PN);
        map<string,vector<int> >::iterator itm= this->PNState.find(PNs);
        if(itm==this->PNState.end()){ // No select PN
            int n=0;
            for(vector<int>::iterator it=this->diff.begin();it!=this->diff.end();it++){
                if(*it!= 0){
                    n++;
                    result.push_back(n);
                    n=0;
                }else{ n++; }
            }
            return result;
        }else{
            size_t index;
            vector<int> &PN_b = itm->second;
            if(this->diff.size()==0){ // Only setPN
                vector<int> diffp(PN_b.size(),0);
                for(vector<int>::iterator it=PN_b.begin();it!=PN_b.end();it++){
                    if(PN_b.end()== it+1){
                        index = it-PN_b.begin();
                        diffp.at(index)=1;
                    }else{
                        if(*it!= *(it+1)){
                            index = it-PN_b.begin();
                            diffp.at(index)=1;
                        }
                    }
                }
                // Count result
                int n=0;
                for(vector<int>::iterator it=diffp.begin();it!=diffp.end();it++){
                    if(*it!= 0){
                        n++;
                        if(PN_b.at(it-diffp.begin())==0){
                            result.push_back(n*-1);
                        }else{
                            result.push_back(n);
                        }
                        n=0;
                    }else{ n++; }
                }
            }
            if(this->diff.size()==itm->second.size()){ // Result of Input and PN
                vector<int> diffp = this->diff;
                for(vector<int>::iterator it=PN_b.begin();it!=PN_b.end();it++){
                    if(PN_b.end()== it+1){
                        index = it-PN_b.begin();
                        diffp.at(index)=1;
                    }else{
                        if(*it!= *(it+1)){
                            index = it-PN_b.begin();
                            diffp.at(index)=1;
                        }
                    }
                }
                // Count result
                int n=0;
                for(vector<int>::iterator it=diffp.begin();it!=diffp.end();it++){
                    if(*it!= 0){
                        n++;
                        if(PN_b.at(it-diffp.begin())==0){
                            result.push_back(n*-1);
                        }else{
                            result.push_back(n);
                        }
                        n=0;
                    }else{ n++; }
                }
            }
            return result;
        }
    }
	void clear(){ this->diff.clear(); }
};

WAVECNT::WAVECNT():WAVECNT_impl(nullptr){
    WAVECNT_impl = new WAVECNT_IMPL();
}

WAVECNT::~WAVECNT(){
    if(WAVECNT_impl!=nullptr){
        WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
        delete WAVECNT_impl_;
        WAVECNT_impl = nullptr;
    }
}

void WAVECNT::debug(bool mode){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
    WAVECNT_impl_->debug(mode);
    }

void WAVECNT::setPN(string allPN,const vector<string>& HiPN){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
    WAVECNT_impl_->setPN(allPN,HiPN);
}

vector<int> WAVECNT::getPN(){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
	return WAVECNT_impl_->getPN();
}

WAVECNT& WAVECNT::input(const vector<string>& wave){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
	WAVECNT_impl_->input(wave);
	return *this;
}

WAVECNT& WAVECNT::input(const vector<int>& wave){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
	WAVECNT_impl_->input(wave);
	return *this;
}

WAVECNT& WAVECNT::input(const vector<double>& wave){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
	WAVECNT_impl_->input(wave);
	return *this;
}

vector<int> WAVECNT::getCNT(int PN){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
	return WAVECNT_impl_->getCNT(PN);
}

void WAVECNT::clear(){
    WAVECNT_IMPL* WAVECNT_impl_ = (WAVECNT_IMPL*)WAVECNT_impl;
	WAVECNT_impl_->clear();
}