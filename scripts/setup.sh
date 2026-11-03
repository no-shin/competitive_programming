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

echo "== atcoder-tools config"
scripts/gen_config.sh

# atcoder-tools は ~/.atcodertools.toml を読むのでリンクを張る
# リンクではない実ファイルがあれば消さずに退避する
link="$HOME/.atcodertools.toml"
if [ -e "$link" ] && [ ! -L "$link" ]; then
    mv "$link" "$link.bak"
    echo "moved existing $link to $link.bak"
fi
ln -sfn "$root/.atcodertools.toml" "$link"
echo "linked $link -> $root/.atcodertools.toml"

echo "== alias"
case "$(basename "${SHELL:-bash}")" in
    zsh) rc="$HOME/.zshrc" ;;
    *) rc="$HOME/.bashrc" ;;
esac
if grep -q "alias atcoder-tools=" "$rc" 2>/dev/null; then
    echo "alias already in $rc (skipped)"
else
    echo "alias atcoder-tools='$root/.venv/bin/atcoder-tools'" >> "$rc"
    echo "added alias to $rc (run: source $rc)"
fi

echo "done."
