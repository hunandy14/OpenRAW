﻿/**********************************************************
Name : 建構子
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW.hpp"
namespace imr{
// ImrSize建構子
ImrSize::ImrSize(imint high=0, imint width=0)
: high(high), width(width){

}
// ImrCoor建構子
ImrCoor::ImrCoor(int y=0, int x=0)
: y(y), x(x){

}
// ImrMask建構子
ImrMask::ImrMask(ImrSize masksize)
: mask(masksize.high * masksize.width), masksize(masksize){

}
ImrMask::ImrMask(ImrSize masksize, imch value)
: mask(masksize.high * masksize.width), masksize(masksize){
    for (unsigned i = 0; i < masksize.high*masksize.width; ++i){
        this->mask[i] = value;
    }
}
// imgraw建構子
imgraw::imgraw(ImrSize size)
: width(size.width), high(size.high), 
img_data(size.width*size.high), filesize(size.width*size.high),
masksize(ImrSize(0,0)) {
    
}
} //imr