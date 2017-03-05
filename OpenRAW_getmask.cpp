/**********************************************************
Name : OpenRAW_getmask 說明範例
Date : 2016/10/04
By   : CharlotteHonG
Final: 2017/02/21
**********************************************************/
#include <iostream>
#include "OpenRAW_fun\OpenRAW.hpp"
// Visual Studio 編譯需刪除該行與該檔案
#include "OpenRAW.cpp" // GCC單檔編譯用
using namespace std;
using namespace imr;

#define AutoOpen 0
#define Pic_name_in "IMG.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 256
#define Pic_y 256

int main(int argc, char const *argv[]) {
    // 初始化亂數種子
    srand((unsigned)time(NULL)); rand();
    // 創建畫布
    imgraw img(ImrSize(Pic_y, Pic_x));
    // 讀取檔案
    img.read(Pic_name_in);
    //---------------------------------------------------------
    // 設定遮罩(預設為3x3)
    img.setMaskSize(ImrSize(3,3));
    // 取得Mask陣列及排續 getMask(原點位置, 偏移位置(預設 -1, -1))
    ImrMask mask(img.getMask(ImrCoor(1,1)));
    mask.info("setMaskSize");
    // 原圖比較
    img.pri_blk("Origin", ImrCoor(0, 0), ImrSize(3, 3));
    // 排序
    mask.sort();
    mask.info("sort");
    // 取平均值
    cout << "avg = " << (int)mask.avg() << endl;
    // 取中值
    cout << "median = " << (int)mask.median() << endl;
    // 初值陣列
    ImrMask a{
        1, 2, 3, 
        4, 5, 6, 
        7, 8, 9
    };
    a.info("initializer_list");
    // 取中值2
    cout << "a.median2() = " << a.median2() << endl;
    //---------------------------------------------------------
    // 提示訊息
    img.info("img");
    //---------------------------------------------------------
    // 輸出檔案
    img.write(Pic_name_out);
    // 開啟檔案
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}