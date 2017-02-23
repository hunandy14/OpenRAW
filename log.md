問題記錄檔
===

## 20170223
### 為什麼要加friend
```cpp
friend ImrCoor operator+(ImrCoor const &lhs, ImrCoor const &rhs);
```

不寫的話如果這個定義不是寫在開頭，而是寫在底下，或拆檔會找不到該定義。


### 重載函式的問題
發問：
[[問題] const 位於 函式前 與 參數後 的意思](https://www.ptt.cc/bbs/C_and_CPP/M.1487782131.A.AAF.html)
[[問題] 重載下標符號 const 用途](https://www.ptt.cc/bbs/C_and_CPP/M.1487584989.A.308.html)

整理筆記：
[C++ 重載 operator + , += 重複打兩次及效能問題](http://charlottehong.blogspot.com/2017/02/c-operator.html)
[C++ 重載下標符號 const 與非 const 寫兩次整合成一次的辦法](http://charlottehong.blogspot.com/2017/02/c-const-const.html)

重點：
1. const位於函式名稱後方表示限制該函式的 *this
2. 重載+符號要寫在全域
3. 重載+符號要內要直接呼叫+=函式
4. 重載[]主代碼寫在 const 函式，非const函式強制呼叫 const 版本的並解除 const




## 20170220
### const 函數可以被整合嗎
```cpp
imch & imgraw::random(){
    size_t idx;
    int up=this->filesize, low=0;
    idx = ((rand() / (RAND_MAX+1.0)) * (up - low) + low);
    cout << "idx=" << idx << endl;
    cout << "*imgraw::random()" << endl;
    return (*this)[idx];
}
const imch & imgraw::random() const{
    cout << "**imgraw::random() const" << endl;
    return random();
}
void imgraw::test(const imch & a){
    cout << (int)a << endl;
}
```
然後就是，為什麼 const 版本的函式怎麼樣都不會執行QQ

> 2017/02/21解答：  
> 因為宣告的類別是非const屬性的只會呼叫非const屬性  
> `imgraw a();`  
> `const imgraw a();`  
> 
> c++新特性有一個可以強制解除const屬性  
> `const_cast<>`
> 
> 利用這點解決這個問題把主代碼寫在const屬性裡  
> 
> #### 解法
> 讓 非const版本 的強制去呼叫 const版本的  
> `static_cast<const class&>(*this)`
> 
> 然後再強制解除 const 屬性  
> `const_cast<typename&>`
> 
> 就可以整合成一份主代碼了 
> 
> [[問題] 重載下標符號 const 用途](https://www.ptt.cc/bbs/C_and_CPP/M.1487584989.A.308.html) 




## 20161013
### 方法裡面不應該存在模擬兩可
有一個方法式存在預設值  
`class::fun(int i=1);`  

只有在main也就是非函式定義裡面  
才可以使用這個預設值  
方法定義必須清晰不應該不清楚  

如果真的要用預設值乖乖用  
`class::fun(int i=1);`  
`class::fun();`  

定義兩次吧  

### ImrMask 裡面有一個函式我寫成
imch long 無號整數不應該存在 long  
居然沒有被 C++ 檢查出來  

### 命名空間
原本寫在標頭檔inc "cpp"進來沒問題  
拆分檔案之後忘記在cpp內使用命名空間  
在cpp內的命名空間不應該使用 using 卡了一段時間  


### 參考是什麼
http://stackoverflow.com/questions/2379859/in-c-what-does-mean-after-a-functions-return-type

### 方法回傳為參考時，必須同時定義 const 與非const 版本
有些時候必須使用const，比如說運算子重載的時候  
這時候沒有定義你就沒有辦法直接使用了  

[下标操作符为什么要定义const和非const两个版本？](http://zhidao.baidu.com/question/517798128.html)  

[const 放置位置的意義](http://blog.xuite.net/tsai.oktomy/program/65131235-const+%E6%94%BE%E7%BD%AE%E4%BD%8D%E7%BD%AE%E7%9A%84%E6%84%8F%E7%BE%A9)  

### 重載運算子
用來暫存的temp忘記定義影像大小，找bug找好久QQ  
要把影像大小預設值為0拔掉了  
