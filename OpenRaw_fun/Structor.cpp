﻿/**********************************************************
Name : 建構子
Date : 2016/10/03
By   : CharlotteHonG
Final: 2017/05/21
**********************************************************/
#include "OpenRAW.hpp"
namespace imr{
// ImrSize建構子
ImrSize::ImrSize(size_t high=0, size_t width=0):
    high(high), width(width)
{

}
// ImrCoor建構子
ImrCoor::ImrCoor(int y=0, int x=0): 
    y(y), x(x)
{

}
// ImrMask建構子
ImrMask::ImrMask(ImrSize masksize): 
    mask(masksize.high * masksize.width), masksize(masksize)
{

}
ImrMask::ImrMask(ImrSize masksize, int value):
    mask(masksize.high * masksize.width), masksize(masksize)
{
    for(auto&& i : this->mask)
        i=value;
}
ImrMask::ImrMask(initializer_list<int> mask): mask(mask){
    size_t len=sqrt(mask.size());
    masksize=ImrSize(len, len);
}
// Imgraw建構子
Imgraw::Imgraw(ImrSize size): 
    BaseRaw(size),
    masksize(ImrSize(3, 3))
{

}
} //imr