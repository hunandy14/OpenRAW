問題記錄檔
===

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
