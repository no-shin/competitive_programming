#!/bin/bash

set -eu

# .atcodertools.toml.in の {{ROOT}} をこのリポジトリの場所に置き換えて
# .atcodertools.toml を生成する（生成物は gitignore 済み）
root=$(cd "$(dirname "$0")/.." && pwd)

sed "s|{{ROOT}}|$root|g" "$root/.atcodertools.toml.in" > "$root/.atcodertools.toml"

echo "generated $root/.atcodertools.toml"
