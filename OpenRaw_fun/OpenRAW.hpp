/**********************************************************
Name : OpenRaw 2.7.1
Date : 2016/08/04
By   : CharlotteHonG
Final: 2017/02/21
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
using namespace std;

namespace imr{
    using imch=unsigned char;
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
        friend ImrCoor operator+(ImrCoor const &lhs, ImrCoor const &rhs);
        friend ImrCoor operator-(ImrCoor const &lhs, ImrCoor const &rhs);
        ImrCoor & operator+=(const ImrCoor &rhs);
        ImrCoor & operator-=(const ImrCoor &rhs);
        ImrCoor & operator+=(int val);
        ImrCoor & operator-=(int val);
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
        ImrMask(ImrSize masksize, imch value);
        void sort(size_t len, size_t start);
        void info(string name);
        imch avg();
        imch median();
    public:
        imch & at2d(size_t y, size_t x);
        const imch & at2d(size_t y, size_t x) const;
    public: // 重載運算子
        imch & operator[](const size_t idx);
        const imch & operator[](const size_t idx) const;
        ImrMask operator+(const ImrMask &p);
        ImrMask operator-(const ImrMask &p);
    private:
        vector<imch> mask;
        ImrSize masksize;
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
    class imgraw {
    public: // 建構子
        imgraw(ImrSize size);
        // const size_t one_byte=8;
        #define one_byte 256
    public: // imgraw
        void read(string filename);
        void write(string filename);
        imch & at2d(size_t y, size_t x);
        const imch & at2d(size_t y, size_t x) const;
        void resize_canvas(size_t size);
        void resize_canvas(ImrSize size);
        void info(string name);
        void binarizae(imch value, imch high, imch low);
        void value(imch value);
        imch & random();
        const imch & random() const;
        void pri_blk(string name, ImrCoor pos, ImrSize masksize);
    public: // Mask
        void setMaskSize(ImrSize masksize);
        imch & maskVal(ImrCoor ori, ImrCoor mas, ImrCoor shi);
        const imch & maskVal(ImrCoor ori, ImrCoor mas, ImrCoor shi) const;
        ImrMask getMask(ImrCoor ori, ImrCoor shi);
    public: // histogram
        void pri_htg(string title);
    public: // 重載運算子
        imch & operator[](const size_t idx);
        const imch & operator[](const size_t idx) const;
        imgraw operator+(const imgraw &p);
        imgraw operator+(const imch value);
        imgraw operator-(const imgraw &p);
        imgraw operator-(const imch value);
    private: // 必要成員(建構)
        size_t width;
        size_t high;
        vector<imch> img_data;
        ifstream::pos_type filesize;
        ImrSize masksize;
    private: // 成員(函式)
        string filename;
        imch max, min;
        int htg_data[256];
        void extremum();
        void histogram();
    };
};


#endif