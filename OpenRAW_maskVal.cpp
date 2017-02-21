/**********************************************************
Name : OpenRAW_maskVal �����d��
Date : 2016/10/04
By   : CharlotteHonG
Final: 2017/02/21
**********************************************************/
#include <iostream>
#include "OpenRAW_fun\OpenRAW.hpp"
// Visual Studio �sĶ�ݧR���Ӧ�P���ɮ�
#include "OpenRAW.cpp" // GCC���ɽsĶ��
using namespace std;
using namespace imr;

#define AutoOpen 0
#define Pic_name_in "IMG.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 256
#define Pic_y 256

int main(int argc, char const *argv[]) {
    // �Ыصe��
    imgraw img(ImrSize(Pic_y, Pic_x));
    // Ū���ɮ�
    img.read(Pic_name_in);
    //---------------------------------------------------------
    // Ū��Mask�Ϊk(�W�L��ɷ|�����)
    cout << endl<< "maskVal" << endl;
    for(int j = 51; j < 54; ++j){
        for(int i = 51; i < 54; ++i) {
            ImrCoor ori(0,0);
            ImrCoor mas(j,i);
            // maskVal(���I�A�B�n�I)
            cout << setw(4) << (int)img.maskVal(ori,mas);
        }cout << endl;
    }
    // ��Ϥ��
    img.pri_blk("Origin", ImrCoor(50, 50), ImrSize(4, 4));
    //---------------------------------------------------------
    // ���ܰT��
    img.info("img");
    //---------------------------------------------------------
    // ��X�ɮ�
    img.write(Pic_name_out);
    // �}���ɮ�
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}