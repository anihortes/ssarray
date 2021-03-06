// ssarray.h
// A. Harrison Owen
// Started: 9/10/2021
// Finished: 9/15/2021
// Semi-Smart Array Class
//      template smart array class,
//      can do basic boolean compare operations

#ifndef SSARRAY_SSARRAY_H
#define SSARRAY_SSARRAY_H

#include <cassert>   // for std::assert
#include <cstddef>   // for std::size_t
#include <algorithm> // for std::swap

template <typename valType>
class SSArray {
public:
    // generic types for template
    using value_type = valType;    // value type in array
    using size_type = std::size_t; // size type in array

    //default ctor, array size = 8, array values = whatever is in memory
    SSArray(): _arrayPtr(new value_type[8]), _arraySize(8){}

    //ctor with specified size
    explicit SSArray(size_type size)
        : _arrayPtr(new value_type[size]), _arraySize(size) {}

    //ctor with specified size and value
    SSArray(size_type size, value_type value)
        : _arrayPtr(new value_type[size]), _arraySize(size){
        for(std::size_t i = 0; i < _arraySize; i++){
            _arrayPtr[i] = value;
        }
    }

    //copy ctor
    SSArray(const SSArray & other):
        _arrayPtr(new value_type[other._arraySize]), _arraySize(other._arraySize){
        for(std::size_t i = 0; i < other.size(); i++){
            _arrayPtr[i] = other[i];
        }
    }

    // copy assignment operator
    SSArray & operator=(const SSArray & rhs){
        SSArray copyRhs(rhs);
        arraySwap(copyRhs);
        return *this;
    }

    //move ctor
    SSArray(SSArray && other) noexcept:
            _arrayPtr(other._arrayPtr), _arraySize(other._arraySize)
    {
        other._arrayPtr = nullptr;
        other._arraySize = 0;
    }

    // move assignment operator
    SSArray & operator=(SSArray && rhs) noexcept{
        arraySwap(rhs);
        return *this;
    }

    // dctor
    ~SSArray(){
        delete [] _arrayPtr;
    }

//[] operators : array[n]
public:

    value_type & operator[](size_type index){
        assert(index <= _arraySize);
        return _arrayPtr[index];
    }

    const value_type & operator[](size_type index) const {
        assert(index <= _arraySize);
        return _arrayPtr[index];
    }

// iterator functions
public:

    size_type size(){
        assert(end()-begin() >= 0);
        return (end()-begin());
    }


    [[nodiscard]] size_type size() const{
        assert(end()-begin() >= 0);
        return (end() - begin());
    }

    value_type * begin(){
        return _arrayPtr;
    }

    value_type * end(){
        return begin() + _arraySize;
    }

    const value_type * begin() const{
        return _arrayPtr;
    }

    const value_type * end() const{
        assert(end()-begin() >= 0);
        return begin() + _arraySize;
    }

// private data members and functions
private:

    // for copy and move assignment operators
    void arraySwap(SSArray & other) noexcept{
        std::swap(_arrayPtr, other._arrayPtr);
        std::swap(_arraySize, other._arraySize);
    }

    // generic types for template
    value_type *_arrayPtr;
    size_type _arraySize;
};

//Preconditions:
//Requirements on Types

// lhs == rhs is true : lhs[n] == rhs[n]
//                      AND lhs.size() == rhs.size()
template <class value_type>
bool operator==(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs){
    auto rhsIter = rhs.begin();
    auto lhsIter = lhs.begin();
    // if sizes arent equal, then rhs != lhs
    if(rhs.size() != lhs.size()) return false;
    while (rhsIter != rhs.end() && lhsIter != lhs.end()) {
        if (*rhsIter != *lhsIter) return false;
        rhsIter++;
        lhsIter++;
    }
    return true;
}

template <class SSArray>
bool operator!=(const SSArray & lhs, const SSArray & rhs){
    return !(lhs==rhs);
}

// lhs < rhs is true : lhs[0] < rhs[0]
//                     if lhs[0] == rhs[0] then check for lhs[n+1] < rhs[n+1] ...
//                     if lhs[n+1] == rhs[n+1] for all n then lhs.size() < rhs.size() returns true
template <class value_type>
bool operator<(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs){

    // count will be the range of the for-loop
    // compare rhs and lhs sizes and choose smallest one
    std::size_t count = 0;
    if(rhs.size() > lhs.size()) count = lhs.size();
    else count = rhs.size();

    for(std::size_t i = 0; i < count; i++){
        if(lhs[i] < rhs[i]) return true;
        else if(lhs[i] > rhs[i]) return false;
    }

    return (lhs.size() < rhs.size());
}

template <class SSArray>
bool operator<=(const SSArray & lhs, const SSArray & rhs){
    return !(rhs < lhs);
}

template <class SSArray>
bool operator>(const SSArray & lhs, const SSArray & rhs){
    return (rhs < lhs);
}

template <class SSArray>
bool operator>=(const SSArray & lhs, const SSArray & rhs){
    return !(lhs < rhs);
}
#endif //SSARRAY_SSARRAY_H
