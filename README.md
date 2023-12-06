# RV32I
RV32I processor implementation with Verilog

# 概要
+ 01 : ５段パイプライン＋分岐予測（常に分岐）
+ 02 : ５段パイプライン＋分岐予測（２ビット分岐予測）
+ 03 : ２並列インオーダ＋分岐予測（常に分岐）

# 実行方法
+ 各ディレクトリ(01, 02, 03
```
$ bash iverilog.sh
$ ./a.out > result
```
として、トレースデータを得る。このデータは、ストールなどによるNOP命令も出力されているが、
```
$ python3 CutNop.py 
```
とすれば、NOP命令を削除した result2 ファイルが得られる。

+ 性能評価
```
$ verilator --cc top.v -exe test_bench.cpp
$ make -C obj_dir/ -f Vtop.mk
$ obj_dir/Vtop
```
と実行していくと、１０分ほどで出力が得られる。

