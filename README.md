# competitive_programming

競プロ環境（atcoder-tools・自作ライブラリ・各種 dotfiles）を新しいマシンで再現するためのリポジトリ。

## セットアップ

以下はリポジトリを `~/competitive_programming` に置いた場合。別の場所に置いたならパスを読み替えること。

### 1. 取得・サブモジュール更新

```sh
git pull
git submodule update --init --recursive --remote
```

`reactive` / `noshinn_library` / `ac-library` がサブモジュールとして入る。

### 2. Python 仮想環境の作成

`atcoder-tools` とその依存を `.venv` に入れる（`.venv` は gitignore 済み）。

```sh
python3 -m venv .venv
.venv/bin/pip install -r requirements.txt
```

### 3. atcoder-tools の設定ファイルをリンク

```sh
ln -sf "$HOME/competitive_programming/.atcodertools.toml" ~/.atcodertools.toml
```

### 4. alias の追加

venv を activate せずに使えるよう、`.bashrc` / `.zshrc` に追加する。

```sh
alias atcoder-tools="$HOME/competitive_programming/.venv/bin/atcoder-tools"
```

## 注意

`.atcodertools.toml` 内の `template_file` / `workspace_dir` と、コンパイルコマンドの
`-I.../ac-library` は絶対パス指定なので、リポジトリを別の場所に置いた場合は書き換えること。
