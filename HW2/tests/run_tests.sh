#!/bin/bash
# 用法: ./run_tests.sh ./你的執行檔
BIN=${1:-./a.out}
for f in *.in; do
  n=${f%.in}
  if "$BIN" < "$f" > /tmp/_out.txt 2>/dev/null && cmp -s /tmp/_out.txt "$n.out"; then
    echo "ok    $n  $(cat $n.txt)"
  else
    echo "FAIL  $n  $(cat $n.txt)   (diff <($BIN < $f) $n.out)"
  fi
done
