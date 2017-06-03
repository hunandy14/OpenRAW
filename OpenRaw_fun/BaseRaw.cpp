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
// 圖片大小是否相同
bool BaseRaw::check_size(BaseRaw const& rhs){
    if(this->width==rhs.width and this->high==rhs.high) {
        return 1;
    } return 0;
}
// 隨機回傳一個點
imch & BaseRaw::random(){
    return const_cast<imch&>(static_cast<const BaseRaw&>(*this).random());
}
const imch & BaseRaw::random() const{
    int up=this->img_data.size(), low=0;
    size_t idx = ((rand() / (RAND_MAX+1.0)) * (up - low) + low);
    return (*this)[idx];
}
// 印出畫布大小
void BaseRaw::info(string name=""){
    cout << "[" << name << "]畫布大小(寬x長) = ";
    cout << this->width << " x " << this->high << endl;
}
} // imr