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
// 取得數據極值
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
// 取得數據統計(數值0~255有幾個)
void imgraw::histogram(){
    // 歸零
    for(auto&& i : this->htg_data)
        i=0;
    // 取得數據
    int len = this->width*this->high;
    for (int i = 0; i < len; ++i){
        size_t idx = (int)this->img_data[i];
        ++this->htg_data[idx];
    }
}
// 印出直方圖
void imgraw::pri_htg(string title=""){
    // 取得數據統計
    this->histogram();
    // 壓縮數據
    size_t epart=32; // 壓縮幾等分(高)
    double piece=one_level/epart; // 一等份
    size_t htg_comp[epart]{};
    for (unsigned j = 0; j < epart; ++j){
        for(unsigned i = 0; i < piece; ++i){
            size_t idx = j*piece+i;
            htg_comp[j] += htg_data[idx];
        }
    }
    // 找最高值
    size_t htg_high=0;
    for (unsigned i = 0; i < epart; ++i)
        if (htg_comp[i]>htg_high)
            htg_high = htg_comp[i];
    // 轉換等比(四捨五入)
    double htg_rate[epart]{};
    for (unsigned i = 0; i < epart; ++i){
        htg_rate[i] = round((double)htg_comp[i]
            / (double)htg_high*(double)epart);
    }
    // 轉換字串
    string htg_str[epart][epart];
    for (unsigned j = 0; j < epart; ++j)
        for (unsigned i = 0; i < htg_rate[j]; ++i)
            htg_str[j][i]+=" ▌";
    // 取得最大值數的位數(左邊邊欄空格用)
    string temp;
    stringstream ss;
    ss << htg_high;
    temp.clear();
    ss >> temp;
    ss.clear();
    // 印出
    size_t space=3; // 圖形的間隔
    cout << endl << setw((64-3)-(title.length()/2));
    cout << title << endl;
    for (int i = epart-1; i >= 0; --i){
        // 左邊邊攔說明
        cout << setw(temp.length())
             << htg_high/epart*(i+1) << " ";
        // 圖形
        for (unsigned j = 0; j < epart; ++j)
            cout << setw(space) <<htg_str[j][i];
        cout << endl;
    }
    // 數據說明欄
    for (unsigned i = 0; i < epart/2; ++i){
        cout << setw(6) << (i+1)*16;
    }cout << endl;
    // 打印極值
    this->extremum();
    cout << "max=" << (int)max << ", ";
    cout << "min=" << (int)min << endl;
}
} // imr