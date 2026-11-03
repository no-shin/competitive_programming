#!/usr/bin/env python3
# noshinn_library 以下のソースから VS Code のスニペット (.vscode/cpp.code-snippets) を生成する
#
# ライブラリ側では、スニペットにしたい範囲を次のように囲む
#
#   // snippet-begin: unionfind Union-Find（素集合データ構造）
#   struct unionfind { ... };
#   // snippet-end
#
# snippet-begin: の後の最初の語が prefix（補完で打つ文字列）、残りが説明（省略可）
# 1ファイルに複数書いてよい。サブディレクトリも何階層でも再帰的に探す
import json
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
LIBRARY = ROOT / "noshinn_library"
OUTPUT = ROOT / ".vscode" / "cpp.code-snippets"

EXTENSIONS = {".cpp", ".hpp", ".h", ".cc"}
BEGIN = re.compile(r"^\s*//\s*snippet-begin:\s*(\S+)\s*(.*?)\s*$")
END = re.compile(r"^\s*//\s*snippet-end\b")


def source_files():
    for path in sorted(LIBRARY.rglob("*")):
        rel = path.relative_to(LIBRARY)
        # .git や .github などの隠しディレクトリは見ない
        if any(part.startswith(".") for part in rel.parts):
            continue
        if path.is_file() and path.suffix in EXTENSIONS:
            yield path


def parse(path, errors):
    rel = path.relative_to(LIBRARY).as_posix()
    snippets = []
    current = None
    for lineno, line in enumerate(path.read_text().splitlines(), 1):
        where = f"{rel}:{lineno}"
        if m := BEGIN.match(line):
            if current:
                errors.append(f"{where}: {current['where']} の snippet-begin が閉じられていない")
            current = {"prefix": m[1], "description": m[2] or rel,
                       "where": where, "body": []}
        elif END.match(line):
            if not current:
                errors.append(f"{where}: snippet-begin のない snippet-end")
                continue
            snippets.append(current)
            current = None
        elif current:
            # スニペットでは $ が特別な意味を持つのでエスケープする
            current["body"].append(line.replace("$", "\\$"))
    if current:
        errors.append(f"{current['where']}: snippet-end がない")
    return snippets


def main():
    if not LIBRARY.is_dir():
        sys.exit(f"error: {LIBRARY} がありません（git submodule update --init）")

    errors = []
    snippets = [s for path in source_files() for s in parse(path, errors)]

    seen = {}
    for s in snippets:
        if s["prefix"] in seen:
            errors.append(f"{s['where']}: prefix \"{s['prefix']}\" が "
                          f"{seen[s['prefix']]} と重複している")
        seen.setdefault(s["prefix"], s["where"])

    if errors:
        sys.exit("error:\n  " + "\n  ".join(errors))

    result = {}
    for s in snippets:
        body = s["body"]
        while body and not body[-1].strip():
            body.pop()
        result[f"{s['prefix']} ({s['where'].rsplit(':', 1)[0]})"] = {
            "scope": "cpp",
            "prefix": s["prefix"],
            "body": body,
            "description": s["description"],
        }

    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n")
    print(f"generated {OUTPUT.relative_to(ROOT)} ({len(result)} snippets)")


if __name__ == "__main__":
    main()
