/*
 *  Tool for TK container.
 *
 *  gcc --version：gcc (Debian 10.2.1-6) 10.2.1 20210110
 *  Created on: 3/17/2024
 *  Author: TCK
 */

#include <sstream>
#include <fstream>
#include <map>
#include "TKcntr.h"

using namespace std;

class TKR_imp_{
private:
	bool tk_state=false;
	int tk_len;
	string TKR_name;
	string reportErr = "";
	vector<vector<string> > *TKstring;
	map<string,vector<string>* > item_s;
	map<string,vector<int>* > item_i;
	map<string,vector<double>* > item_d;
	map<int,vector<int> > addr_rec;
	struct Private;
	string dump_s;
	int dump_i;
	double dump_d;
	void READTK(string TKR_name){
		// Read file
		int line_n = 0;
		size_t element_n;
		string line, element;
		vector<string> line_e;
		ifstream file(TKR_name);
		if (file.is_open()){
			while(getline(file, line)){
				line_e.clear();
	            stringstream ss(line);
	            while(getline(ss, element, '\t')){
	                if(element.size()!=0){
	                	line_e.push_back(element);
	                }
	            }
	            if(line_n==0){
	            	element_n = line_e.size();
	            	this->TKstring = new vector<vector<string> >;
	            	this->TKstring->push_back(line_e);
	            	if(element_n==0){this->reportErr = this->reportErr+"ERR: First row in "+TKR_name+" is empty.\n";}
	            }else{
	            	if(line_e.size()== element_n){
	            		this->TKstring->push_back(line_e);
	            	}else{
	            		this->reportErr = this->reportErr+"Warning: Wrong number of elements in row "+to_string(line_n)+"\n";
	            	}
	            }
	            line_n++;
			}
			this->tk_state = true;
			file.close();
		}else{
			this->tk_state = false;
			this->reportErr = this->reportErr+"ERR: Failed to open "+TKR_name+"\n";
		}
	}
	void FIND_S(vector<string> item_s){
		vector<string>* tmp_s;
		vector<vector<string> > *TKstring_p = this->TKstring;
		int found;
		// get string
		for(vector<string>::iterator it = item_s.begin(); it!=item_s.end(); it++){
			found = 0;
			for(size_t j=0; j<(*TKstring_p).at(0).size(); j++){
				if((*it).compare((*TKstring_p).at(0).at(j))==0){
					found = 1;
					tmp_s = new vector<string>;
					for(size_t i=1; i<(*TKstring_p).size(); i++){
						tmp_s->push_back((*TKstring_p).at(i).at(j));
					}
					this->item_s.insert(pair<string, vector<string>* >(*it,tmp_s));
					tmp_s = nullptr;
				}
			}
			if(found==0){this->reportErr = this->reportErr+"ERR: "+(*it)+" not found in first row.\n";}
		}
	}
	void FIND_I(vector<string> item_i){
		vector<int> *tmp_i;
		vector<vector<string> > *TKstring_p = this->TKstring;
		int found;
		// get integer
		for(vector<string>::iterator it = item_i.begin(); it!=item_i.end(); it++){
			found = 0;
			for(size_t j=0; j<(*TKstring_p).at(0).size(); j++){
				if((*it).compare((*TKstring_p).at(0).at(j))==0){
					found = 1;
					tmp_i = new vector<int>;
					bool conv = true;
					for(size_t i=1; i<(*TKstring_p).size(); i++){
						try {
							int i_c = stoi((*TKstring_p).at(i).at(j));
							tmp_i->push_back(i_c);
						} catch (invalid_argument &e) {
							this->reportErr = this->reportErr+"ERR: Convert column "+(*it)+" failed. => ";
							this->reportErr = this->reportErr+e.what()+" failed.\n";
							delete tmp_i;
							tmp_i = nullptr;
							conv = false;
							break;
						}
					}
					if(conv==true){ this->item_i.insert(pair<string, vector<int>* >(*it,tmp_i)); }
				}
			}
			if(found==0){this->reportErr = this->reportErr+"ERR: "+(*it)+" not found in first row.\n";}
		}
	}
	void FIND_D(vector<string> item_d){
		vector<double> *tmp_d;
		vector<vector<string> > *TKstring_p = this->TKstring;
		int found;
		// get double
		for(vector<string>::iterator it = item_d.begin(); it!=item_d.end(); it++){
			found = 0;
			for(size_t j=0; j<(*TKstring_p).at(0).size(); j++){
				if((*it).compare((*TKstring_p).at(0).at(j))==0){
					found = 1;
					tmp_d = new vector<double>;
					bool conv = true;
					for(size_t i=1; i<(*TKstring_p).size(); i++){
						try {
							double i_d = stod((*TKstring_p).at(i).at(j));
							tmp_d->push_back(i_d);
						} catch (invalid_argument &e) {
							this->reportErr = this->reportErr+"ERR: Convert column "+(*it)+" failed. => ";
							this->reportErr = this->reportErr+e.what()+" failed.\n";
							delete tmp_d;
							tmp_d = nullptr;
							conv = false;
							break;
						}
					}
					if(conv==true){ this->item_d.insert(pair<string, vector<double>* >(*it,tmp_d)); }
				}
			}
			if(found==0){this->reportErr = this->reportErr+"ERR: "+(*it)+" not found in first row.\n";}
		}
	}
	void GET_LEN(){
		if(!this->item_s.empty()){
			map<string,vector<string>* >::iterator it= this->item_s.begin();
			size_t length=it->second->size();
			this->tk_len = length;
			return;
		}else if(!this->item_i.empty()){
			map<string,vector<int>* >::iterator iti= this->item_i.begin();
			size_t length=iti->second->size();
			this->tk_len = length;
			return;
		}else if(!this->item_d.empty()){
			map<string,vector<double>* >::iterator itd = this->item_d.begin();
			size_t length=itd->second->size();
			this->tk_len = length;
			return;
		}else{
			this->tk_len = 0;
			return;
		}
	}
public:
	TKR_imp_(string TKR_name, vector<string> item_s,vector<string> item_i,vector<string> item_d){
		// Private PRIVATE;
		this->reportErr = this->reportErr+"=========  "+TKR_name+" error report  =========\n";
		this->TKR_name = TKR_name;
		this->READTK(TKR_name);

		if(this->tk_state==true){
			this->FIND_S(item_s);
			this->FIND_I(item_i);
			this->FIND_D(item_d);
			this->GET_LEN();
		}
	}

