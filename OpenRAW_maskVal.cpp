/**********************************************************
Name : OpenRAW_maskVal �����d��
Date : 2016/10/04
By   : CharlotteHonG
Final: 2016/10/13
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
    cout << endl<< "Original" << endl;
    for(int j = 50; j < 54; ++j){
        for(int i = 50; i < 54; ++i) {
            cout << setw(4) << (int)img.at2d(j,i);
        }cout << endl;
    }
    //---------------------------------------------------------
    // ���ܰT��
    img.info();
    //---------------------------------------------------------
    // ��X�ɮ�
    img.write(Pic_name_out);
    // �}���ɮ�
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}