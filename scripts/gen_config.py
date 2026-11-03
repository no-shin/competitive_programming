#!/usr/bin/env python3
# config/ の雛形からマシンごとの設定ファイルを生成する（生成物は gitignore 済み）
#
# 雛形の中では次の変数が使える
#   {{ROOT}}           このリポジトリの絶対パス
#   {{COMPILE_FLAGS}}  config/compile_flags.txt を空白区切りでつないだもの
#   {{COMPILE_ARGS}}   同じものを JSON 文字列のカンマ区切りにしたもの（JSON の配列の中で使う）
#   {{INCLUDE_PATHS}}  -I の値を JSON 文字列のカンマ区切りにしたもの
#   {{DEFINES}}        -D の値を JSON 文字列のカンマ区切りにしたもの
#   {{CPP_STANDARD}}   -std= の値（例: gnu++20）
import json
import pathlib
import shlex
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
CONFIG = ROOT / "config"

# 雛形 → 生成先（どちらも ROOT からの相対パス）
TARGETS = {
    "config/atcodertools.toml.in": ".atcodertools.toml",
    "config/shellrc.in": ".shellrc",
    "config/vscode/tasks.json.in": ".vscode/tasks.json",
    "config/vscode/launch.json.in": ".vscode/launch.json",
    "config/vscode/settings.json.in": ".vscode/settings.json",
    "config/vscode/c_cpp_properties.json.in": ".vscode/c_cpp_properties.json",
}


def read_flags():
    text = (CONFIG / "compile_flags.txt").read_text()
    text = text.replace("{{ROOT}}", str(ROOT))
    return shlex.split(text, comments=True)


def json_items(values):
    return ", ".join(json.dumps(v) for v in values)


def build_variables(flags):
    includes = [f[2:] for f in flags if f.startswith("-I")]
    defines = [f[2:] for f in flags if f.startswith("-D")]
    standards = [f[5:] for f in flags if f.startswith("-std=")]
    return {
        "ROOT": str(ROOT),
        "COMPILE_FLAGS": " ".join(flags),
        "COMPILE_ARGS": json_items(flags),
        "INCLUDE_PATHS": json_items(includes),
        "DEFINES": json_items(defines),
        "CPP_STANDARD": standards[-1] if standards else "",
    }


def render(template, variables):
    for name, value in variables.items():
        template = template.replace("{{" + name + "}}", value)
    return template


def main():
    variables = build_variables(read_flags())
    for src, dst in TARGETS.items():
        text = render((ROOT / src).read_text(), variables)
        if "{{" in text:
            sys.exit(f"error: {src} に未定義の変数が残っています")
        if dst.endswith(".json"):
            try:
                json.loads(text)
            except json.JSONDecodeError as e:
                sys.exit(f"error: {src} から生成した JSON が不正です: {e}")

        out = ROOT / dst
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(text)
        print(f"generated {dst}")


if __name__ == "__main__":
    main()
