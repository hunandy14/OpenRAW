/**********************************************************
Name : imgraw ��@
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW.hpp"
namespace imr{
/*
       ##

     ####     ### ##    ######  ## ###    ######  ##   ##
       ##     ## # ##  ##   ##  ###      ##   ##  ## # ##
       ##     ## # ##  ##   ##  ##       ##   ##  ## # ##
       ##     ## # ##   ######  ##       ##  ###  ## # ##
     ######   ##   ##       ##  ##        ### ##   ## ##
                        #####
*/
// �פJ�ɮ�
void imgraw::read(string filename) {
    this->filename = filename;
    // �G�i��Ҧ��}�ɴ���
    fstream img;
    img.open(filename, ios::in | ios::binary);
    // �p�G�}���ɮץ��ѡAfp��0�F���\�Afp���D0
    if(!img) {
        img.close();
        cout << "No file." << endl;
        exit(1);
    }
    else {
        // cout << "File ok." << endl;
    } img.close();
    // �G�i��Ҧ�Ū��
    // ���o�`��
    img.open(this->filename, ios::in | ios::binary);
    img.seekg(0, ios::end);
    this->filesize = img.tellg();
    img.seekg(0, ios::beg);
    // Ū����
    this->img_data.vector::resize(this->filesize);
    img.read((char*)&this->img_data[0], this->filesize);
    img.close();
}
// �N�O�����ƶץX
void imgraw::write(string filename) {
    // �i��Ҧ��g��
    fstream img;
    img.open(filename, ios::out | ios::binary);
    img.write((char*)&img_data[0], this->filesize);
    img.close();
}
// Ū�ɳ��I(�ˬd���)
imch imgraw::point_read(imint y, imint x) {
    imint pos = (y*this->width)+x;
    return this->img_data.at(pos);
}
// �g�J�O������I(�ˬd���)
void imgraw::point_write(imint y, imint x, imch value) {
    imint pos = (y*this->width)+x;
    this->img_data.vector::at(pos) = value;
}
// �H�G���覡Ū���μg�J(�ˬd���)
imch& imgraw::at2d(size_t y, size_t x){
    size_t pos = (y*this->width)+x;
    return this->img_data.at(pos);
}
const imch& imgraw::at2d(size_t y, size_t x) const{
    size_t pos = (y*this->width)+x;
    return this->img_data.at(pos);
}
// �վ�e���j�p
void imgraw::resize_canvas(ImrSize size) {
    imint x = size.width;
    imint y = size.high;
    // cout << "x=" << x << endl;
    // cout << "y=" << y << endl;
    this->width = x;
    this->high = y;
}
// ��o�e
imint imgraw::w() {
    return this->width;
}
// ��o��
imint imgraw::h() {
    return this->high;
}
// �L�X�e���j�p
void imgraw::info(){
    cout << "�e���j�p(�ex��) = " << this->width
         << " x " << this->high << endl;
}
// �G�Ȥ�(�ɽu, ���ƭ�, �I���ƭ�)
void imgraw::binarizae(imch value=128,
        imch high=255, imch low=0)
{
    int len = this->width * this->high;
    // cout << "this[0]=" << (*this)[0] << endl;
    for (int i = 0; i < len; ++i)
    {
        if( (*this)[i] > value ) {
            (*this)[i] = high;
        }else{
            (*this)[i] = low;
        }
    }
}
// �@�����Ҧ�����(��諸�ƭ�)
void imgraw::value(imch value){
    int len = this->width * this->high;
    for (int i = 0; i < len; ++i){
        (*this)[i] = value;
    }
}
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
// ���o�B�n�A�^�Ǥ@���}�C(���I��m�A�첾����)
ImrMask imgraw::getMask(ImrCoor ori, 
        ImrCoor shi = ImrCoor(-1,-1))
{
    if (this->masksize.high == 0
        && this->masksize.width == 0){
        cout << "Error! Uninit masksize." << endl;
        return ImrMask(ImrSize(0, 0));
    }
    // �ЫذʺA�}�C
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
    // �L�X
    // for (int j = 0; j < 3; ++j){
    //     for (int i = 0; i < 3; ++i){
    //         cout << mask.at2d(j,i);
    //     }cout << endl;
    // }
    // return ImrMask();
    return mask;
}
// �]�w�B�n
void imgraw::setMaskSize(ImrSize masksize){
    this->masksize = masksize;
}
/*

    #    # #  ####  #####  ####   ####  #####    ##   #    #
    #    # # #        #   #    # #    # #    #  #  #  ##  ##
    ###### #  ####    #   #    # #      #    # #    # # ## #
    #    # #      #   #   #    # #  ### #####  ###### #    #
    #    # # #    #   #   #    # #    # #   #  #    # #    #
    #    # #  ####    #    ####   ####  #    # #    # #    #
*/
// �L�X�����
void imgraw::pri_htg(string title=""){
    // ���o�ƾ�
    this->histogram();
    // ���Y�ƾ�
    int htg_comp[32]={0};
    for (int i = 0; i < 32; ++i){
        htg_comp[i]=(
            htg_data[(i*8)+0]+
            htg_data[(i*8)+1]+ 
            htg_data[(i*8)+2]+ 
            htg_data[(i*8)+3]+
            htg_data[(i*8)+4]+
            htg_data[(i*8)+5]+
            htg_data[(i*8)+6]+
            htg_data[(i*8)+7]
        );
    }
    // ��̰���
    int htg_high=0;
    for (int i = 0; i < 32; ++i){
        if (htg_comp[i]>htg_high){
            htg_high = htg_comp[i];
        }
    }
    // �ഫ����
    int htg_rate[32]={0};
    for (int i = 0; i < 32; ++i){
        htg_rate[i] = (int)((double)htg_comp[i]
            / (double)htg_high*32);
    }
    // �ഫ�r��
    string str[32][32];
    for (int j = 0; j < 32; ++j){
        for (int i = 0; i < htg_rate[j]; ++i){
            str[j][i]+=" �m";
        }
    }
    // ���o��ƪ���
    string temp;
    stringstream ss;
    ss << htg_high;
    temp.clear();
    ss >> temp;
    ss.clear();
    // �L�X
    cout << endl << setw((64-3)-(title.length()/2));
    cout << title << endl;
    for (int i = 31; i >= 0; --i){
        cout << setw(temp.length()) 
             << htg_high/32*(i+1) << " ";
        for (int j = 0; j < 32; ++j){
            cout << setw(3) <<str[j][i];
        }
        cout << endl;   
    }
    // �ƾڻ�����
    cout << setw(3) << "";
    for (int i = 0; i < 32/2; ++i){
        cout << setw(6) << (i+1)*16;  
    }
    cout << "" << endl;
}
// ���o�ƾڲέp(�ƭ�0~255���X��)
void imgraw::histogram(){
    int s=this->width * this->high;
    int temp;
    // �k�s
    for (int i = 0; i < 256; ++i)
        this->htg_data[i]=0;
    // ���o�ƾ�
    for (int i = 0; i < s; ++i){
        temp = (int)this->img_data.at(i);
        ++this->htg_data[temp];
    }
}
// ���o�ƾڷ���
void imgraw::extremum(){
    imch temp;
    this->min=255;
    this->max=0;
    for (int j = 0; j < (int)this->high; ++j){
        for (int i = 0; i < (int)this->width; ++i){
            temp = this->at2d(j,i);
            if (temp > this->max){
                this->max = temp;
            }else if (temp < this->min){
                this->min = temp;
            }
        }
    }
}
} // imr