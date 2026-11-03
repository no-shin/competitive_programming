# competitive_programming

競プロ環境（atcoder-tools・自作ライブラリ・各種 dotfiles）を新しいマシンで再現するためのリポジトリ。

## セットアップ

```sh
scripts/setup.sh
```

リポジトリをどこに置いていても、このコマンド1つで以下をまとめて行う。何度実行しても結果は同じ。

1. サブモジュール（`reactive` / `noshinn_library` / `ac-library`）の取得・更新
2. Python 仮想環境 `.venv` の作成と `requirements.txt` のインストール（`.venv` は gitignore 済み）
3. `config/` の雛形から設定ファイルを生成（`scripts/gen_config.py`）
4. `noshinn_library` から VS Code のスニペットを生成（`scripts/gen_snippets.py`）
5. `~/.atcodertools.toml` へのリンク（リンクでない実ファイルがあれば `.bak` に退避）
6. `.bashrc`（zsh なら `.zshrc`）に `source <リポジトリ>/.shellrc` を追加（既にあれば何もしない）

終わったら `source ~/.bashrc` で `compile` / `atcoder-tools` の alias を有効にする。

## 構成

```text
config/                     # 雛形（git 管理）
├── compile_flags.txt       # コンパイルオプション。atcoder-tools / VS Code / alias compile で共通
├── atcodertools.toml.in
├── shellrc.in
└── vscode/*.in
scripts/
├── setup.sh
├── gen_config.py           # config/ → 下の生成物
└── gen_snippets.py         # noshinn_library → .vscode/cpp.code-snippets

# 以下は生成物（マシンごとにパスが違うので gitignore）
.atcodertools.toml
.shellrc
.vscode/                    # tasks / launch / settings / c_cpp_properties / スニペット
```

雛形の中では `{{ROOT}}`（リポジトリの場所）や `{{COMPILE_FLAGS}}` などの変数が使える。
使える変数は `scripts/gen_config.py` の先頭に書いてある。

## VS Code

`atcoder-tools gen` でコンテストを作ると、そのディレクトリに `.vscode` へのリンクが張られる。
`atcoder/abcXXX/` を開けば、Build / Test / Submit タスク・デバッグ・スニペットがそのまま使える。

## スニペット

`noshinn_library` のソースで、スニペットにしたい範囲を次のように囲む。サブディレクトリは何階層でもよい。

```cpp
// snippet-begin: unionfind Union-Find
struct unionfind { ... };
// snippet-end
```

`snippet-begin:` の後の最初の語が補完で打つ文字列、残りが説明（省略可）。
ライブラリを変えたら `scripts/gen_snippets.py` を実行し直す。

## 注意

- 設定を変えるときは `config/` の雛形を編集し、各マシンで `scripts/gen_config.py`（または `scripts/setup.sh`）を実行し直すこと。
- 生成物を直接編集しても、次の生成で上書きされ、他のマシンにも共有されない。
