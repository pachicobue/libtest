# 文字列マッチング

## 問題文

長さ`M,N`の文字列`S,P`が与えられます。`S`の部分文字列で`P`と一致する場所を昇順に列挙して下さい。  
部分文字列`S_i...S_{i+N-1}`が`P`に一致する時`i`を一致場所と呼ぶことにします。

## 制約

- `S,P`は小文字アルファベットからなる
- `1 <= |S| <= 100000`
- `1 <= |P| <= 10000`

## 入力

```
S
P
```

## 出力

1行目に一致場所の個数`l`を出力して下さい。  
2行目に一致場所を昇順に出力して下さい。
```
l
i_1 i_2 ... i_l
```

## サンプル

入力
```
aebaebaebaebaebaebaeblaebaebfeobhaebdaebjdaebaebaebaebnaebwaebmgwvp
aeb
```

出力
```
17
0 3 6 9 12 15 18 22 25 33 37 42 45 48 51 55 59
```