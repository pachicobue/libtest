# 一次関数集合と最小関数値クエリ(Convex Hull)

## 問題文
一次関数の集合`F`を考える。各要素は`f_i(x)=a_i*x+b_i`であり、初めは空集合である。  
ここに`Q`個のクエリが飛んでくるので処理して下さい。

- `t_i = 0 a_i b_i`: 一次関数`f(x)=a_i*x+b_i`を`F`に追加する
- `t_i = 1 x_i`: `min_{f in F} f(x_i)` を出力する。但し`F`が空のときは`10000100000`より大きな値(`long long`に収まる範囲で)を出力すれば良いです。

ここで以下の性質が成り立っていると仮定して良いです。

- クエリで飛んでくる`a_i`は単調非増加
- クエリで飛んでくる`x_i`は単調非減少

## 制約

- `1 <= Q <= 100000`
- `-100000 <= a_i,b_i,x_i <= 100000`
- クエリで飛んでくる`a`は単調非増加
- クエリで飛んでくる`x`は単調非減少

## 入力

1行目がクエリの個数で、  
2行目から`Q+1`行目までがクエリ内容です。
```
Q
t_1 a_1 b_1
t_2 x_2
t_3 x_3
.
.
t_Q a_Q b_Q
```

## 出力

クエリ処理結果を出力して下さい。

## サンプル

入力
```
21
1 -87
1 -75
0 92 -28
1 -70
1 -70
1 -59
1 -50
1 -48
0 61 -9
0 48 63
1 -44
1 -35
1 -17
0 27 63
0 16 4
0 15 -27
1 -16
0 -1 -98
0 -1 90
1 -4
0 -12 -13
```

出力
```
2305843009213693951
2305843009213693951
-6468
-6468
-5456
-4628
-4444
-4076
-3248
-1592
-1500
-396
```