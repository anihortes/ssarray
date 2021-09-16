//
// Created by A. Harrison Owen on 9/10/2021.
//

#ifndef SSARRAY_SSARRAY_H
#define SSARRAY_SSARRAY_H

#include <iostream>
#include <string> // for std::string
#include <utility> // for std::move, std::swap
#include <ostream> // for std::ostream
#include <cassert> // for std::assert
#include <cstddef> // for std::size_t
#include <algorithm> // for std::swap, std::equal, std::fill

template <typename valType>
class SSArray
{
public:
    using value_type = valType;
    using size_type = std::size_t;

    //default ctor
    SSArray(): _arrayPtr(new value_type[8]), _arraySize(8){}

    //ctor
    explicit SSArray(size_type size)
        : _arrayPtr(new value_type[size]), _arraySize(size) {}

    //ctor
    SSArray(size_type size, value_type value)
        : _arrayPtr(new value_type[size]), _arraySize(size){
        //std::fill(_arrayPtr, _arrayPtr+size-1, 0);

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

    // copy assignment
    SSArray & operator=(const SSArray & rhs){
        SSArray copyRhs(rhs);
        arraySwap(copyRhs);
        return *this;
    }

    // move assignment
    SSArray & operator=(SSArray && rhs) noexcept{
        arraySwap(rhs);
        return *this;
    }

    //move ctor
    SSArray(SSArray && other) noexcept:
        _arrayPtr(other._arrayPtr), _arraySize(other._arraySize)
    {
        other._arrayPtr= 0;
        other._arraySize=0;
    }

    ~SSArray(){
        delete [] _arrayPtr;
    }

public:

    value_type & operator[](size_type index){
        assert(index <= _arraySize);
        return _arrayPtr[index];
    }

    const value_type & operator[](size_type index) const {
        assert(index <= _arraySize);
        return _arrayPtr[index];
    }

public:

    size_type size(){
        return (end()-begin());
    }

    [[nodiscard]] size_type size() const{
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
        return begin() + _arraySize;
    }

private:
    void arraySwap(SSArray & other) noexcept{
        std::swap(_arrayPtr, other._arrayPtr);
        std::swap(_arraySize, other._arraySize);
    }
    value_type *_arrayPtr;
    size_type _arraySize;
};

//Preconditions:
//Requirements on Types

template <class value_type>
bool operator==(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs){
    auto rhsIter = rhs.begin();
    auto lhsIter = lhs.begin();
    // if sizes arent equal, then rhs != lhs
    if(rhs.size()!=lhs.size()) return false;
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

template <class value_type>
bool operator<(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs){
    // count will be the range of the for-loop
    // compare rhs and lhs sizes and choose smallest one
    std::size_t count=0;
    if(rhs.size()>lhs.size())count=lhs.size();
    else count = rhs.size();

    for(std::size_t i=0; i<count; i++){
        if(lhs[i]<rhs[i]) return true;
        else if(lhs[i]>rhs[i])return false;
    }
    return(lhs.size() < rhs.size());
}

template <class SSArray>
bool operator<=(const SSArray & lhs, const SSArray & rhs){
    return!(rhs<lhs);
}

template <class SSArray>
bool operator>(const SSArray & lhs, const SSArray & rhs){
    return(rhs<lhs);
}

template <class SSArray>
bool operator>=(const SSArray & lhs, const SSArray & rhs){
    return !(lhs<rhs);
}
#endif //SSARRAY_SSARRAY_H
