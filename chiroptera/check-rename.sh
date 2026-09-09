#!/usr/bin/env bash
# Fails if any reference to the upstream name survives outside the allowlist.
# Allowed: the upstream GitHub org, upstream domains, the separate greeter package,
# official plugin ids (author namespace "noctalia"), lines marked <!-- keep --> or
# noctalia-compat, the MIT license and credits, vendored third_party code, the alias
# test that names both globals on purpose, and this tooling directory.
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"

plugins='bitwarden|bongocat|example|kaomoji|mpvpaper|notes|screen_recorder|timer|translator|umbriel-companion|wallhaven|wallpaper_depth|world_clock'
allow="noctalia-dev|noctalia-greeter|noctalia\.dev|noctalia-compat|NOCTALIA_GREETER|noctalia/($plugins)\b|<!-- keep -->|^\./(chiroptera|third_party|LICENSE|CREDITS\.md|tests/plugin_api_alias_test\.cpp)(/|:)"
status=0

leftovers=$(find . -type f -not -path './.git/*' -not -path './build*/*' -print0 \
  | xargs -0 grep -HnI -i 'noctalia' -- 2>/dev/null | grep -vE "$allow" || true)
if [ -n "$leftovers" ]; then
  echo "check-rename: leftover references:" >&2
  echo "$leftovers" >&2
  status=1
fi

paths=$(find . -not -path './.git/*' -not -path './build*/*' -not -path './third_party/*' -iname '*noctalia*' || true)
if [ -n "$paths" ]; then
  echo "check-rename: leftover paths:" >&2
  echo "$paths" >&2
  status=1
fi

for f in .github nix flake.nix flake.lock default.nix noctalia.scm lefthook.yml; do
  if [ -e "$f" ]; then
    echo "check-rename: $f must not exist" >&2
    status=1
  fi
done

if ! grep -q 'Copyright' LICENSE; then
  echo "check-rename: LICENSE lost its copyright notice" >&2
  status=1
fi

if [ "$status" -eq 0 ]; then
  echo "check-rename: ok"
fi
exit "$status"
