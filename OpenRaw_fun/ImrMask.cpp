/**********************************************************
Name : ImrMask 實作
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW.hpp"
namespace imr{
/*
    ###               #     #
     #  #    # #####  ##   ##   ##    ####  #    #
     #  ##  ## #    # # # # #  #  #  #      #   #
     #  # ## # #    # #  #  # #    #  ####  ####
     #  #    # #####  #     # ######      # #  #
     #  #    # #   #  #     # #    # #    # #   #
    ### #    # #    # #     # #    #  ####  #    #
*/
// 排序陣列(長度，起始點)
void ImrMask::sort(size_t len=0, size_t start=0) {
    int temp;
    int* arr = &this->mask[start];
    // 長度為0時自動選全部
    if (len == 0)
        len = this->masksize.high*this->masksize.width;
    // 插入排序法
    for (int i=1, j; i<(int)len; i++) {
        temp = arr[i];
        for (j=i-1; j>=0 && arr[j]>temp; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
}
// 以二維方式讀取或寫入
int& ImrMask::at2d(size_t y, size_t x){
    return const_cast<int&>(
        static_cast<const ImrMask&>(*this).at2d(y, x));
}
const int& ImrMask::at2d(size_t y, size_t x) const{
    size_t pos = (y*this->masksize.width) + x;
    return this->mask[pos];
}
// 印出資訊
void ImrMask::info(string name=""){
    cout << name << endl;
    for (unsigned j = 0; j < masksize.high; ++j){
        for (unsigned i = 0; i < masksize.width; ++i){
            cout << setw(4) << (size_t)this->at2d(j, i);
        }cout << endl;
    }cout << endl;
}
// 取得平均值
int ImrMask::avg(){
    double long temp=0;
    size_t len=this->masksize.high * this->masksize.width;
    for (unsigned i = 0; i < len; ++i)
        temp += (double)(*this)[i];
    return (int)((temp/len)+0.5);
}
// 取得中值
int ImrMask::median(){
    size_t len=this->masksize.high * this->masksize.width;
    if(len==0)
        return 0;
    size_t idx=floor(len/2);
    this->sort();
    return (*this)[idx];
}
int ImrMask::median2(){
    int temp(0);
    auto bit = [&](size_t idx){
        return static_cast<bitset<one_byte>>(mask[idx]);
    };
    cout << "bit = " << bit(0) << endl;
    return temp;
}
} //imr