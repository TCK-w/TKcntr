/*
 *  Main program of TKcntr.h.
 *
 *  gcc --version：gcc (Debian 10.2.1-6) 10.2.1 20210110
 *  Created on: 3/17/2024
 *  Author: TCK
 */

#include "TKcntr.h"

using namespace std;

int main(){
    //set the parameters of TKcntr
    TKcntr c;
    vector<string> item_s = {"name"};
    vector<string> item_i = {"addr","addr123"};
    vector<string> item_d = {"v1","v2"};
    // vector<string> item_d = {"v1"};
    c.setItem("String",item_s);
    c.setItem("Integer",item_i);
    c.setItem("Double",item_d);
    //create WT using user difined name
    WT& wt0 = c.wt("wt",0);
    WT& wt1 = c.wt("wt",1);
    cout<<"Find wt0 in c? "<<c.findWt("wt",0)<<endl;
    cout<<"Find wt1 in c? "<<c.findWt("wt",1)<<endl;
    // // read TKR file
    TKR& r1 = c.tkr("./File/TKcntr_file1.txt");
    TKR& r2 = c.tkr("./File/TKcntr_file2.txt");
    r1.showItem();
    cout<<"r1 state: "<<r1.state()<<endl;
    cout<<r1.err()<<endl;
    vector<string> r1_s = r1.getString("name");
    vector<int> r1_i = r1.getInt("addr");
    vector<double> r1_d1 = r1.getDouble("v1");
    vector<double> r1_d2 = r1.getDouble("v2");
    for(int i=0; i<r1.len();i++){
        cout<<r1_i.at(i)<<" "<<r1_s.at(i)<<" "<<r1_d1.at(i)<<" "<<r1_d2.at(i)<<endl;
    }
    cout<<"modify value"<<endl;
    r1.getString("name",2) = "hello";
    r1.getInt("addr",2) = 100;
    r1.getDouble("v1",2) = 10.5;
    vector<string> mr1_s = r1.getString("name");
    vector<int> mr1_i = r1.getInt("addr");
    vector<double> mr1_d1 = r1.getDouble("v1");
    vector<double> mr1_d2 = r1.getDouble("v2");
    for(int i=0; i<r1.len();i++){
        cout<<mr1_i.at(i)<<" "<<mr1_s.at(i)<<" "<<mr1_d1.at(i)<<" "<<mr1_d2.at(i)<<endl;
    }
}
