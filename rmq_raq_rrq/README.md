# 区間最小値+区間加算+区間巡回クエリ

## 問題文

長さ`N`の数列`V`が与えられます。`Q`個のクエリか飛んでくるので処理結果を出力して下さい。  

- `t_i=0, n_i`: `V_{n_i}`の値を出力して下さい
- `t_i=1, n_i x_i`: `V_{n_i}`に`x_i`を代入して下さい
- `t_i=2, l_i r_i`: `min(V_{l_i},V_{l_i+1},...,V_{r_i-1})`を出力して下さい
- `t_i=3, l_i r_i x_i`: `V_{l_i},V_{l_i+1},...,V_{r_i-1}`に`x_i`を加算して下さい
- `t_i=4, l_i r_i`: `V_{l_i},V_{l_i+1},...,V_{r_i-1}`を左に1つ巡回シフトして下さい
- `t_i=5, l_i r_i`: `V_{l_i},V_{l_i+1},...,V_{r_i-1}`を右に1つ巡回シフトして下さい

## 制約

- `1 <= N <= 100000`
- `1 <= Q <= 100000`
- `-100000 <= V_i <= 100000`
- `0 <= n_i < N`
- `0 <= l_i < r_i <= N`
- `-100000 <= x_i <= 100000`

## 入力

```
N Q
V_0 V_1 ... V_{N-1}
t_1 l_1 r_1 x_1
t_2 n_2
t_3 n_3 x_3
t_4 l_4 r_4
.
.
t_Q n_Q x_Q
```

## 出力

クエリの処理結果を出力して下さい

## サンプル

入力
```
63 53
-61 -12 50 44 61 -21 -60 -60 37 100 -37 40 -7 -86 -15 -57 -14 45 -81 2 27 35 79 -79 33 81 23 92 65 44 52 90 15 68 30 87 37 -26 69 -82 -47 -41 -73 -78 64 24 -94 32 -44 -2 -56 -99 29 31 -94 -13 -73 51 -46 -81 -50 -96 61
1 12 53
4 11 35
3 34 38 -65
0 51
2 29 43
1 7 47
2 17 60
4 43 50
0 46
0 15
2 39 50
4 15 36
0 42
1 19 -96
4 14 57
2 12 63
3 24 27 19
3 13 60 87
5 16 29
5 7 25
3 28 34 62
4 51 61
0 0
2 5 27
0 19
3 19 34 84
3 23 25 -53
1 14 -46
5 42 51
1 0 62
4 0 25
4 31 44
5 30 44
2 18 34
2 1 55
1 41 -12
2 37 41
1 43 -55
3 44 59 10
1 48 -2
5 0 10
5 15 43
1 58 -4
1 47 68
5 4 43
0 48
1 16 -54
5 2 11
1 16 89
5 8 57
3 10 53 -44
2 14 34
3 36 42 80
```

出力
```
-99
-91
-99
32
-14
-94
-73
-99
-61
-86
114
62
-86
5
-2
-130
```
