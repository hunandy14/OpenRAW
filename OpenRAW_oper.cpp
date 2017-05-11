/*****************************************************************
Name : 
Date : 2017/02/23
By   : CharlotteHonG
Final: 2017/02/23
*****************************************************************/
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
    // ImrCoor �[��B��
    ImrCoor p, p1(1, 2), p2(3, 4);
    p=p1+p2; p.info();
    p=p1-p2; p.info();
    cout << endl;
    p+=1; p.info();
    p-=1; p.info();
    cout << endl;
    // imgraw ��z�ƭȥ[��
    img.pri_blk("img", ImrCoor(0, 0), ImrSize(4, 4));
    img+=1;
    img.pri_blk("img", ImrCoor(0, 0), ImrSize(4, 4));
    img-=1;
    img.pri_blk("img", ImrCoor(0, 0), ImrSize(4, 4));
    // 
    ImrSize a(4, 4);
    ImrSize b(4, 4);
    if(a==b) {
        cout << "123" << endl;
    }


    // ��X�ɮ�
    img.write(Pic_name_out);
    // �}���ɮ�
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}
/*==============================================================*/