	int len(){ return this->tk_len; }

	vector<string> getString(string item_name){
		map<string,vector<string>* >::iterator it=this->item_s.find(item_name);
		if(it==this->item_s.end()){
			vector<string> dump;
			return dump;
		}else{
			return *(it->second);
		}
	}

	vector<int> getInt(string item_name){
		map<string,vector<int>* >::iterator it=this->item_i.find(item_name);
		if(it==this->item_i.end()){
			vector<int> dump;
			return dump;
		}else{
			return *(it->second);
		}
	}

	vector<double> getDouble(string item_name){
		map<string,vector<double>* >::iterator it=this->item_d.find(item_name);
		if(it==this->item_d.end()){
			vector<double> dump;
			return dump;
		}else{
			return *(it->second);
		}
	}

	string& getString(string item_name,int n){
		map<string,vector<string>* >::iterator it=this->item_s.find(item_name);
		if(it==this->item_s.end() || n<0){
			this->dump_s = "Not Found";
			return this->dump_s;
		}else{
			return it->second->at(n);
		}
	}

	int& getInt(string item_name, int n){
		map<string,vector<int>* >::iterator it=this->item_i.find(item_name);
		if(it==this->item_i.end() || n<0){
			this->dump_i= -1;
			return this->dump_i;
		}else{
			return it->second->at(n);
		}
	}

	double& getDouble(string item_name, int n){
		map<string,vector<double>* >::iterator it=this->item_d.find(item_name);
		if(it==this->item_d.end() || n<0){
			this->dump_d= -1;
			return this->dump_d;
		}else{
			return it->second->at(n);
		}
	}
	bool find(string item_name){
		map<string,vector<string>* >::iterator it= this->item_s.find(item_name);
		map<string,vector<int>* >::iterator iti= this->item_i.find(item_name);
		map<string,vector<double>* >::iterator itd = this->item_d.find(item_name);
		if(it==this->item_s.end() || iti==this->item_i.end() || itd==this->item_d.end()){
			return false;
		}else{ return true; }
	}

	string err(){ return this->reportErr;}

	bool state(){ return this->tk_state;}

	void showItem(){
		cout<<"=========  "<<this->TKR_name<<" Items  ========="<<endl;
		cout<<"Type string:\t";
		map<string,vector<string>* >::iterator it;
		for(it = this->item_s.begin(); it!=this->item_s.end(); it++){
			cout<<(*it).first<<"\t";
		}
		cout<<endl;
		cout<<"Type int:\t";
		map<string,vector<int>* >::iterator iti;
		for(iti = this->item_i.begin(); iti!=this->item_i.end(); iti++){
			cout<<(*iti).first<<"\t";
		}
		cout<<endl;
		cout<<"Type double:\t";
		map<string,vector<double>* >::iterator itd;
		for(itd = this->item_d.begin(); itd!=this->item_d.end(); itd++){
			cout<<(*itd).first<<"\t";
		}
		cout<<endl;
	}
};

