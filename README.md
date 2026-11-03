# competitive_programming

競プロ環境（atcoder-tools・自作ライブラリ・各種 dotfiles）を新しいマシンで再現するためのリポジトリ。

## セットアップ

```sh
scripts/setup.sh
```

リポジトリをどこに置いていても、このコマンド1つで以下をまとめて行う。何度実行しても結果は同じ。

1. サブモジュール（`reactive` / `noshinn_library` / `ac-library`）の取得・更新
2. Python 仮想環境 `.venv` の作成と `requirements.txt` のインストール（`.venv` は gitignore 済み）
3. `.atcodertools.toml.in` から `.atcodertools.toml` を生成（`scripts/gen_config.sh`）
4. `~/.atcodertools.toml` へのリンク（リンクでない実ファイルがあれば `.bak` に退避）
5. `.bashrc`（zsh なら `.zshrc`）に `atcoder-tools` の alias を追加（既にあれば何もしない）

終わったら `source ~/.bashrc` で alias を有効にする。

## 注意

- 設定を変えるときは `.atcodertools.toml.in` を編集し、各マシンで `scripts/gen_config.sh`（または `scripts/setup.sh`）を実行し直すこと。
- 生成された `.atcodertools.toml` はマシンごとにパスが異なるため gitignore している。直接編集しても共有されない。
