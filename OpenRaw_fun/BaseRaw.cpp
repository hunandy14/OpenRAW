/*****************************************************************
Name : 
Date : 2017/05/21
By   : CharlotteHonG
Final: 2017/05/21
*****************************************************************/
#include "OpenRAW.hpp"

namespace imr{
// �վ�e���j�p
inline
void BaseRaw::resize(ImrSize size) {
    size_t y=size.high, x=size.width;
    this->width = x;
    this->high = y;
    this->img_data.vector::resize(x*y);
}
// �L�X�e���j�p
void BaseRaw::info(string name=""){
    cout << "[" << name << "]�e���j�p(�ex��) = ";
    cout << this->width << " x " << this->high << endl;
}
} // imr