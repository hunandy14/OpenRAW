/**********************************************************
Name : Imgraw 實作
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
// 匯入檔案
void Imgraw::read(string filename) {
    this->filename = filename;
    // 二進位模式開檔測試
    fstream img;
    img.open(filename, ios::in | ios::binary);
    // 如果開啟檔案失敗，fp為0；成功，fp為非0
    if(!img) {
        img.close();
        cout << "No file." << endl;
        exit(1);
    }
    else {
        // cout << "File ok." << endl;
    } img.close();
    // 二進位模式讀檔
    // 取得總長
    img.open(this->filename, ios::in | ios::binary);
    img.seekg(0, ios::end);
    auto filesize = img.tellg();
    img.seekg(0, ios::beg);
    // 讀取值
    this->img_data.vector::resize(filesize);
    img.read((char*)&this->img_data[0], filesize);
    img.close();
}
// 將記憶體資料匯出
void Imgraw::write(string filename) {
    // 進位模式寫檔
    fstream img_file;
    img_file.open(filename, ios::out | ios::binary);
    img_file.write((char*)&img_data[0], this->img_data.size());
    img_file.close();
}
// 二值化(界線, 填色數值, 背景數值)
void Imgraw::binarizae(imch value=128,
        imch high=255, imch low=0)
{
    size_t len = this->width * this->high;
    for (unsigned i = 0; i < len; ++i)
        (*this)[i] = (*this)[i]>value? high: low;
}
// 一次更改所有像素(更改的數值)
void Imgraw::value(imch value){
    for(auto&& i : this->img_data)
        i = value;
}
// 圖片大小是否相同
bool Imgraw::check_size(Imgraw const& rhs){
    if(this->width==rhs.width and this->high==rhs.high) {
        return 1;
    } return 0;
}
// 隨機回傳一個點
imch & Imgraw::random(){
    return const_cast<imch&>(static_cast<const Imgraw&>(*this).random());
}
const imch & Imgraw::random() const{
    int up=this->img_data.size(), low=0;
    size_t idx = ((rand() / (RAND_MAX+1.0)) * (up - low) + low);
    return (*this)[idx];
}
// 區塊打印
void Imgraw::pri_blk(string name, ImrCoor pos, ImrSize masksize){
    cout << name << endl;
    for(unsigned j = pos.y; j < pos.y+masksize.high; ++j){
        for(unsigned i = pos.x; i < pos.x+masksize.width; ++i) {
            cout << setw(4) << (int)(*this).at2d(j, i);
        }cout << endl;
    }cout << endl;
}
} // imr