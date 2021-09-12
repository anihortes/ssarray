#include <iostream>
using std::cout;
using std::endl;
#include "ssarray.h"
#include <string>
using std::string;



int main() {
    bool allgood;  // For results of checking multiple values

    using ST = SSArray<int>::size_type;
    const ST thesize = 20;
    SSArray<int> mi1(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        mi1[i] = 15-int(i*i);
    }

    // Make new copy -- COPY CTOR
    SSArray<int> mi2(mi1);
    mi2[1] = 99;
    if(mi1==mi2) std::cout << "HEY!!\n";
    else{
        std::cout << "NAY!!!!\n";
    }
    for(int i = 0; i < mi1.size(); i++){
        std::cout << mi1[i] << " ";
    }
    cout << "\n";
    for(int i = 0; i < mi1.size(); i++){
        std::cout << mi2[i] << " ";
    }
    SSArray<int> a(5,3);
    cout << "\n";
    for(int i = 0; i < a.size(); i++){
        std::cout << a[i] << " ";
    }
    return 0;
};
