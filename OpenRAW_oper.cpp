/*****************************************************************
Name : 
Date : 2017/02/23
By   : CharlotteHonG
Final: 2017/02/23
*****************************************************************/
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
    // 創建畫布
    imgraw img(ImrSize(Pic_y, Pic_x));
    // 讀取檔案
    img.read(Pic_name_in);
    // ImrCoor 加減運算
    ImrCoor p, p1(1, 2), p2(3, 4);
    p=p1+p2; p.info();
    p=p1-p2; p.info();
    cout << endl;
    p+=1; p.info();
    p-=1; p.info();
    cout << endl;




    // 輸出檔案
    img.write(Pic_name_out);
    // 開啟檔案
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}
/*==============================================================*/