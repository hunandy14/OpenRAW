/**********************************************************
Name : 建構子
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW.hpp"
namespace imr{
// ImrSize建構子
ImrSize::ImrSize(size_t high=0, size_t width=0)
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
ImrMask::ImrMask(ImrSize masksize, int value)
: mask(masksize.high * masksize.width), masksize(masksize){
    for(auto&& i : this->mask)
    	i=value;
}
ImrMask::ImrMask(initializer_list<int> mask): mask(mask){
	size_t len=sqrt(mask.size());
	masksize=ImrSize(len, len);
}
// imgraw建構子
imgraw::imgraw(ImrSize size)
: width(size.width), high(size.high), 
img_data(size.width*size.high), filesize(size.width*size.high),
masksize(ImrSize(3, 3)) {
	// 初始化亂數種子
    srand((unsigned)time(NULL)); rand();
}
} //imr