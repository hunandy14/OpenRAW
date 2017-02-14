# OpenRAW 2.5.0 refrence

**如何引入使用**  
- 標頭僅需引入 `#include "OpenRAW"`  
- 使用時須使用命名空間 `namespace imr`  
    可在標頭引入 `using namespace imr;`  

**GCC 編譯**  
直接編譯`OpenRAW_main.cpp`檔即可  
`g++ -Wall -std=c++0x OpenRAW_main.cpp -o OpenRAW_main`  

**Visual Studio 編譯(擇一即可)**  
1. 需註解 `GCC單檔編譯用` 這一行並移除該檔案  
2. 只加入main.cpp檔 (OpenRAW_fun 資料夾
    還是要複製進去但檔案不要加入專案項目內)  


```
typedef unsigned char imch;
typedef size_t imint;

namespace imr{
    class ImrSize{
    public:
        ImrSize(imint y, imint x);
        imint width;
        imint high;
    };

    class ImrCoor{
    public:
        ImrCoor(int y, int x);
        int y;
        int x;
    };

    class ImrMask{
    public:
        ImrMask(ImrSize masksize);
    private:
        vector<imch> mask;
    };

    class imgraw {
    public:
        imgraw(ImrSize size);
    private:
        vector<imch> img_data;
    };
};
```
</br></br></br>


# 各項類別屬性與建構說明

---

## ImrSize 畫布大小
`ImrSize` 用來描述畫布畫布大小  
大小可在建構時設置  
如，設置一個256x256大小的畫布  
`ImrSize size(256,256);`  

使用時可使用公開變數  
`size.width`與`size.high`  
型態為 `size_t`   

> 某些情況可需要轉態  
`for (int i=0; i<=(int)size.high, ++i)`  

### 方法  
> #### void info();  

印出畫布大小  
`size.info();`  

---
</br></br></br>

## ImrCoor 座標位置  
`ImrCoor` 用來描述座標位置  
座標可在建構時設置  
如，設置一個(0,0)的座標  
`ImrCoor coor(0,0);`  

使用時可使用公開變數  
`size.y`與`size.x`  
型態為 `int`   

### 方法  
#### void info();
印出座標位置  
`coor.info();`  

### 重載 
`ImrCoor` 提供基本的加減乘除運算子  

```
ImrCoor a(1,2), b(3,4), c;
c = a+b;
```
> C則為(4,6)依此類推  

---
</br></br></br>

## ImrMask 遮罩陣列
`ImrMask` 用來儲存遮罩陣列  
使用時需再主程式宣告，並接住(複製)  
方法產生的類別，即可使用。  
`ImrMask mask = img.getMask();`

> 由於僅是接住方法產生的陣列  
> 故不需建構任何資訊(由方法建構)  
> 方法用法請參考該類別說明欄位  

使用時可直接使用[下標]存取指標陣列  
`cout << mask[0] << endl;`  
`mask[0] = 1;`  
型態為`unsigned char*`  

> 雖然為動態陣列，不過會智能解構  
> 不必擔心主程式接住後記憶體釋放問題  

> 因為是動態陣列，主程式用複製的方式  
> 只複製指標並不會拖垮效能  
> 不過讀取的時候那仍然是複製數值  
> 盡可能使用 maskVal() 取代  

### 方法  
#### imch & at2d(size_t y, size_t x);
以二維的方式存取位置(y,x)的遮罩   
`cout << mask.at2d(0,0);`  
`mask.at2d(0,0) = 0;`  

#### void sort(size_t len, size_t start);  
插入排序遮罩大小，由小到大  
`mask.sort();` 排序全部  

其中可以自由指定那些需要排序  
`sort(len, start);`  
比如說一共有4個我要排序中間兩個  
長度是2，從mask[1]開始排序  
`mask.sort(2,1);`  

#### void info();
印出所有遮罩元素  
`mask.info();`  

#### imch avg();  
回傳平均值  
`mask.avg();`  

### 重載 
`ImrMask` 提供基本的`加減`運算子  

```
ImrMask a(1), b(3), c;
c = a+b;
```
> C則為全部則為4依此類推 

---
</br></br></br>

# imgraw OpenRAW主要類別
`imgraw` 用來儲存RAW圖檔  
在建構時需設置圖檔大小  
建構參數是 `imgraw(ImrSize)` 類別  


如，設置一個256x256大小的圖檔  
`ImrSize size(256,256);`  
`imgraw img(size);`  
你也可以一起設置  
`imgraw img(ImrSize(256,256));`   

> 設置錯誤的圖檔大小，基於RAW檔特性  
> 程式是無法辨別並自動修正的  
> 可能會產生不可預知的錯誤  

