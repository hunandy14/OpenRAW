/*****************************************************************
Name : 
Date : 2017/03/10
By   : CharlotteHonG
Final: 2017/03/10
*****************************************************************/
#include "OpenRAW.hpp"

namespace imr {
/*
     ##   ##                    ##
     ##   ##                    ##
     ### ###   ######   #####   ##  ##
     ## # ##  ##   ##  ##       ## ##
     ## # ##  ##   ##   ####    ####
     ##   ##  ##  ###      ##   ## ##
     ##   ##   ### ##  #####    ##  ##

*/
// ���o�B�n�� (���I�A�B�n�y�СA�첾)
imch& imgraw::maskVal(ImrCoor ori, ImrCoor mas,
        ImrCoor shi=ImrCoor(-1,-1))
{
    // �^�ǥ��T��m���ƭ�
    return const_cast<imch&>(
        static_cast<const imgraw&>
        (*this).maskVal(ori, mas, shi)
    );
    // return this->at2d((pos.y), (pos.x));
}
const imch& imgraw::maskVal(ImrCoor ori, ImrCoor mas,
        ImrCoor shi=ImrCoor(-1,-1)) const
{
    // ���o������m
    ImrCoor pos = ori + mas + shi;
    // �ץ���t
    if (pos.y <0){
        pos.y = 0;
    }
    if (pos.y > (int)this->high-1){
        pos.y = (int)this->high-1;
    }
    if (pos.x <0){
        pos.x = 0;
    }
    if (pos.x > (int)this->width-1){
        pos.x = (int)this->width-1;
    }
    // �^�ǥ��T��m���ƭ�
    return this->at2d((pos.y), (pos.x));
}
// �]�w�B�n
void imgraw::setMaskSize(ImrSize masksize){
    this->masksize = masksize;
}
// ���o�B�n�A�^�Ǥ@���}�C(���I��m�A�첾����)
ImrMask imgraw::getMask(ImrCoor ori,
        ImrCoor shi = ImrCoor(-1,-1))
{
    // �Ы��{�ɾB�n
    ImrMask mask(this->masksize);
    // �ƻs�B�n
    for (int j = 0; j < (int)this->masksize.high; ++j){
        for (int i = 0; i < (int)this->masksize.width; ++i){
            // �B�n��m
            ImrCoor mas(j,i);
            // �ƻs�B�n�ƭ�
            mask.at2d(j,i)=this->maskVal(ori, mas, shi);
        }
    }
    return mask;
}
} // imr