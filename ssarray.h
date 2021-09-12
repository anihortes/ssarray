//
// Created by A. Harrison Owen on 9/10/2021.
//

#ifndef SSARRAY_SSARRAY_H
#define SSARRAY_SSARRAY_H

#include <iostream>
#include <string> // for std::string
#include <utility> // for std::move. std::swap
#include <ostream> // for std::ostream
#include <cassert> // for std::assert
#include <cstddef> // for std::size_t
#include <typeinfo> // for typeid

template <typename valType>
class SSArray
{
public:
    using value_type = valType;
    using size_type = std::size_t;

    //default ctor
    SSArray(): _arrayPtr(new value_type[8]), _arraySize(8){

    }

    //ctor
    explicit SSArray(size_type size)
        : _arrayPtr(new value_type[size]), _arraySize(size) {

    }

    //ctor
    SSArray(size_type size, value_type value)
        : _arrayPtr(new value_type[size]), _arraySize(size){
        for(int i = 0; i<_arraySize;i++){
            _arrayPtr[i] = value;
        }
    }

/*
    SSArray(SSArray & other):_arrayPtr(other._arrayPtr), _arraySize(other._arraySize){
        for(int i = 0; i<_arraySize;i++){
            _arrayPtr[i] = other[i];
        }
    }
    */

    //copy ctor
    SSArray(const SSArray & other): _arrayPtr(new value_type[other.size()]), _arraySize(other._arraySize){
        for(int i = 0; i<_arraySize;i++){
            _arrayPtr[i] = other[i];
        }
    }

    // copy assignment
    SSArray & operator=(const SSArray & rhs){
        SSArray copy_of_rhs(rhs);
        arraySwap(copy_of_rhs);
        return *this;
    }

    // move assignment
    SSArray & operator=(SSArray && rhs) noexcept{
        arraySwap(rhs);
        return *this;
    }

    //move ctor
    SSArray(SSArray && other) noexcept: _arrayPtr(other._arrayPtr), _arraySize(other._arraySize)
    {
        other._arrayPtr=0;
        other._arraySize=1;
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

        return end()-begin();
    }
    [[nodiscard]] size_type size() const{
        return end() - begin();
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

    value_type * _arrayPtr;
    int _arraySize{};
};

//Preconditions:
//Requirements on Types

template <class SSArray>
bool operator==(const SSArray & rhs, const SSArray & lhs){
    assert(typeid(rhs[0]).name() == typeid(lhs[0]).name());
    if(rhs.size() == lhs.size()){
        int equalCompare = 0;
        for(int i = 0; i < rhs.size(); i++){
            if (rhs[i] == rhs[i]) {
                equalCompare++;
            }
        }
        if(equalCompare==rhs.size())
            return true;
    }
    return false;
}

template <class SSArray>
bool operator!=(const SSArray & rhs, const SSArray & lhs){
    assert(typeid(rhs[0]).name() == typeid(lhs[0]).name());
    return !(rhs==lhs);
};

template <class SSArray>
bool operator<(const SSArray & rhs, const SSArray & lhs){
    return !(rhs==lhs);
};

template <class SSArray>
bool operator<=(const SSArray & rhs, const SSArray & lhs){
    return !(rhs==lhs);
};

template <class SSArray>
bool operator>(const SSArray & rhs, const SSArray & lhs){
    return !(rhs==lhs);
};

template <class SSArray>
bool operator>=(const SSArray & rhs, const SSArray & lhs){
    return !(rhs==lhs);
};
#endif //SSARRAY_SSARRAY_H
