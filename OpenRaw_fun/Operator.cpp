/**********************************************************
Name : �\�������d
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
// ���d�˷�̖
int & ImrMask::operator[](const size_t idx){
    return const_cast<int&>(static_cast<const ImrMask&>(*this)[idx]);
}
const int & ImrMask::operator[](const size_t idx) const{
    return this->mask[idx];
}
// ���d�Ӝp��̖
ImrMask operator+(ImrMask const &lhs, ImrMask const &rhs){
    return ImrMask(lhs) += rhs;
}
ImrMask operator-(ImrMask const &lhs, ImrMask const &rhs){
    return ImrMask(lhs) -= rhs;
}
ImrMask & ImrMask::operator+=(const ImrMask &rhs){
    // �ж���С�Ƿ��Ǻ�
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
    // �ж���С�Ƿ��Ǻ�
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
// ���d�˷�̖
imch& imgraw::operator[](const size_t idx){
    return const_cast<imch&>(static_cast<const imgraw&>(*this)[idx]);
}
const imch& imgraw::operator[](const size_t idx) const{
    return this->img_data[idx];
}
// ���d�Ӝp��̖
imgraw imgraw::operator+(const imgraw &p){
    // �@������L��
    size_t y = this->high>p.high? this->high: p.high;
    size_t x = this->width>p.width? this->width: p.width;
    // ��������Ӱ��
    imgraw temp(ImrSize(y, x));
    // ȡ��Ӱ������
    int len = (int)this->high * (int)this->width;
    // ���c���
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
    // �@������L��
    size_t y = this->high;
    size_t x = this->width;
    // ��������Ӱ��
    imgraw temp(ImrSize(y, x));
    // ȡ��Ӱ������
    int len = (int)this->high * (int)this->width;
    // ���c���
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
    // �@������L��
    size_t y = this->high>p.high? this->high: p.high;
    size_t x = this->width>p.width? this->width: p.width;
    // ��������Ӱ��
    imgraw temp(ImrSize(y, x));
    // ȡ��Ӱ������
    int len = (int)this->high * (int)this->width;
    // ���c���p
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
    // �@������L��
    size_t y = this->high;
    size_t x = this->width;
    // ��������Ӱ��
    imgraw temp(ImrSize(y, x));
    // ȡ��Ӱ������
    int len = (int)this->high * (int)this->width;
    // ���c���
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