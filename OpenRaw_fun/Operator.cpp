/**********************************************************
Name : 運算子重載
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
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
ImrCoor operator*(ImrCoor const &lhs, ImrCoor const &rhs){
    return ImrCoor(lhs) *= rhs;
}
ImrCoor operator/(ImrCoor const &lhs, ImrCoor const &rhs){
    return ImrCoor(lhs) /= rhs;
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
ImrCoor & ImrCoor::operator*=(const ImrCoor &rhs){
    this->y *= rhs.y;
    this->x *= rhs.x;
    return *this;
}
ImrCoor & ImrCoor::operator/=(const ImrCoor &rhs){
    this->y /= rhs.y;
    this->x /= rhs.x;
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

imch& ImrMask::operator[](const size_t __n){
    return const_cast<imch&>(static_cast<const ImrMask&>(*this)[__n]);;
}
const imch& ImrMask::operator[](const size_t __n) const{
    return this->mask[__n];
}
ImrMask ImrMask::operator+(const ImrMask &p){
    // 獲得最大長度
    size_t y_max = this->masksize.high>p.masksize.high?
                this->masksize.high: p.masksize.high;
    size_t x_max = this->masksize.width>p.masksize.width?
                this->masksize.width: p.masksize.width;
    // 獲得最小長度
    size_t y_min = this->masksize.high<p.masksize.high? 
                this->masksize.high: p.masksize.high;
    size_t x_min = this->masksize.width<p.masksize.width?
                this->masksize.width: p.masksize.width;
    // 創建暫存影像
    ImrMask temp(ImrSize(y_max, x_max));
    // 單點相加
    for (int j = 0; j < (int)y_min; ++j){
        for (int i = 0; i < (int)x_min; ++i){
            double num = (double)this->at2d(j, i)
                + (double)p.at2d(j, i);
            if (num > (double)255){
                temp.at2d(j, i) = (imch)255;
            }
            else{
                temp.at2d(j, i) = (*this)[i]+p[i];
            }
        }
    }
    return temp;
}
ImrMask ImrMask::operator-(const ImrMask &p){
    // 獲得最大長度
    size_t y_max = this->masksize.high>p.masksize.high?
                this->masksize.high: p.masksize.high;
    size_t x_max = this->masksize.width>p.masksize.width?
                this->masksize.width: p.masksize.width;
    // 獲得最小長度
    size_t y_min = this->masksize.high<p.masksize.high? this->masksize.high: p.masksize.high;
    size_t x_min = this->masksize.width<p.masksize.width? this->masksize.width: p.masksize.width;
    // 創建暫存影像
    ImrMask temp(ImrSize(y_max, x_max));
    // 單點相加
    for (int j = 0; j < (int)y_min; ++j){
        for (int i = 0; i < (int)x_min; ++i){
            double num = (double)this->at2d(j, i)
                - (double)p.at2d(j, i);
            if (num < (double)0){
                temp.at2d(j, i) = (imch)0;
            }
            else{
                temp.at2d(j, i) = (*this)[i]-p[i];
            }
        }
    }
    return temp;
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
imch& imgraw::operator[](const size_t __n){
    return const_cast<imch&>(static_cast<const imgraw&>(*this)[__n]);
}
const imch& imgraw::operator[](const size_t __n) const{
    return this->img_data[__n];
}
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