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
    SSArray(): _arrayPtr(new value_type[8]), _arraySize(8){
/*
        std::fill(iter begin, iter begin+7, 0);


        size_type index = 0;
        while(true){
            _arrayPtr[index] = 0;
            if(index == 8) break;
            index++;
        }*/
    }

    //ctor
    explicit SSArray(size_type size)
        : _arrayPtr(new value_type[size]), _arraySize(size) {
/*
            std::fill(iter begin, iter begin+size-1, 0);

           size_type index = 0;
        while(true){
            _arrayPtr[index] = index;
            if(index == size) break;
            index++;
        }*/
    }

    //ctor
    SSArray(size_type size, value_type value)
        : _arrayPtr(new value_type[size]), _arraySize(size){
        //std::fill(_arrayPtr, _arrayPtr+size-1, 0);

        size_type index = 0;
        while(true){
            assert(index < size);
            _arrayPtr[index] = value;
            if(index == size) break;
            index++;
        }

    }

    //copy ctor
    SSArray(const SSArray & other): _arrayPtr(new value_type[other._arraySize]), _arraySize(other._arraySize){
       // std::copy(other.begin(),other.end(),_arrayPtr??)
        size_type index = 0;
        while(true){
            assert(index < other.size());
            _arrayPtr[index] = other[index];
            if(index == other.size()) break;
            index++;
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
    size_type _arraySize;
};

//Preconditions:
//Requirements on Types

template <class SSArray>
bool operator==(const SSArray & rhs, const SSArray & lhs){
    //assert(std::equal(rhs.begin(),rhs.end(),lhs.begin()));
    if(rhs.size() == lhs.size()){
        if(std::equal(rhs.begin(),rhs.end(),lhs.begin(),lhs.end()))
            return true;
        /*int equalCompare = 0;
        for(int i = 0; i < rhs.size(); i++){
            if (rhs.begin()+i == lhs.begin()+i) {
                equalCompare++;
            }
        }
        if(equalCompare==rhs.size())
            return true;*/
    }
    return false;
}

template <class SSArray>
bool operator!=(const SSArray & rhs, const SSArray & lhs){
    //assert(std::equal(rhs.begin(),rhs.end(),lhs.begin()));
    return !(rhs==lhs);
}

template <class SSArray>
bool operator<(const SSArray & rhs, const SSArray & lhs){
    //assert(std::equal(rhs.begin(),rhs.end(),lhs.begin()));
    auto mypair = std::mismatch(rhs.begin(),rhs.end(),lhs);
    while(mypair.first != rhs.end() && mypair.second != lhs.end()) {
        if (mypair.first < mypair.second) return true;
        mypair.first++;
        mypair.second++;
    }
    return false;
}

template <class SSArray>
bool operator<=(const SSArray & rhs, const SSArray & lhs){
    //assert(std::equal(rhs.begin(),rhs.end(),lhs.begin()));
    auto mypair = std::mismatch(rhs.begin(),rhs.end(),lhs);
    while(mypair.first != rhs.end() && mypair.second!=lhs.end()) {
        if (mypair.first < mypair.second) return true;
        if (mypair.first > mypair.second) return false;
        mypair.first++;
        mypair.second++;
    }
    return true;
}

template <class SSArray>
bool operator>(const SSArray & rhs, const SSArray & lhs){
    //assert(std::equal(rhs.begin(),rhs.end(),lhs.begin()));
    return !(rhs <= lhs);
}

template <class SSArray>
bool operator>=(const SSArray & rhs, const SSArray & lhs){
    //assert(std::equal(rhs.begin(),rhs.end(),lhs.begin()));
    return !(rhs < lhs);
}
#endif //SSARRAY_SSARRAY_H
