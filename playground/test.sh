#!/bin/bash

# fail.logを初期化
> fail.log

# 10回繰り返し実行
for i in {1..10}; do
    # 実行前にi回目を出力
    echo "${i}回目" >> fail.log
    # philoプログラムを実行し、出力から"die"が含まれる行を抽出してfail.logに書き込む
    ../philo/philo 201 13 30 30 10 | grep "die" >> fail.log
done

echo "Completed. Check fail.log for results."
