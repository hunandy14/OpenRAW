/**********************************************************
Name : OpenRaw 3.0.0
Date : 2016/08/04
By   : CharlotteHonG
Final: 2017/05/21
**********************************************************/
#ifndef OPEN_RAW_HPP
#define OPEN_RAW_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
#include <bitset>
#include <initializer_list>
#include <algorithm>
using namespace std;

namespace imr{
using imch=unsigned char;
#define one_level 256
#define one_byte 8
/*
     ######                      #####     ##
       ##                       ##   ##
       ##     ### ##   ## ###   ##       ####     ######    #####
       ##     ## # ##  ###       #####     ##        ##    ##   ##
       ##     ## # ##  ##            ##    ##       ##     #######
       ##     ## # ##  ##       ##   ##    ##      ##      ##
     ######   ##   ##  ##        #####   ######   ######    #####
*/
class ImrSize{
public:
    ImrSize(size_t y, size_t x);
    friend bool operator==(const ImrSize& lhs, const ImrSize& rhs);
    friend bool operator!=(const ImrSize& lhs, const ImrSize& rhs);
    operator const size_t() const;
    void info();
public:
    size_t high;
    size_t width;
};
/*
     ######                       ####
       ##                        ##  ##
       ##     ### ##   ## ###   ##        #####    #####   ## ###
       ##     ## # ##  ###      ##       ##   ##  ##   ##  ###
       ##     ## # ##  ##       ##       ##   ##  ##   ##  ##
       ##     ## # ##  ##        ##  ##  ##   ##  ##   ##  ##
     ######   ##   ##  ##         ####    #####    #####   ##
*/
class ImrCoor{
public:
    ImrCoor(int y, int x);
    void info();
    // 重載運算子
    friend ImrCoor const operator+(ImrCoor const &lhs, ImrCoor const &rhs);
    friend ImrCoor const operator-(ImrCoor const &lhs, ImrCoor const &rhs);
    ImrCoor & operator+=(const ImrCoor & rhs);
    ImrCoor & operator-=(const ImrCoor & rhs);
    ImrCoor & operator+=(const int & val);
    ImrCoor & operator-=(const int & val);
public:
    int y;
    int x;
};
/*
     ######                     ##   ##                    ##
       ##                       ##   ##                    ##
       ##     ### ##   ## ###   ### ###   ######   #####   ##  ##
       ##     ## # ##  ###      ## # ##  ##   ##  ##       ## ##
       ##     ## # ##  ##       ## # ##  ##   ##   ####    ####
       ##     ## # ##  ##       ##   ##  ##  ###      ##   ## ##
     ######   ##   ##  ##       ##   ##   ### ##  #####    ##  ##
*/
class ImrMask{
public:
    ImrMask(ImrSize masksize);
    ImrMask(ImrSize masksize, int value);
    ImrMask(initializer_list<int> mask);
public:
    void sort(size_t len, size_t start);
    void info(string name);
    int avg();
    int median();
    int median2();
public:
    int & at2d(size_t y, size_t x);
    const int & at2d(size_t y, size_t x) const;
    ImrMask & resize(ImrSize masksize);
    ImrMask & fixval();
public: // 重載運算子
    int & operator[](const size_t idx);
    const int & operator[](const size_t idx) const;
    friend ImrCoor const operator+(ImrCoor const &lhs, ImrCoor const &rhs);
    friend ImrCoor const operator-(ImrCoor const &lhs, ImrCoor const &rhs);
    ImrMask & operator+=(ImrMask const &rhs);
    ImrMask & operator-=(ImrMask const &rhs);
    ImrMask & operator+=(const int & rhs);
    ImrMask & operator-=(const int & rhs);
private:
    vector<int> mask;
public:
    ImrSize masksize;
};
/*
     ######                                       ######
     ##   ##                                      ##   ##
     ##   ##   ######   #####    #####            ##   ##   ######  ##   ##
     ######   ##   ##  ##       ##   ##           ######   ##   ##  ## # ##
     ##   ##  ##   ##   ####    #######           ## ##    ##   ##  ## # ##
     ##   ##  ##  ###      ##   ##                ##  ##   ##  ###  ## # ##
     ######    ### ##  #####     #####   #######  ##   ##   ### ##   ## ##

*/
class BaseRaw{
protected:
    BaseRaw(ImrSize size): 
    width(size.width), high(size.high), 
    img_data(size.width*size.high){}
    virtual ~BaseRaw() = default;
public: // 重載運算子
    imch & operator[](const size_t idx);
    const imch & operator[](const size_t idx) const;
    BaseRaw& operator+=(int const& rhs);
    BaseRaw& operator-=(int const& rhs);
    imch& at2d(size_t y, size_t x);
    const imch& at2d(size_t y, size_t x) const;
public:
    void resize(ImrSize size);
    bool check_size(BaseRaw const& rhs);
    imch & random();
    const imch & random() const;
    virtual void info(string name);
protected:
    size_t width;
    size_t high;
    vector<imch> img_data;
};
/*
       ##

     ####     ### ##    ######  ## ###    ######  ##   ##
       ##     ## # ##  ##   ##  ###      ##   ##  ## # ##
       ##     ## # ##  ##   ##  ##       ##   ##  ## # ##
       ##     ## # ##   ######  ##       ##  ###  ## # ##
     ######   ##   ##       ##  ##        ### ##   ## ##
                        #####
*/
class Imgraw: public BaseRaw {
public: // 建構子
    Imgraw(ImrSize size);
    ~Imgraw() = default;
public: // Imgraw
    void read(string filename);
    void write(string filename);
    void binarizae(imch value, imch high, imch low);
    void value(imch value);
    void pri_blk(string name, ImrCoor pos, ImrSize masksize);
public: // Mask
    void setMaskSize(ImrSize masksize);
    imch & maskVal(ImrCoor ori, ImrCoor mas, ImrCoor shi);
    const imch & maskVal(ImrCoor ori, ImrCoor mas, ImrCoor shi) const;
    const ImrMask getMask(ImrCoor ori, ImrCoor shi);
public: // histogram
    void pri_htg(string title);
    void pri_htg2(string title);
private: // 必要成員(建構)
    ImrSize masksize;
private: // 成員(函式)
    string filename;
    imch max, min;
    int htg_data[256];
    void extremum();
    void histogram();
};
} //Imgraw


#endif