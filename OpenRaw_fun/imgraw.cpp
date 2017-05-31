/**********************************************************
Name : Imgraw ��@
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
void Imgraw::read(string filename) {
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
    auto filesize = img.tellg();
    img.seekg(0, ios::beg);
    // Ū����
    this->img_data.vector::resize(filesize);
    img.read((char*)&this->img_data[0], filesize);
    img.close();
}
// �N�O�����ƶץX
void Imgraw::write(string filename) {
    // �i��Ҧ��g��
    fstream img_file;
    img_file.open(filename, ios::out | ios::binary);
    img_file.write((char*)&img_data[0], this->img_data.size());
    img_file.close();
}
// �G�Ȥ�(�ɽu, ���ƭ�, �I���ƭ�)
void Imgraw::binarizae(imch value=128,
        imch high=255, imch low=0)
{
    size_t len = this->width * this->high;
    for (unsigned i = 0; i < len; ++i)
        (*this)[i] = (*this)[i]>value? high: low;
}
// �@�����Ҧ�����(��諸�ƭ�)
void Imgraw::value(imch value){
    for(auto&& i : this->img_data)
        i = value;
}
// �Ϥ��j�p�O�_�ۦP
bool Imgraw::check_size(Imgraw const& rhs){
    if(this->width==rhs.width and this->high==rhs.high) {
        return 1;
    } return 0;
}
// �H���^�Ǥ@���I
imch & Imgraw::random(){
    return const_cast<imch&>(static_cast<const Imgraw&>(*this).random());
}
const imch & Imgraw::random() const{
    int up=this->img_data.size(), low=0;
    size_t idx = ((rand() / (RAND_MAX+1.0)) * (up - low) + low);
    return (*this)[idx];
}
// �϶����L
void Imgraw::pri_blk(string name, ImrCoor pos, ImrSize masksize){
    cout << name << endl;
    for(unsigned j = pos.y; j < pos.y+masksize.high; ++j){
        for(unsigned i = pos.x; i < pos.x+masksize.width; ++i) {
            cout << setw(4) << (int)(*this).at2d(j, i);
        }cout << endl;
    }cout << endl;
}
} // imr