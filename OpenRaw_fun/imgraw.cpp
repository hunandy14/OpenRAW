/**********************************************************
Name : imgraw 實作
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
void imgraw::read(string filename) {
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
    this->filesize = img.tellg();
    img.seekg(0, ios::beg);
    // 讀取值
    this->img_data.vector::resize(this->filesize);
    img.read((char*)&this->img_data[0], this->filesize);
    img.close();
}
// 將記憶體資料匯出
void imgraw::write(string filename) {
    // 進位模式寫檔
    fstream img_file;
    img_file.open(filename, ios::out | ios::binary);
    img_file.write((char*)&img_data[0], this->filesize);
    img_file.close();
}
// 以二維方式讀取或寫入(檢查邊界)
imch& imgraw::at2d(size_t y, size_t x){
    return const_cast<imch&>(
        static_cast<const imgraw&>(*this).at2d(y, x));
}
const imch& imgraw::at2d(size_t y, size_t x) const{
    size_t pos = (y*this->width)+x;
    return this->img_data.at(pos);
}
// 調整畫布大小
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
// 印出畫布大小
void imgraw::info(string name=""){
    cout << "[" << name << "]畫布大小(寬x長) = ";
    cout << this->width << " x " << this->high << endl;
}
// 二值化(界線, 填色數值, 背景數值)
void imgraw::binarizae(imch value=128,
        imch high=255, imch low=0)
{
    size_t len = this->width * this->high;
    for (unsigned i = 0; i < len; ++i)
        (*this)[i] = (*this)[i]>value? high: low;
}
// 一次更改所有像素(更改的數值)
void imgraw::value(imch value){
    for(auto&& i : this->img_data)
        i = value;
}
// 隨機回傳一個點
imch & imgraw::random(){
    return const_cast<imch&>(static_cast<const imgraw&>(*this).random());
}
const imch & imgraw::random() const{
    int up=this->filesize, low=0;
    size_t idx = ((rand() / (RAND_MAX+1.0)) * (up - low) + low);
    return (*this)[idx];
}
// 區塊打印
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
// 取得遮罩值 (原點，遮罩座標，位移)
imch& imgraw::maskVal(ImrCoor ori, ImrCoor mas,
        ImrCoor shi=ImrCoor(-1,-1))
{
    // 回傳正確位置的數值
    return const_cast<imch&>(
        static_cast<const imgraw&>
        (*this).maskVal(ori, mas, shi)
    );
    // return this->at2d((pos.y), (pos.x));
}
const imch& imgraw::maskVal(ImrCoor ori, ImrCoor mas,
        ImrCoor shi=ImrCoor(-1,-1)) const
{
    // 取得對應位置
    ImrCoor pos = ori + mas + shi;
    // 修正邊緣
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
    // 回傳正確位置的數值
    return this->at2d((pos.y), (pos.x));
}
// 設定遮罩
void imgraw::setMaskSize(ImrSize masksize){
    this->masksize = masksize;
}
// 取得遮罩，回傳一維陣列(原點位置，位移維度)
ImrMask imgraw::getMask(ImrCoor ori,
        ImrCoor shi = ImrCoor(-1,-1))
{
    if (this->masksize.high == 0
        or this->masksize.width == 0){
        cerr << "Error! Uninit masksize." << endl;
        return ImrMask(ImrSize(0, 0));
    }
    // 創建動態陣列
    ImrMask mask(this->masksize);
    // 複製遮罩
    for (int j = 0; j < (int)this->masksize.high; ++j){
        for (int i = 0; i < (int)this->masksize.width; ++i){
            // 遮罩位置
            ImrCoor mas(j,i);
            // 複製遮罩數值
            mask.at2d(j,i)=this->maskVal(ori, mas, shi);
        }
    }
    return mask;
}
/*

    #    # #  ####  #####  ####   ####  #####    ##   #    #
    #    # # #        #   #    # #    # #    #  #  #  ##  ##
    ###### #  ####    #   #    # #      #    # #    # # ## #
    #    # #      #   #   #    # #  ### #####  ###### #    #
    #    # # #    #   #   #    # #    # #   #  #    # #    #
    #    # #  ####    #    ####   ####  #    # #    # #    #
*/
// 取得數據極值
void imgraw::extremum(){
    imch temp;
    this->min=255;
    this->max=0;
    for (unsigned j = 0; j < this->high; ++j){
        for (unsigned i = 0; i < this->width; ++i){
            temp = this->at2d(j,i);
            if (temp > this->max){
                this->max = temp;
            }else if (temp < this->min){
                this->min = temp;
            }
        }
    }
}
// 取得數據統計(數值0~255有幾個)
void imgraw::histogram(){
    // 歸零
    for(auto&& i : this->htg_data)
        i=0;
    // 取得數據
    int len = this->width*this->high;
    for (int i = 0; i < len; ++i){
        size_t idx = (int)this->img_data[i];
        ++this->htg_data[idx];
    }
}
// 印出直方圖
void imgraw::pri_htg(string title=""){
    // 取得數據統計
    this->histogram();
    // 壓縮數據
    size_t epart=32; // 壓縮幾等分(高)
    double piece=one_byte/epart; // 一等份
    size_t htg_comp[epart]{};
    for (unsigned j = 0; j < epart; ++j){
        for(unsigned i = 0; i < piece; ++i){
            size_t idx = j*piece+i;
            htg_comp[j] += htg_data[idx];
        }
    }
    // 找最高值
    size_t htg_high=0;
    for (unsigned i = 0; i < epart; ++i)
        if (htg_comp[i]>htg_high)
            htg_high = htg_comp[i];
    // 轉換等比(四捨五入)
    double htg_rate[epart]{};
    for (unsigned i = 0; i < epart; ++i){
        htg_rate[i] = round((double)htg_comp[i]
            / (double)htg_high*(double)epart);
    }
    // 轉換字串
    string htg_str[epart][epart];
    for (unsigned j = 0; j < epart; ++j)
        for (unsigned i = 0; i < htg_rate[j]; ++i)
            htg_str[j][i]+=" ▌";
    // 取得最大值數的位數(左邊邊欄空格用)
    string temp;
    stringstream ss;
    ss << htg_high;
    temp.clear();
    ss >> temp;
    ss.clear();
    // 印出
    size_t space=3; // 圖形的間隔
    cout << endl << setw((64-3)-(title.length()/2));
    cout << title << endl;
    for (int i = epart-1; i >= 0; --i){
        // 左邊邊攔說明
        cout << setw(temp.length())
             << htg_high/epart*(i+1) << " ";
        // 圖形
        for (unsigned j = 0; j < epart; ++j)
            cout << setw(space) <<htg_str[j][i];
        cout << endl;
    }
    // 數據說明欄
    for (unsigned i = 0; i < epart/2; ++i){
        cout << setw(6) << (i+1)*16;
    }cout << endl;
    // 打印極值
    this->extremum();
    cout << "max=" << (int)max << ", ";
    cout << "min=" << (int)min << endl;
}
} // imr