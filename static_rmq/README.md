# 区間最小値クエリ(更新クエリなし)

## 問題文

長さ`N`の数列`V`が与えられます。`Q`個のクエリか飛んでくるので処理結果を出力して下さい。  

- `l_i r_i`: `V_{l_i}+V_{l_i+1}+...+V_{r_i-1}`を出力して下さい

## 制約

- `1 <= N <= 100000`
- `1 <= Q <= 100000`
- `-1000000000 <= V_i <= 1000000000`
- `0 <= l_i < r_i <= N`

## 入力

```
N Q
V_0 V_1 ... V_{N-1}
l_1 r_1
l_2 r_2
.
.
l_Q r_Q
```

## 出力

```
ans_1
ans_2
.
.
ans_Q
```

## サンプル

入力
```
12 23
20 66 -67 -26 52 76 39 54 -30 39 39 67
2 5
5 11
2 6
2 7
0 7
4 6
0 7
7 10
3 4
4 11
7 9
11 12
3 6
1 11
5 12
2 8
6 10
1 4
1 5
2 7
3 6
1 9
0 2
```

出力
```
-67
-30
-67
-67
-67
52
-67
-30
-26
-30
-30
67
-26
-67
-30
-67
-30
-67
-67
-67
-26
-67
20
```