# MKKKKKS library for C

## 使い方 

ビルドで mkkkkks.a とかできるけど、これはテスト向け。  
それぞれのソースファイルはわりと独立で使えるので、  
必要に応じて各自のソリューションにぶっ込んどくのがいーんでないかい。  

各機能の使い方については、 test/ にあるソース読んどくよろし。  

### Doxygen対応 

…でコメント書いてあるので、あとは各自のソリューションにて。  
まだなら是非とも導入しましょう。  
http://www.doxygen.jp/

## 機能紹介 

### safe_alloc

ゼロクリア付きのmallocと  
インスタンスポインタにNULLを書き込むfree  
それだけ  

### quick_text

いちいち0終端させなくても扱える部分文字列機能  

### quick_loader

ファイルサイズ調べてmallocとファイル全体ロードのワンセット  
それだけ  

### advanced_m3u

拙作libretroコアで使っている拡張M3Uを汎用で使えるように再実装したもの  
詳細は ../doc/AdvancedM3u.md にて
