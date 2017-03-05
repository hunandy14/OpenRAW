/**********************************************************
Name : ImrMask ��@
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
// �Ƨǰ}�C(���סA�_�l�I)
void ImrMask::sort(size_t len=0, size_t start=0) {
    int temp;
    int* arr = &this->mask[start];
    // ���׬�0�ɦ۰ʿ����
    if (len == 0)
        len = this->masksize.high*this->masksize.width;
    // ���J�ƧǪk
    for (int i=1, j; i<(int)len; i++) {
        temp = arr[i];
        for (j=i-1; j>=0 && arr[j]>temp; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
}
// �H�G���覡Ū���μg�J
int& ImrMask::at2d(size_t y, size_t x){
    return const_cast<int&>(
        static_cast<const ImrMask&>(*this).at2d(y, x));
}
const int& ImrMask::at2d(size_t y, size_t x) const{
    size_t pos = (y*this->masksize.width) + x;
    return this->mask[pos];
}
// ���]�j�p
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
// �L�X��T
void ImrMask::info(string name=""){
    cout << name << endl;
    for (unsigned j = 0; j < masksize.high; ++j){
        for (unsigned i = 0; i < masksize.width; ++i){
            cout << setw(4) << this->at2d(j, i);
        }cout << endl;
    }cout << endl;
}
// ���o������
int ImrMask::avg(){
    double long temp=0;
    size_t len=this->masksize.high * this->masksize.width;
    for (unsigned i = 0; i < len; ++i)
        temp += (double)(*this)[i];
    return (int)((temp/len)+0.5);
}
// ���o����
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
    // �ƻs�B�n���e
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
    // �h�ƨM (��^�h��)
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
    // ��R
    auto&& fill = [&](size_t idx){
        bool val = maj(idx);
        idx = one_byte-idx-1;
        for(unsigned i = 0; i < len; ++i) {
            // �����M��P�h�Ƥ��@�˪�(�Q�^�O)
            if(bit[i][idx] != val) {
                // cout << i << "!=val";
                // ���@�˪̦p�G��1�h����J1
                if(val != true and list[i]==false) {
                    // cout << "---fill";
                    bit[i].set();
                } else if(val != false and list[i]==false){
                    // cout << "---fill";
                    bit[i].reset();
                }
                // �����w��L��
                list[i] = true;
                // cout << endl;
            }
        }
    };
    // ��R�����è���
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