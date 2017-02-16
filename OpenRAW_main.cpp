/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2017/02/14
**********************************************************/
#include <iostream>
#include "OpenRAW_fun\OpenRAW.hpp"
// Visual Studio �sĶ�ݧR���Ӧ�P���ɮ�
#include "OpenRAW.cpp" // GCC���ɽsĶ��

using namespace std;
using namespace imr;

#define AutoOpen 1
#define Pic_name_in "IMG.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 256
#define Pic_y 256

int main(int argc, char const *argv[]) {
    // �Ыصe��
    imgraw img(ImrSize(Pic_y, Pic_x));
    // imgraw img_2(ImrSize(Pic_y, Pic_x));
    imgraw img_2(ImrSize(0, 0));
    img_2.resize_canvas(ImrSize(Pic_y, Pic_x));
    // Ū���ɮ�
    img.read(Pic_name_in);
    //---------------------------------------------------------
    // ���I�ާ@
    for(int j = 0; j < Pic_y; ++j){
        for(int i = 0; i < Pic_x; ++i){
            // img2[j*(Pic_x)+i]=img[j*(Pic_x)+i];
            img_2.at2d(j,i)=img.at2d(j,i);
        }
    }
    //---------------------------------------------------------
    // ���ܰT��
    img_2.info();
    //---------------------------------------------------------
    // ��X�ɮ�
    img_2.write(Pic_name_out);
    // �}���ɮ�
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}