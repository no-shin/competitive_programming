#!/bin/bash

set -eu

# 新しいマシンでの環境構築をまとめて行う
# 何度実行しても同じ結果になるので、設定を変えたときに再実行してもよい
root=$(cd "$(dirname "$0")/.." && pwd)
cd "$root"

echo "== submodules"
# --recursive は付けない（ac-library 内のテスト用サブモジュールは不要）
git submodule update --init --remote

echo "== python venv"
if [ ! -d .venv ]; then
    python3 -m venv .venv
fi
.venv/bin/pip install -q -r requirements.txt

echo "== config"
python3 scripts/gen_config.py
python3 scripts/gen_snippets.py

# atcoder-tools は ~/.atcodertools.toml を読むのでリンクを張る
# リンクではない実ファイルがあれば消さずに退避する
link="$HOME/.atcodertools.toml"
if [ -e "$link" ] && [ ! -L "$link" ]; then
    mv "$link" "$link.bak"
    echo "moved existing $link to $link.bak"
fi
ln -sfn "$root/.atcodertools.toml" "$link"
echo "linked $link -> $root/.atcodertools.toml"

echo "== shell"
# alias compile / atcoder-tools は生成した .shellrc で定義する
case "$(basename "${SHELL:-bash}")" in
    zsh) rc="$HOME/.zshrc" ;;
    *) rc="$HOME/.bashrc" ;;
esac
line="source \"$root/.shellrc\""
if grep -qF "$line" "$rc" 2>/dev/null; then
    echo "$rc already sources .shellrc (skipped)"
else
    echo "$line" >> "$rc"
    echo "added to $rc: $line (run: source $rc)"
fi

echo "done."
