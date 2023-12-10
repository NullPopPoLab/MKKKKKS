# AdvancedM3U

## 元のM3U仕様(たぶん)

基本的には、単純に1行1ファイルで書き並べていくだけ。  

\# で始まる行はコメント行。  
(# で始まるファイルの扱いなんぞ知らん)  

 | のあるはファイル名とラベルで区切られる。  

```
#Comment (is not a path)
FileA
DirB/FileBA
DirB/FileBB|Label for FileBB
```

## AdvancedM3U用の特殊記述

* で始まる行は、 *～; で特別な指定ができる。  

* に続けて英大文字を書くとデバイスを選択する。  
(使えるデバイスについては実装側で決める)  

さらに数字を追記してスロットを1以上の整数で指定すると、  
初期設定として指定のスロットに入った状態で始まる。  
(使えるスロット番号についても実装側で決める)  

そこから ! を追記すると、それは読み出し専用フラグとする。  
(実際に読み出し専用にするかも実装側で決める)  

### 特殊記述がない行の扱い

既定動作とする。  
既定のデバイスは実装側で決める。  
常に書き込み可とする。  
スロットについては、デバイス毎の登録順で該当する番号を試す。  
そのスロットが既に使われている場合は適用しない。  

```
# device A, slot 2, writable
*A2;FileA

# device B, slot 1, read only
*B1!;DirB/FileBA

# device B, unslotting, read only
*B!;DirB/FileBB

# default device, try slotting, writable
# e.g.
# default device is A, try to slot 2
# default device is B, try to slot 3
DirC/FileCA
```
