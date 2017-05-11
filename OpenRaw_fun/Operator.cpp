/**********************************************************
Name : �\�������d
Date : 2016/10/03
By   : CharlotteHonG
Final: 2017/03/05
**********************************************************/
#include "OpenRAW.hpp"
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
bool operator==(const ImrSize& lhs, const ImrSize& rhs){
    return (lhs.width==rhs.width and lhs.high==rhs.high);
}
/*
     ######                       ####
       ##                        ##  ##
       ##     ### ##   ## ###   ##        #####    #####   ## ###
       ##     ## # ##  ###      ##       ##   ##  ##   ##  ###
       ##     ## # ##  ##       ##       ##   ##  ##   ##  ##
       ##     ## # ##  ##        ##  ##  ##   ##  ##   ##  ##
     ######   ##   ##  ##         ####    #####    #####   ##

*/
ImrCoor const operator+(ImrCoor const &lhs, ImrCoor const &rhs){
    return ImrCoor(lhs) += rhs;
}
ImrCoor const operator-(ImrCoor const &lhs, ImrCoor const &rhs){
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
ImrCoor & ImrCoor::operator+=(const int & val){
    this->y += val;
    this->x += val;
    return *this;
}
ImrCoor & ImrCoor::operator-=(const int & val){
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
ImrMask const operator+(ImrMask const &lhs, ImrMask const &rhs){
    return ImrMask(lhs) += rhs;
}
ImrMask const operator-(ImrMask const &lhs, ImrMask const &rhs){
    return ImrMask(lhs) -= rhs;
}
ImrMask & ImrMask::operator+=(ImrMask const &rhs){
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
ImrMask & ImrMask::operator-=(ImrMask const &rhs){
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
imgraw & imgraw::operator+=(int const& rhs){
    for(unsigned i = 0; i < this->img_data.size(); ++i) {
        this->img_data[i] += static_cast<imch>(rhs);
    }return (*this);
}
imgraw & imgraw::operator-=(int const& rhs){
    for(unsigned i = 0; i < this->img_data.size(); ++i) {
        this->img_data[i] -= static_cast<imch>(rhs);
    }return (*this);
}
} //imr