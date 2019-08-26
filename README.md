# libtest

ライブラリのテストに使うための問題集  
CIで使いやすいように、入出力自動生成＋自動テストみたいな流れでテストする  
[rime](https://github.com/icpc-jag/rime) の機能限定版という感じ

## 必要なもの

- [CMake](https://cmake.org/) 
- C++17 ([filesystem](https://cpprefjp.github.io/reference/filesystem.html)が使える環境)

## テストの流れ

愚直解による出力生成を行うかどうかでテストをsmall,largeに区別する(largeは出力生成しない)。  
入力検証は行わない(C++専用だし細かいことは気にしない)。

1. `Problem::generate_input<Problem::small_constraint>` でsmall入力を生成
2. `Problem::generate_output` で想定出力(small)を生成
3. `Problem::generate_input<Problem::large_constraint>` でlarge入力を生成
4. `Solution::solve`に`${case}.in`を入力して実行して出力を生成
5. 対応する`${case}.out`があれば `Problem::judge` で検証

## 問題の記述

`libtest/{problem_dir}`ディレクトリを作り、  
問題を表す構造体を定義する(ファイル名は`problem.hpp`など何でも良い)。  
問題に必要な要素は以下のものである。

- 問題のパス
- 問題名
- 実行時間制限
- 入力生成器(small)
- 入力生成器(large)
- 出力生成器(small)
- 出力検証器
- 制約(small,large)

詳細はサンプル問題である`libtest/a_plus_b/problem.hpp`を参考にすると良い。

## 解法の記述

解法を表す構造体に必要な要素は以下のものである。  
`libtest`は問題集なので、解法はここではなくライブラリ内に書くことが想定される。

- 解法名
- `solve`関数

詳細は`libtest/a_plus_b/solution_sample.cpp`を参考にすると良い。  
入力生成＋テストをいくつ行うかは`Problem`のコンストラクタで指定する。

## 手生成のテストケース追加

`libtest/{problem_dir}/test_cases`直下に`{casename}.in`と`{casename}.out`を追加すれば良い。  
出力検証が必要なければ、`{casename}.out`は不要

## ログ出力の制御

`std::unique_ptr<Logger> g_logger_ptr`がログを担当しているので、これを解法ファイル内などでいじると良い。  
直接いじるより以下のラッパーを使ったほうが安全そう。

- `libtest::mute_log()`: ログ出力をOFF
- `libtest::unmute_log()`: ログ出力をON
- `libtest::redirect_log(std::ostream& os)`: ログ出力先を`os`に変更。デフォルトは`std::cout`

また、テストの実行関数`unit_test::run_test(silent)`を引数に`true`を渡して実行するとテスト途中経過を非表示にできる。

## 注意点

単体テストを`fork`ではなく`thread`で実装しているので、解法が終了しない場合の処理が上手く出来ていない。  
そのため現状は実行時間制限の2倍までに終了しなかった場合は、その旨をログに吐いた後すぐにテストを強制終了する。
