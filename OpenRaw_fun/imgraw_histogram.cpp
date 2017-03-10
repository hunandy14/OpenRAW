/*****************************************************************
Name : 
Date : 2017/03/10
By   : CharlotteHonG
Final: 2017/03/10
*****************************************************************/
#include "OpenRAW.hpp"

namespace imr {
/*

    #    # #  ####  #####  ####   ####  #####    ##   #    #
    #    # # #        #   #    # #    # #    #  #  #  ##  ##
    ###### #  ####    #   #    # #      #    # #    # # ## #
    #    # #      #   #   #    # #  ### #####  ###### #    #
    #    # # #    #   #   #    # #    # #   #  #    # #    #
    #    # #  ####    #    ####   ####  #    # #    # #    #
*/
// ���o�ƾڷ���
void imgraw::extremum(){
    imch temp;
    this->min=255;
    this->max=0;
    for (unsigned j = 0; j < this->high; ++j){
        for (unsigned i = 0; i < this->width; ++i){
            temp = this->at2d(j,i);
            if (temp > this->max){
                this->max = temp;
            }else if (temp < this->min){
                this->min = temp;
            }
        }
    }
}
// ���o�ƾڲέp(�ƭ�0~255���X��)
void imgraw::histogram(){
    // �k�s
    for(auto&& i : this->htg_data)
        i=0;
    // ���o�ƾ�
    int len = this->width*this->high;
    for (int i = 0; i < len; ++i){
        size_t idx = (int)this->img_data[i];
        ++this->htg_data[idx];
    }
}
// �L�X�����
void imgraw::pri_htg(string title=""){
    // ���o�ƾڲέp
    this->histogram();
    // ���Y�ƾ�
    size_t epart=32; // ���Y�X����(��)
    double piece=one_level/epart; // �@����
    size_t htg_comp[epart]{};
    for (unsigned j = 0; j < epart; ++j){
        for(unsigned i = 0; i < piece; ++i){
            size_t idx = j*piece+i;
            htg_comp[j] += htg_data[idx];
        }
    }
    // ��̰���
    size_t htg_high=0;
    for (unsigned i = 0; i < epart; ++i)
        if (htg_comp[i]>htg_high)
            htg_high = htg_comp[i];
    // �ഫ����(�|�ˤ��J)
    double htg_rate[epart]{};
    for (unsigned i = 0; i < epart; ++i){
        htg_rate[i] = round((double)htg_comp[i]
            / (double)htg_high*(double)epart);
    }
    // �ഫ�r��
    string htg_str[epart][epart];
    for (unsigned j = 0; j < epart; ++j)
        for (unsigned i = 0; i < htg_rate[j]; ++i)
            htg_str[j][i]+=" �m";
    // ���o�̤j�ȼƪ����(��������Ů��)
    string temp;
    stringstream ss;
    ss << htg_high;
    temp.clear();
    ss >> temp;
    ss.clear();
    // �L�X
    size_t space=3; // �ϧΪ����j
    cout << endl << setw((64-3)-(title.length()/2));
    cout << title << endl;
    for (int i = epart-1; i >= 0; --i){
        // �������d����
        cout << setw(temp.length())
             << htg_high/epart*(i+1) << " ";
        // �ϧ�
        for (unsigned j = 0; j < epart; ++j)
            cout << setw(space) <<htg_str[j][i];
        cout << endl;
    }
    // �ƾڻ�����
    for (unsigned i = 0; i < epart/2; ++i){
        cout << setw(6) << (i+1)*16;
    }cout << endl;
    // ���L����
    this->extremum();
    cout << "max=" << (int)max << ", ";
    cout << "min=" << (int)min << endl;
}
} // imr