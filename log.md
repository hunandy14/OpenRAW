問題記錄檔
===
## 20170319
### 繼承後如何轉名
父類別的資料成員原本叫做arr，我希望繼承後可以改用mask名稱操作

一般可以用參考取別名，轉名醫開始使用 auto&

```cpp
auto& maks = arr;
```

貌似不行查了一下，還有另一個 `dedecltype(var)` 這個可行

```cpp
decltype(arr) & mask = arr;
```

查了一下找到這個
http://tommyjswu-blog.logdown.com/posts/736924-c-11-mouth-cannon-auto

理解是
- auto 靜態
- decltype 動態

像是 template，你沒辦法在一開始就知道他是什麼用 auto 會查不出來

 
## 20170317
### 繼承downcast問題
arr -> arr_int
operator函式定義在arr

```cpp
arr_int a;
a=a+a;
```

a+a 返還的型態是 arr 可是 arr_int 因為沒有寫所以編譯器自己補了一個

```cpp
arr_int & arr_int::operator=(arr_int const & rhs);
```

會導致 arr_int = arr 這種狀況找不到函式使用



> 解決了，新增缺少的operator=()。並讓他呼叫原本的父類別的函式即可

```cpp
   Arr_int & operator=(Arr<int> const & rhs){
       this->Arr<int>::operator=(rhs);
       return (*this);
   }
```

或是


```cpp
    Arr_uch & operator=(Arr<uch> const & rhs){
        ((*static_cast<Arr<uch>*>(this)) = rhs);
        return (*dynamic_cast<Arr_uch*>(this));
    }
```

</br>

### 記得如和增加const屬性與解除const屬性
Caesar08 op[][] 裡面用了兩個類別來重載第二個括號
兩個類別寫的內容完全一樣，想說能不能直接A繼承B或B繼承A

可問題是一個有const 一個沒 const 該怎麼解決這個問題呢

> 最後發現兩分代碼裡面根本就長的不一樣，沒有一樣的地方可以提出
> 這個問題看起貌似不存在，僅是一開始沒看好誤會了
> 
> 在做繼承時應該看清楚裡些是完全一樣的，拉出來省得重打一次


</br>

### friend 函式
- 如果該函式有多型宣告，則在friend前也要補上一樣的多型

```cpp
template <typename T1> friend
    Arr<T1> Arr::operator+(Arr<T1> const &lhs, Arr<T1> const &rhs);
```


</br></br></br>

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



</br></br></br>

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



</br></br></br>

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
