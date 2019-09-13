# 自身を含む文字列の数え上げクエリ

## 問題文

文字列の多重集合`S`は初め空集合です。ここに`Q`個のクエリが飛んでくるので処理結果を出力して下さい。

- `t_i=0, s_i`:`S`に文字列`s_i`を追加する
- `t_i=1, s_i`:`S`の元`t`で文字列`s_i`が`t`のprefixであるようなものの個数を出力して下さい。

## 制約

- `1 <= Q <= 100000`
- `|s_i|`の合計は`400000`以下
- `s_i`は小文字アルファベットからなる

## 入力

```
Q
t_1 s_1
t_2 s_2
.
.
t_Q s_Q
```

## 出力

クエリ処理結果を出力して下さい。

## サンプル

入力
```
83
1 b
0 b
1 abb
0 bababbabbbabbbbbabb
1 abaaaaaabbbbaaabba
0 ba
0 aaaabbaaabababaabababb
1 abaabbaaaabbaabbbbabbababbb
0 aabbabaaabbabbaaabbbabaabbb
0 bbbababab
0 bbbabbbaabbaab
1 ababbbbbbabbaaab
0 a
0 b
1 b
1 aa
0 bbbabbbbaaaabbbbbaaaaab
1 baabbaaabbbabaabab
0 abbabbbbbbbabbabaabbaaa
1 bb
0 aaa
1 bababaaaabaabbaaa
0 a
1 bab
0 a
1 baaaabbbbaaaabbabbaaabaaa
1 a
0 a
1 bb
1 bbb
0 b
1 abbaabaaaaababaababbbbbba
1 a
1 a
0 aaa
1 aaaaaaabbbbabaaaabbbb
0 baabbbbbbababbaaabaab
0 b
1 bbaabbbbbaaababbbbb
1 bbaaabababaabaaaa
1 baabbaabaaabbbbabaa
1 bbbaabaaaba
0 babaaabaabbababa
0 aaababbabbabbbbbababbba
1 aaaaaaaabbbbbaaaaaaa
0 abbaabbbbaabbbbbaa
0 a
1 b
1 bbb
0 ba
0 abbbabbababbaabbabbabaa
0 bbabbbbabbbab
1 bbbbaaaabaaaaabbbbbbb
1 aba
1 aba
1 ab
1 baababbabbaababaabbbabbbaba
0 ab
1 a
0 abbbaaaabbbbbaaaaaaaabbbab
0 b
0 abbaabbabbaabaabbaabbbba
1 abbabaabaabbaabbb
1 abb
0 aab
1 ab
0 bbbabaaaababbaababbbba
0 aaaabbabbabbababa
0 abbbbaaabaabbabaaaa
1 bbbbbbbababaaababbbabbabab
0 bb
0 abbbbbbbabaaaaa
0 a
1 ab
0 bbbaababbbbbababab
0 bbbaaaabbabaaabababbaabbbba
1 aabbabaababababbaaa
0 aabaababbbbaabab
1 aba
0 bababbabbbbbbabaaaabaabbaa
1 bb
0 b
1 aaaaaaabaaababbabaabbaaab
```

出力
```
0
0
0
0
0
6
2
0
3
0
1
0
7
3
3
0
8
8
0
0
0
0
0
0
11
3
0
0
0
3
0
14
0
5
6
0
8
0
0
8
0
```
