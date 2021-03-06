# 自動MOD取り構造体のデバッグにどうぞ(固定MOD)

## 問題文

`P=924844033`とします。整数`x`が与えられ、クエリが`Q`個飛んでくるので処理して下さい。

- `t_i = 0, v_i`: `x+v_i`を`P`で割った余りを出力して下さい。
- `t_i = 1, v_i`: `x-v_i`を`P`で割った余りを出力して下さい。
- `t_i = 2, v_i`: `x*v_i`を`P`で割った余りを出力して下さい。
- `t_i = 3, v_i`: `x/v_i`を`P`で割った余りを出力して下さい(`v_i!=0 (mod P)`は仮定して良い)。
- `t_i = 4, v_i`: `v_i-x`を`P`で割った余りを出力して下さい。
- `t_i = 5, v_i`: `v_i/x`を`P`で割った余りを出力して下さい。但し`x==0 (mod P)`の場合は`-1`を出力して下さい。
- `t_i = 6, n_i`: `x^n_i`を`P`で割った余りを出力して下さい(`^`は累乗。`n_i`が非負であることは仮定して良い)。
- `t_i = 7, v_i`: `x==v_i (mod P)`なら`1`を、そうでなければ`0`を出力して下さい。
- `t_i = 8, v_i`: `x`に`v_i`を代入して下さい(出力は無し)。
- `t_i = 9, v_i`: `x`に`x+v_i`を代入して下さい(出力は無し)。
- `t_i = 10, v_i`: `x`に`x-v_i`を代入して下さい(出力は無し)。
- `t_i = 11, v_i`: `x`に`x*v_i`を代入して下さい(出力は無し)。
- `t_i = 12, v_i`: `x`に`x/v_i`を代入して下さい(出力は無し。`v_i!=0 (mod P)`は仮定して良い)。
- `t_i = 13, n_i`: `x`に`x^n_i`を代入して下さい(出力は無し。`n_i`が非負であることは仮定して良い)。

## 制約

- `-1000000000 <= x <= 1000000000`
- `1 <= Q <= 100000`
- `-1000000000 <= v_i <= 1000000000`
- `0 <= n_i <= 1000000000`

## 入力

```
x Q
t_1 v_1
t_2 v_2
t_3 n_3
.
.
t_Q v_Q
```

## 出力

クエリ処理結果を出力して下さい。

## サンプル

入力
```
974971057 47
2 -458208860
13 42
3 104903134
2 315692256
10 -26457767
1 305797235
9 602380952
4 -3092454
7 951074577
9 248471838
7 595689656
9 -643990619
11 48230425
11 604015768
2 -607940829
1 783382410
6 53
7 -619901145
5 320767902
6 24
7 -314500532
5 -23462634
4 672217616
13 35
4 172249590
2 -746017953
2 319855470
12 -342652820
12 -623661089
10 44376954
11 738943893
11 -680685405
8 409207623
4 431736716
13 40
9 620601674
7 118255000
11 -728456449
2 -9747204
7 196328788
1 865029007
4 -664085094
9 -181129626
7 -98730970
9 187486772
6 59
4 588762667
```

出力
```
237835541
909048805
69743550
792463473
145953952
0
0
393328983
658762108
727061983
0
616941344
535878484
0
338465438
154917131
261663471
315629154
30072159
22529093
0
475997991
0
292516977
28056988
0
281100316
349703570
```
