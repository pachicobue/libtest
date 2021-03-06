# 区間をセグ木っぽく分割する問題

## 問題文

2冪の整数`N=2^n`が与えられます。`[0,2^n)`に含まれる半開区間`[l,r)`が以下を満たすとき、`良い区間`と呼ぶことにする。  
要するにセグ木に載っている区間のことです。

- `l < r`
- 区間長が2冪(`2^m`とする)
- `l,r`が`2^m`の倍数

ここで`Q`個のクエリが飛んでくるので処理結果を出力して下さい。

- `t_i=0, l_i r_i`: `[l,r)`を最少の`良い区間`で分割する方法を出力して下さい
- `t_i=1, x_i`: `x_i`を含む`良い区間`を列挙して出力して下さい

`良い区間`は以下の順序で並べて出力して下さい。

1. 区間長が長いものを先に出力
2. 区間長が等しいものは、左端`l`が小さいものを先に出力

## 制約

- `1 <= N <= 2^{16}`
- `1 <= Q <= 100000`
- `0 <= l_i < r_i <= N`
- `0 <= x_i < N`

## 入力

```
N Q
t_1 l_1 r 1
t_2 x_1
.
.
t_Q x_Q
```

## 出力

各クエリ結果は以下のように出力して下さい。  
1行目に良い区間の個数`m`を出力し、  
2行目から`m+1`行目に良い区間を`l r`の形式で出力して下さい。
```
m
l_1 r_1
l_2 r_2
.
.
l_m r_m
```

## サンプル

入力
```
128 10
1 16
1 57
1 123
1 102
1 107
1 57
0 65 122
1 49
0 97 111
0 5 114
```

出力
```
8
0 128
0 64
0 32
16 32
16 24
16 20
16 18
16 17
8
0 128
0 64
32 64
48 64
56 64
56 60
56 58
57 58
8
0 128
64 128
96 128
112 128
120 128
120 124
122 124
123 124
8
0 128
64 128
96 128
96 112
96 104
100 104
102 104
102 103
8
0 128
64 128
96 128
96 112
104 112
104 108
106 108
107 108
8
0 128
0 64
32 64
48 64
56 64
56 60
56 58
57 58
8
80 96
96 112
72 80
112 120
68 72
66 68
120 122
65 66
8
0 128
0 64
32 64
48 64
48 56
48 52
48 50
49 50
6
100 104
104 108
98 100
108 110
97 98
110 111
8
32 64
64 96
16 32
96 112
8 16
6 8
112 114
5 6
```
