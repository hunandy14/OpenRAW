/**********************************************************
Name : 運算子重載
Date : 2016/10/03
By   : CharlotteHonG
Final: 2017/03/05
**********************************************************/
#include "OpenRAW.hpp"
namespace imr{
/*
     ######                       ####
       ##                        ##  ##
       ##     ### ##   ## ###   ##        #####    #####   ## ###
       ##     ## # ##  ###      ##       ##   ##  ##   ##  ###
       ##     ## # ##  ##       ##       ##   ##  ##   ##  ##
       ##     ## # ##  ##        ##  ##  ##   ##  ##   ##  ##
     ######   ##   ##  ##         ####    #####    #####   ##

*/
ImrCoor operator+(ImrCoor const &lhs, ImrCoor const &rhs){
    return ImrCoor(lhs) += rhs;
}
ImrCoor operator-(ImrCoor const &lhs, ImrCoor const &rhs){
    return ImrCoor(lhs) -= rhs;
}
ImrCoor & ImrCoor::operator+=(const ImrCoor &rhs){
    this->y += rhs.y;
    this->x += rhs.x;
    return *this;
}
ImrCoor & ImrCoor::operator-=(const ImrCoor &rhs){
    this->y -= rhs.y;
    this->x -= rhs.x;
    return *this;
}
ImrCoor & ImrCoor::operator+=(int val){
    this->y += val;
    this->x += val;
    return *this;
}
ImrCoor & ImrCoor::operator-=(int val){
    this->y -= val;
    this->x -= val;
    return *this;
}
/*
     ######                     ##   ##                    ##
       ##                       ##   ##                    ##
       ##     ### ##   ## ###   ### ###   ######   #####   ##  ##
       ##     ## # ##  ###      ## # ##  ##   ##  ##       ## ##
       ##     ## # ##  ##       ## # ##  ##   ##   ####    ####
       ##     ## # ##  ##       ##   ##  ##  ###      ##   ## ##
     ######   ##   ##  ##       ##   ##   ### ##  #####    ##  ##

*/
// 重載下標符號
int & ImrMask::operator[](const size_t idx){
    return const_cast<int&>(static_cast<const ImrMask&>(*this)[idx]);
}
const int & ImrMask::operator[](const size_t idx) const{
    return this->mask[idx];
}
// 重載加減符號
ImrMask operator+(ImrMask const &lhs, ImrMask const &rhs){
    return ImrMask(lhs) += rhs;
}
ImrMask operator-(ImrMask const &lhs, ImrMask const &rhs){
    return ImrMask(lhs) -= rhs;
}
ImrMask & ImrMask::operator+=(const ImrMask &rhs){
    // 判定大小是否吻合
    if(this->masksize.high != rhs.masksize.high
        or this->masksize.width != rhs.masksize.width)
    {
        cout << "  **Error! Invalid size" << endl;
        return (*this);
    }
    size_t len=this->masksize.high * this->masksize.width;
    for(unsigned i = 0; i < len; ++i)
        (*this)[i] += rhs[i];
    return (*this);
}
ImrMask & ImrMask::operator-=(const ImrMask &rhs){
    // 判定大小是否吻合
    if(this->masksize.high != rhs.masksize.high
        or this->masksize.width != rhs.masksize.width)
    {
        cout << "  **Error! Invalid size" << endl;
        return (*this);
    }
    size_t len=this->masksize.high * this->masksize.width;
    for(unsigned i = 0; i < len; ++i)
        (*this)[i] -= rhs[i];
    return (*this);
}
ImrMask & ImrMask::operator+=(const int & rhs){
    size_t len=this->masksize.high * this->masksize.width;
    for(unsigned i = 0; i < len; ++i)
        (*this)[i] += rhs;
    return (*this);
}
ImrMask & ImrMask::operator-=(const int & rhs){
    size_t len=this->masksize.high * this->masksize.width;
    for(unsigned i = 0; i < len; ++i)
        (*this)[i] -= rhs;
    return (*this);
}
/*
       ##

     ####     ### ##    ######  ## ###    ######  ##   ##
       ##     ## # ##  ##   ##  ###      ##   ##  ## # ##
       ##     ## # ##  ##   ##  ##       ##   ##  ## # ##
       ##     ## # ##   ######  ##       ##  ###  ## # ##
     ######   ##   ##       ##  ##        ### ##   ## ##
                        #####
*/
// 重載下標符號
imch& imgraw::operator[](const size_t idx){
    return const_cast<imch&>(static_cast<const imgraw&>(*this)[idx]);
}
const imch& imgraw::operator[](const size_t idx) const{
    return this->img_data[idx];
}
// 重載加減符號
imgraw imgraw::operator+(const imgraw &p){
    // 獲得最大長度
    size_t y = this->high>p.high? this->high: p.high;
    size_t x = this->width>p.width? this->width: p.width;
    // 創建暫存影像
    imgraw temp(ImrSize(y, x));
    // 取得影像總像素
    int len = (int)this->high * (int)this->width;
    // 單點相加
    for (int i = 0; i < len; ++i){
        if ((double)(*this)[i]+(double)p[i] > (double)255){
            temp[i] = (imch)255;
        }
        else{
            temp[i] = (*this)[i]+p[i];
        }
    }
    return temp;
}
imgraw imgraw::operator+(const imch value){
    // 獲得最大長度
    size_t y = this->high;
    size_t x = this->width;
    // 創建暫存影像
    imgraw temp(ImrSize(y, x));
    // 取得影像總像素
    int len = (int)this->high * (int)this->width;
    // 單點相加
    for (int i = 0; i < len; ++i){
        if ((double)(*this)[i]+value > (double)255){
            temp[i] = (imch)255;
        }
        else{
            temp[i] = (*this)[i]+value;
        }
    }
    return temp;
}
imgraw imgraw::operator-(const imgraw &p){
    // 獲得最大長度
    size_t y = this->high>p.high? this->high: p.high;
    size_t x = this->width>p.width? this->width: p.width;
    // 創建暫存影像
    imgraw temp(ImrSize(y, x));
    // 取得影像總像素
    int len = (int)this->high * (int)this->width;
    // 單點相減
    for (int i = 0; i < len; ++i){
        if ((double)(*this)[i]-(double)p[i] < 0){
            temp[i] = (imch)0;
        }
        else{
            temp[i] = (*this)[i]-p[i];
        }
    }
    return temp;
}
imgraw imgraw::operator-(const imch value){
    // 獲得最大長度
    size_t y = this->high;
    size_t x = this->width;
    // 創建暫存影像
    imgraw temp(ImrSize(y, x));
    // 取得影像總像素
    int len = (int)this->high * (int)this->width;
    // 單點相加
    for (int i = 0; i < len; ++i){
        if ((double)(*this)[i]-value < (double)0){
            temp[i] = (imch)0;
        }
        else{
            temp[i] = (*this)[i]-value;
        }
    }
    return temp;
}
} //imr