使用時可直接使用[下標]存取圖檔資訊  
`cout << img[0] << endl;`  
`img[0] = 1;`  
型態為`vector<unsigned char>`  

> 注意因為型態是 `unsigned char`   
> 如果超出255將會從0開始計算  
> 修正方式請在處理時轉為其他型態  

```
img[0] = 127;
double temp;
temp = (double)img[0] + (double)255;

if (temp > 255){
    temp=255;
}

img[0] = (unsigned char)temp;
```

## 方法
```
typedef unsigned char imch;
typedef size_t imint;
```
</br>

> #### void read(string filename);  

將檔案與主程式放到同一個位置  
`img.read("File name");`  
即可將圖檔讀入  
</br>

> #### void write(string filename);  

`img.write("File name");`  
填入輸出的檔名，通常會在圖像處理完畢後輸出  
</br>

> #### imch & at2d(size_t y, size_t x);  

以二維的方式存取圖檔資訊  
`cout << img.at2d(y, x) << endl;`  
`img.at2d(y, x)=img.at2d(y, x)+10;`  
</br>

> #### void resize_canvas(ImrSize size);  

重新定義畫布大小  
`img.resize_canvas(ImrSize(high, width))`  
</br>

> #### imint w();  

獲得寬  
`img.w();`  
</br>

> #### imint h();  

獲得高  
`img.h();`  
</br>

> #### void info();  

印出畫布大小  
`img.info();`  
</br>

> #### void imgraw::binarizae(imch value=128, imch high=255, imch low=0)  

二值化(界線, 填色數值, 背景數值)  
`img.binarizae();`  
</br>

> #### void imgraw::value(imch value);

一次更改所有像素(更改的數值)  
`img.value(0);`  
</br>


</br></br>
## 方法 - Mask  
> #### void setMaskSize(ImrSize masksize);  

設定遮罩大小，使用`getMask()`前須事先指定  
`img.setMaskSize(ImrSize(3,3));`  
</br>

> #### imch maskVal(ImrCoor ori, ImrCoor mas, ImrCoor shi);  

取得遮罩數據  
**遮罩會自動檢查邊界，如果遇到邊界無法取值，自動補上邊界數值**  

**使用說明**  
`ImrCoor ori();`  
對應原圖的點  

`ImrCoor mas();`  
遮罩二維位置  

`ImrCoor shi();`  
偏移位置(可省略預設 -1,-1)  

**假設**  
ori(1,1),  
mas(2,2),  
shi(-1,-1),  

```
原圖(5x5)
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 

遮罩參考點 ori(1,1)
○ ○ ○ ○ ○ 
○ ● ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 

加上位移 shi(-1,-1)
● ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 

放大這個部分 
● ● ● ○ ○ 
● ● ● ○ ○ 
● ● ● ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 

取 mas(2,2)
● ● ● 
● ● ● 
● ● ○ 

img.maskVal(ImrCoor(1,1), ImrCoor(2,2));
可得 [ 若shi留空，預設是shi(-1,-1) ]
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ● ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
```


> #### ImrMask getMask(ImrCoor ori, ImrCoor shi);  
取得遮罩陣列(一維)  
> 需先設置遮罩大小 `img,setMaskSize(ImrSize(3,3));`   
> 點會複製到動態陣列上，除非有要排序，否則會比較花費時間  

```
// 設定遮罩
img.setMaskSize(ImrSize(4,4));
// 取得Mask陣列及排續 getMask(原點位置)
ImrMask mask = img.getMask(ImrCoor(2,2));

cout << endl<< "setMaskSize" << endl;
for (int j = 0, c = 0; j < 4; ++j){
    for (int i = 0; i < 4; ++i, c++){
        cout << (int)mask[c] << " ";
        // cout << mask.at2d(j,i);
    }cout << endl;
}
```

```
原圖(5x5)
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 

對應原圖的點
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ● ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 

偏移位置 shi(-1,-1)
[ 若shi留空，預設是shi(-1,-1) ]
○ ○ ○ ○ ○ 
○ ● ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 
○ ○ ○ ○ ○ 

獲得(4x4)
○ ○ ○ ○ ○ 
○ ● ● ● ● 
○ ● ● ● ●  
○ ● ● ● ●  
○ ● ● ● ●  
```
</br>


</br></br>
## 方法 - Histogram  
> #### void pri_htg(string title);  

印出直方圖  
`img.pri_htg("title name");`  

## 重載  
`imgraw` 提供基本的`加減`運算子  

#### 物件相加  
    imgraw img(...), img2(...);
    imgraw img3 = img+img2;
    
#### 數件+常數  
    imgraw img(...);
    img = img + 10;
    
#### 下標存取  
    imgraw img(...);
    img[0]=255;
    cout << img[0] << endl;














