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
    fstream img_file;
    img_file.open(filename, ios::out | ios::binary);
    img_file.write((char*)&img_data[0], this->filesize);
    img_file.close();
}
// �H�G���覡Ū���μg�J(�ˬd���)
imch& imgraw::at2d(size_t y, size_t x){
    return const_cast<imch&>(
        static_cast<const imgraw&>(*this).at2d(y, x));
}
const imch& imgraw::at2d(size_t y, size_t x) const{
    size_t pos = (y*this->width)+x;
    return this->img_data.at(pos);
}
// �վ�e���j�p
void imgraw::resize_canvas(size_t size) {
    this->width = 0;
    this->high = 0;
    this->img_data.vector::resize(size);
    this->filesize = size;
}
void imgraw::resize_canvas(ImrSize size) {
    size_t y=size.high, x=size.width;
    this->width = x;
    this->high = y;
    this->img_data.vector::resize(x*y);
    this->filesize = x*y;
}
// �L�X�e���j�p
void imgraw::info(string name=""){
    cout << "[" << name << "]�e���j�p(�ex��) = ";
    cout << this->width << " x " << this->high << endl;
}
// �G�Ȥ�(�ɽu, ���ƭ�, �I���ƭ�)
void imgraw::binarizae(imch value=128,
        imch high=255, imch low=0)
{
    size_t len = this->width * this->high;
    for (unsigned i = 0; i < len; ++i)
        (*this)[i] = (*this)[i]>value? high: low;
}
// �@�����Ҧ�����(��諸�ƭ�)
void imgraw::value(imch value){
    for(auto&& i : this->img_data)
        i = value;
}
// �H���^�Ǥ@���I
imch & imgraw::random(){
    return const_cast<imch&>(static_cast<const imgraw&>(*this).random());
}
const imch & imgraw::random() const{
    int up=this->filesize, low=0;
    size_t idx = ((rand() / (RAND_MAX+1.0)) * (up - low) + low);
    return (*this)[idx];
}
// �϶����L
void imgraw::pri_blk(string name, ImrCoor pos, ImrSize masksize){
    cout << name << endl;
    for(unsigned j = pos.y; j < pos.y+masksize.high; ++j){
        for(unsigned i = pos.x; i < pos.x+masksize.width; ++i) {
            cout << setw(4) << (int)(*this).at2d(j, i);
        }cout << endl;
    }cout << endl;
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