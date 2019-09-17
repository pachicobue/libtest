# 最近共通祖先(LCA)

## 問題文

`N`頂点の無向木`G`が与えられます。`Q`個のクエリが飛んでくるので処理して下さい。  

- `a b`: 頂点`a,b`のLCAを出力して下さい。

## 制約

- `2 <= N <= 100000`
- `1 <= Q <= 100000`
- `0 <= u_i,v_i < N`(辺の端点)
- `0 <= a_i,b_i < N`(クエリ点)

## 入力

```
N Q
u_1 v_1
u_2 v_2
.
.
u_{N-1} v_{N-1}
a_1 b_1
a_2 b_2
.
.
a_Q b_Q
```

## 出力

クエリ処理結果を出力して下さい。
```
l_1
l_2
.
.
l_Q
```

## サンプル

入力
```
69 35
0 54
0 60
0 66
1 27
2 30
2 20
3 7
3 31
4 42
4 45
4 61
5 29
6 13
8 68
8 47
9 35
9 16
10 62
10 68
11 23
11 29
12 52
13 60
14 31
14 48
14 59
14 44
15 50
15 47
16 51
17 27
17 63
18 62
18 43
19 43
21 48
22 50
22 52
23 24
24 67
24 58
24 28
24 65
25 39
25 34
26 50
27 28
27 41
28 62
29 38
30 36
30 46
31 56
31 46
32 35
32 64
33 39
33 40
34 38
36 39
36 37
42 51
42 47
49 50
51 57
51 53
53 60
55 60
56 68
6 56
29 44
16 22
47 52
6 66
10 36
32 47
38 54
0 67
27 44
28 65
41 48
39 68
14 54
59 64
10 23
30 65
38 68
5 40
22 29
6 60
11 15
22 62
21 47
24 47
11 63
7 56
20 63
26 50
35 54
0 8
45 59
38 51
17 42
```

出力
```
68
60
29
51
47
0
10
51
0
0
28
28
28
68
0
51
10
24
68
29
47
60
47
47
47
47
28
31
28
50
0
0
42
51
42
```