class TKcntr_imp_{
private:
	map<string,TKR*> TK_list;
	map<string,WT*> waveList;
	vector<string> type_s, type_i, type_d;
public:
	~TKcntr_imp_(){
		map<string,TKR*>::iterator it;
		for(it=this->TK_list.begin();it!=this->TK_list.end();it++){
			TKR* tmp = it->second;
			delete tmp;
			it->second = nullptr;
		}
		map<string,WT*>::iterator its;
		for(its=this->waveList.begin();its!=this->waveList.end();its++){
			WT* tmp = its->second;
			delete tmp;
			it->second = nullptr;
		}
	}

	void setItem(string& type, vector<string>& Item_name){
		if(this->TK_list.empty()){
			if(type.compare("String")==0){
				this->type_s.clear();
				for(vector<string>::const_iterator it=Item_name.begin(); it!=	Item_name.end();it++){
					this->type_s.push_back((*it));
				}
			}
			if(type.compare("Integer")==0){
				this->type_i.clear();
				for(vector<string>::const_iterator it=Item_name.begin(); it!=	Item_name.end();it++){
					this->type_i.push_back((*it));
				}
			}
			if(type.compare("Double")==0){
				this->type_d.clear();
				for(vector<string>::const_iterator it=Item_name.begin(); it!=	Item_name.end();it++){
					this->type_d.push_back((*it));
				}
			}
		}
	}

	TKR& tkr(string& TKR_name){
		map<string,TKR*>::iterator it = this->TK_list.find(TKR_name);
		if(it==this->TK_list.end()){
			TKR *tmp_tk = new TKR(TKR_name,this->type_s,this->type_i,this->type_d);
			this->TK_list.insert(pair<string,TKR*>(TKR_name,tmp_tk));
			return *tmp_tk;
		}else{
			return *(it->second);
		}
	}

	WT& wt(string& subdie_name, int& n){
		string targ_name = subdie_name +"_"+ to_string(n);
		map<string,WT*>::iterator it = this->waveList.find(targ_name);
		if(it==this->waveList.end()){
			WT *tmp_wt = new WT;
			this->waveList.insert(pair<string,WT*>(targ_name,tmp_wt));
			return *tmp_wt;
		}else{
			return *(it->second);
		}
	}

	bool findWt(string& subdie_name, int& n){
		string targ_name = subdie_name +"_"+ to_string(n);
		map<string,WT*>::iterator it = this->waveList.find(targ_name);
		if(it==this->waveList.end()){
			return false;
		}else{
			return true;
		}
	}
};

TKcntr::TKcntr():TKcntr_imp(nullptr){
	if(TKcntr_imp==nullptr){
		TKcntr_imp = new TKcntr_imp_;
	}
}
TKcntr::~TKcntr(){
	if(TKcntr_imp!=nullptr){
		TKcntr_imp_* imp = (TKcntr_imp_*)TKcntr_imp;
		delete imp;
		TKcntr_imp = nullptr;
	}
}
void TKcntr::setItem(string type, vector<string>& Item_name){
	TKcntr_imp_* imp = (TKcntr_imp_*)TKcntr_imp;
	imp->setItem(type,Item_name);
}
TKR& TKcntr::tkr(string tk_name){
	TKcntr_imp_* imp = (TKcntr_imp_*)TKcntr_imp;
	return imp->tkr(tk_name);
}
WT& TKcntr::wt(string subdie_name, int n){
	TKcntr_imp_* imp = (TKcntr_imp_*)TKcntr_imp;
	return imp->wt(subdie_name, n);
}
bool TKcntr::findWt(string subdie_name, int n){
	TKcntr_imp_* imp = (TKcntr_imp_*)TKcntr_imp;
	return imp->findWt(subdie_name, n);
}

TKR::TKR(string& TK_name,vector<string>& item_s,vector<string>& item_i,vector<string>& item_d):TKR_imp(nullptr){
	if(TKR_imp==nullptr){
		TKR_imp = new TKR_imp_(TK_name,item_s,item_i,item_d);
	}
}
TKR::~TKR(){
	if(TKR_imp!=nullptr){
		TKR_imp_* imp = (TKR_imp_*)TKR_imp;
		delete imp;
		TKR_imp = nullptr;
	}
}
int TKR::len(){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->len();
}
vector<string> TKR::getString(string item_name){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->getString(item_name);
}
vector<int> TKR::getInt(string item_name){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->getInt(item_name);
}
vector<double> TKR::getDouble(string item_name){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->getDouble(item_name);
}
string& TKR::getString(string item_name, int n){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->getString(item_name,n);
}
int& TKR::getInt(string item_name, int n){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->getInt(item_name,n);
}
double& TKR::getDouble(string item_name, int n){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->getDouble(item_name,n);
}
bool TKR::find(string item_name){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->find(item_name);
}
string TKR::err(){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->err();
}
bool TKR::state(){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->state();
}
void TKR::showItem(){
	TKR_imp_* imp = (TKR_imp_*)TKR_imp;
	return imp->showItem();
}

WT::WT(){ cout<<"WT constructed."<<endl;}
WT::~WT(){ cout<<"WT destructed."<<endl;}