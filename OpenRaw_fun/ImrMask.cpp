/**********************************************************
Name : ImrMask 實作
Date : 2016/10/03
By   : CharlotteHonG
Final: 2017/03/05
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
// 重設大小
ImrMask & ImrMask::resize(ImrSize masksize){
    ImrMask temp(masksize);
    for(unsigned j = 0; j < this->masksize.high; ++j) {
        for(unsigned i = 0; i < this->masksize.width; ++i) {
            temp.at2d(j, i) = (*this).at2d(j, i);
        }
    } (*this) = temp;
    return (*this);
}
ImrMask & ImrMask::fixval(){
    for(auto&& i : this->mask) {
        if(i > 255) {
            i = 255;
        } else if(i < 0) {
            i = 0;
        }
    }
    return (*this);
}
// 印出資訊
void ImrMask::info(string name=""){
    cout << name << endl;
    for (unsigned j = 0; j < masksize.high; ++j){
        for (unsigned i = 0; i < masksize.width; ++i){
            cout << setw(4) << this->at2d(j, i);
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
    if(len==0 or len%2 != 1) {
        cout << "  **Error! Even or Len is Zero." << endl;
        return -1;
    }
    size_t idx=floor(len/2);
    this->sort();
    return (*this)[idx];
}

int ImrMask::median2(){
    size_t len = this->masksize.high * this->masksize.width;
    if(len==0 or len%2 != 1) {       
        cout << "  **Error! Even or Len is Zero." << endl;
        return -1;
    }
    // 複製遮罩內容
    vector<bitset<one_byte>> bit(len);
    vector<bool> list(len);
    for(unsigned i = 0; i < len; ++i) {
        if((*this)[i] < 0) {
            cout << "  **Error! Negative" << endl;
            return -1;
        }
        bit[i] = (*this)[i];
        // cout << "bit = " << bit[i] << endl;
    }
    // 多數決 (返回多數)
    auto&& maj = [&](size_t idx){
        idx = one_byte-idx-1;
        int temp=0;
        for(unsigned i = 0; i < len; ++i) {
            if(bit[i][idx]==1) {
                ++temp;
            } else if (bit[i][idx]==0){
                --temp;
            }
        } return temp>0? 1:0;
    };
    // 填充
    auto&& fill = [&](size_t idx){
        bool val = maj(idx);
        idx = one_byte-idx-1;
        for(unsigned i = 0; i < len; ++i) {
            // 垂直尋找與多數不一樣者(被淘汰)
            if(bit[i][idx] != val) {
                // cout << i << "!=val";
                // 不一樣者如果為1則全填入1
                if(val != true and list[i]==false) {
                    // cout << "---fill";
                    bit[i].set();
                } else if(val != false and list[i]==false){
                    // cout << "---fill";
                    bit[i].reset();
                }
                // 紀錄已填過的
                list[i] = true;
                // cout << endl;
            }
        }
    };
    // 填充全部並取值
    auto&& median_num = [&](){
        for(unsigned i = 0; i < len; ++i) {
            fill(i);
        }
        for(unsigned i = 0; i < len; ++i) {
            if(list[i] == false) {
                return (int)i;
            }
        }
        return -1;
    };
    return (*this)[median_num()];
}
} //imr