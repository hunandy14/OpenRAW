/**********************************************************
Name : OpenRaw 2.6.0
Date : 2016/08/04
By   : CharlotteHonG
Final: 2017/02/14
**********************************************************/
#ifndef OPEN_RAW_HPP
#define OPEN_RAW_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
typedef unsigned char imch;
typedef size_t imint;

namespace imr{
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
        ImrSize(imint y, imint x);
        imint high;
        imint width;
        void info();
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
        ImrCoor operator+(const ImrCoor &p);
        ImrCoor operator-(const ImrCoor &p);
        ImrCoor operator*(const ImrCoor &p);
        ImrCoor operator/(const ImrCoor &p);
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
        // 重載運算子
        imch & operator[](const size_t __n);
        const imch & operator[](const size_t __n) const;
        imch & at2d(size_t y, size_t x);
        const imch & at2d(size_t y, size_t x) const;
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
    public:
        imgraw(ImrSize size);
        // imgraw
        void read(string filename);
        void write(string filename);
        imch & at2d(size_t y, size_t x);
        const imch & at2d(size_t y, size_t x) const;
        void resize_canvas(size_t size);
        void resize_canvas(ImrSize size);
        void info(string name);
        void binarizae(imch value, imch high, imch low);
        void value(imch value);
        // Mask
        void setMaskSize(ImrSize masksize);
        imch & maskVal(ImrCoor ori, ImrCoor mas, ImrCoor shi);
        const imch & maskVal(ImrCoor ori, ImrCoor mas, ImrCoor shi) const;
        ImrMask getMask(ImrCoor ori, ImrCoor shi);
        // histogram
        void pri_htg(string title);
        // 重載運算子
        imch & operator[](const size_t __n);
        const imch & operator[](const size_t __n) const;
        imgraw operator+(const imgraw &p);
        imgraw operator+(const imch value);
        imgraw operator-(const imgraw &p);
        imgraw operator-(const imch value);
    private:
        imint width;
        imint high;
        vector<imch> img_data;
        ifstream::pos_type filesize;
        string filename;
        imch max;
        imch min;
        int htg_data[256];
        void histogram();
        void extremum();
        ImrSize masksize;
    };
};


#endif