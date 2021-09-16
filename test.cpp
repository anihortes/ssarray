#include <iostream>
using std::cout;
using std::endl;
#include "ssarray.h"
#include <string>
using std::string;
#include <utility>
using std::move;
#include <algorithm>
using std::mismatch;


int main() {
    using ST = SSArray<int>::size_type;
    const ST thesize = 100;
    SSArray<int> rhs(thesize);

    // Set all items
    for (auto i = ST(0); i != thesize; ++i)
    {
        rhs[i] = 15-int(i*i);
    }


    // Make copy
    SSArray<int> lhs(rhs);
if(rhs!=lhs){
    cout << "TESTONMG\n";
}
rhs[20] = 343;
    auto rhsIter = rhs.begin();
    auto lhsIter = lhs.begin();
    // if sizes arent equal, then rhs != lhs
    // no need to iter through entire array checking values
    int count = 0;
    if(rhs.size()!=lhs.size()) cout << "FALSE1\n";
    while (rhsIter != rhs.end() && lhsIter != lhs.end()) {
        if (*rhsIter != *lhsIter) cout << "FALSE2 @ i = " << count << endl;
        cout << "RHS: " << *rhsIter << " LHS: " << *lhsIter << endl;
        rhsIter++;
        lhsIter++;
        count++;
    }
    cout << "END\n";

    return 0;
};
