/*****************************************************************
Name : 
Date : 2017/05/21
By   : CharlotteHonG
Final: 2017/05/21
*****************************************************************/
#include "OpenRAW.hpp"

namespace imr{
// 調整畫布大小
inline
void BaseRaw::resize(ImrSize size) {
    size_t y=size.high, x=size.width;
    this->width = x;
    this->high = y;
    this->img_data.vector::resize(x*y);
}
// 印出畫布大小
void BaseRaw::info(string name=""){
    cout << "[" << name << "]畫布大小(寬x長) = ";
    cout << this->width << " x " << this->high << endl;
}
} // imr