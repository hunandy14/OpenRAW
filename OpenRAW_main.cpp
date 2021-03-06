/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2017/02/21
**********************************************************/
#include <iostream>
#include "OpenRAW_fun\OpenRAW.hpp"

using namespace std;
using namespace imr;

#define AutoOpen 1
#define Pic_name_in "IMG.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 256
#define Pic_y 256

int main(int argc, char const *argv[]) {
    // 初始化亂數種子
    srand((unsigned)time(NULL)); rand();
    // 創建畫布
    Imgraw img(ImrSize(Pic_y, Pic_x));
    // Imgraw img_2(ImrSize(Pic_y, Pic_x));
    Imgraw img_2(ImrSize(0, 0));
    img_2.resize(ImrSize(Pic_y, Pic_x));
    // 讀取檔案
    img.read(Pic_name_in);
    //---------------------------------------------------------
    // 單點操作
    for(int j = 0; j < Pic_y; ++j){
        for(int i = 0; i < Pic_x; ++i){
            // img_2[j*(Pic_x)+i]=img[j*(Pic_x)+i];
            img_2.at2d(j,i)=img.at2d(j,i);
        }
    }
    cout << "random-point=" << (int)img.random() << endl;
    // ---------------------------------------------------------
    // 提示訊息
    img_2.info("img_2");
    //---------------------------------------------------------
    // 輸出檔案
    img_2.write(Pic_name_out);
    // 開啟檔案
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}