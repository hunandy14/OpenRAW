問題記錄檔
===

## 2017/03/24
### 移動語意的大規則
深度拷貝指的是實際複製`指針所指之處`的內容
淺度拷貝指的是指複製`指針容器內的指針`
> 淺度拷貝後A物件被更動B物件也會跟著被改變

`std::move()` 意指針對`具移動函式的物件`起作用
所謂的`具移動函式的物件`的指的是成員具備指標，且他的 `opertor=()`
提供了深度拷貝與淺度拷貝重載，利用 `std::move()` 將可選擇調用淺度拷貝

如果一個物件不具有移動函式，那麼有沒有使用std::move()結果將沒有區別
> 因為 fun(const &T); 可以接收左右值

右值引用在在引用後會變成左值，因為它具備名字了，所以要用`std::move()`轉回右值


## 2017/03/23
### 移動語意的真正用途
這裡有一個超級大的坑，所有的教學文章都是在教已經會的人，都是以你知道什麼是移動語意，他應該怎麼做的前提下來教你，怎麼觸發移動語意，他們更著重於怎麼觸發，而不是移動語意是什麼該怎麼實現。
> 這我是覺得很奇怪，也因此導致我找超久，最後還是依靠幸運找到答案的。


移動語意真正是用在當你的類別具有指標成員的時候必須自己重載=成 `深度拷貝`
但我們總是會用到 `淺度拷貝的` ，我們換個名詞來形容就是 `移動`
再不發生深度拷貝的行為下，把資源從 a 弄到 b 不就是 `移動` 的意思了

移動函式 `std::move()` 的原理是將他轉成右值引用，以便你區分不一樣的等號

```cpp
Arr & operator=(Arr<T> const & rhs);
Arr & operator=(Arr<T> && rhs);
```

讓第一個等號做深度拷貝，讓第二個等號做淺度拷貝(移動)

#### 此外
經過 `std::move()` 的變數會被語法標記，標記已經不能用了
但這只是標記而已並不代表真的不能，你還是可以存取，只不過會發生未指定行為

##### 未指定行為
編譯器可以根據`語言標準`所提供的行為，選擇要執行哪個行為
> 不會炸且保證每次都一樣，但是有可能換一個編譯器得到不一樣的結果

#####  為定義行為
未定義行為則是完全看你運氣了，他就是存在那個會炸掉的機率，而且還很大。
> 但如果你的程式寫的足夠多，或執行的足夠久，炸的機率接近100%。





### 左右值與const的關係
修正其實具備四種屬性
- 左值 non-const
- 左值 const
- 右值 non-const
- 右值 const

只不過 `右值 const` 本身並沒有什麼用途，移動語意需要語法標記 const 可能會阻礙標記

### 參考
我看得第一篇很好的解釋了什麼是右值，但我還是不能明白什麼是移動語意
[[译]详解C++右值引用](http://jxq.me/2012/06/06/%E8%AF%91%E8%AF%A6%E8%A7%A3c%E5%8F%B3%E5%80%BC%E5%BC%95%E7%94%A8/)

這一篇看完也什麼收穫，感覺跟第一篇一樣
[C++11 标准新特性: 右值引用与转移语义](https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/)

這篇讓我想到很多，補了很多知識，不過還沒想出解
[关于C++右值及std::move()的疑问？](https://www.zhihu.com/question/50652989)

上一篇連出來的，不過還是沒看懂QQ 很神奇
[RVO V.S. std::move](https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/RVO_V_S_std_move?lang=en)

這一篇使用了指標，讓我很有感覺，可是還是沒想到，這是想出來的主力。(這篇還有很多沒看懂)
就是他提到了 unique_ptr 讓我她看懂，我才有可能在下一篇找到答案
[详解C++11中移动语义(std::move)和完美转发(std::forward)](http://shaoyuan1943.github.io/2016/03/26/explain-move-forward/)

微軟的示範文章，但那時候很多看不懂沒繼續看
[移動建構函式和移動指派運算子 (C++)](https://msdn.microsoft.com/zh-tw/library/dd293665.aspx)

這裡是關鍵，我看到了 unique_ptr 搭配上一篇忽然想到深度跟淺度拷貝的問題，終於想通了
[搜索 "std::move() 有什麼用" 搜到的書](https://books.google.com.tw/books?id=SuX-AwAAQBAJ&pg=PA976&lpg=PA976&dq=std::move()+%E6%9C%89%E4%BB%80%E9%BA%BC%E7%94%A8&source=bl&ots=ArggA6OIRv&sig=31FAmHiEfFv_4u8Ty6SfZxK-X6k&hl=zh-TW&sa=X&ved=0ahUKEwintbKizurSAhUGKZQKHbuJDbMQ6AEIOjAE#v=onepage&q=std%3A%3Amove()%20%E6%9C%89%E4%BB%80%E9%BA%BC%E7%94%A8&f=false)



## 2017/03/21
### 研究什麼移動語意
意外發現第三種屬性

如果只重載

```cpp
Arr & operator=(Arr<T> & rhs);
Arr & operator=(Arr<T> && rhs);
```

他會找不到

```cpp
const Arr a;
```


只重載

```cpp
Arr & operator=(Arr<T> const & rhs);
```

那麼無名右值也會被算進來這裡，就無法實現移動語意


覺得左值又值，加上const應該是三種屬性
- 左值 const
- 左值 non-const
- 右值 

應該重載

```cpp
Arr & operator=(Arr<T> const & rhs);
```

負責左值的 const 與 non-const
然後再重載

```cpp
Arr & operator=(Arr<T> && rhs);
```

負責右值，一直以為右值就是 const 貌似是個誤會

?右值不是 const 也不是 non-const 就是無名指標
這句話不知道對不對

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

這種做法只會針對父類別的成員做相加不會更動到子類別成員

```cpp
Arr<int> f;
Arr_int s;

// 01
s=f+f;

// 02
s = s+s;
s += s;

// 03
s = s;
```

1. 等號右邊放 `Arr<int>`
s的成員可能會比f還多，多的部分保留原本有什麼就是什麼
看起來很合理，反正本來就沒有。

2. 等號右邊是放 `Arr_int`
這裡(s+s)會被轉型成 `Arr<int>` (父類的返回參數)
導致捨棄右邊s的 `<Arr_int> 非父類成員`

3. 等號右邊放 `Arr_int`
因為本來就沒更改 operator=(Arr_int const & rhs)
並不影響還是可以把全部的成員複製過去。

</br>

### 記得如何增加const屬性與解除const屬性
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
