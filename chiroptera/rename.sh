#!/usr/bin/env bash
# Idempotent transform: turn an upstream Noctalia tree into Chiroptera Shell.
# Run after every upstream merge (see ChiropteraOS/docs/upstream-sync.md). Safe to re-run.
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"

GH_USER=george-leonard314
# Never renamed or rewritten: our tooling, build dirs, vendored code, the MIT notice and
# credits, and the alias test that names both API globals on purpose.
exclude='^(chiroptera|build[^/]*|third_party|LICENSE|CREDITS\.md|tests/plugin_api_alias_test\.cpp)(/|$)'
# Official plugins are published under the author namespace "noctalia"; their ids stay.
plugins='bitwarden|bongocat|example|kaomoji|mpvpaper|notes|screen_recorder|timer|translator|umbriel-companion|wallhaven|wallpaper_depth|world_clock'

# 1. Upstream-only infrastructure we do not carry.
rm -rf .github nix flake.nix flake.lock default.nix noctalia.scm lefthook.yml

# 2. Rename files and directories whose names contain the old name, deepest first.
#    "|| true" guards: on a re-run nothing matches and grep would exit 1 under pipefail.
find . -depth -not -path './.git/*' -not -path './build*/*' -iname '*noctalia*' -printf '%P\n' \
  | { grep -vE "$exclude" || true; } \
  | while IFS= read -r path; do
      dir=$(dirname "$path")
      base=$(basename "$path" | sed 's/noctalia/chiroptera/g; s/Noctalia/Chiroptera/g; s/NOCTALIA/CHIROPTERA/g')
      mv "$path" "$dir/$base"
    done

# 3. Rewrite text contents. The upstream repo URL first, then the generic rules with
#    lookaheads that protect the org, domains, greeter, plugin ids, and marked lines.
mapfile -d '' files < <(
  find . -type f -not -path './.git/*' -not -path './build*/*' -printf '%P\0' \
    | { grep -zvE "$exclude" || true; } \
    | { xargs -0 -r grep -lIZ -i 'noctalia' -- 2>/dev/null || true; }
)
if [ "${#files[@]}" -gt 0 ]; then
  perl -pi -e '
      next if /<!-- keep -->|noctalia-compat/;
      s{github\.com/noctalia-dev/noctalia(?![A-Za-z0-9-])}{github.com/'"$GH_USER"'/chiroptera-shell}g;
      s{noctalia(?!-dev\b|-greeter|\.dev\b|-compat|/(?:'"$plugins"')\b)}{chiroptera}g;
      s/Noctalia/Chiroptera/g;
      s/NOCTALIA(?!_GREETER)/CHIROPTERA/g;
    ' "${files[@]}"
fi

# 4. README banner crediting upstream, inserted once.
if ! grep -q '<!-- chiroptera-banner -->' README.md; then
  {
    cat <<'BANNER'
<!-- chiroptera-banner -->
# Chiroptera Shell

The desktop shell of ChiropteraOS. A rebrand of Noctalia by the Noctalia team and contributors, MIT licensed: <!-- keep -->
https://github.com/noctalia-dev/noctalia <!-- keep -->

Upstream is tracked as the `upstream` git remote. `chiroptera/rename.sh` is the transform applied
after each upstream merge; `chiroptera/check-rename.sh` verifies it. Plugins written for Noctalia <!-- keep -->
keep working: the Luau API is registered as `chiroptera` with `noctalia` as an alias. <!-- keep -->
The rest of this README is the upstream documentation with names rewritten.

---

BANNER
    cat README.md
  } > README.md.new
  mv README.md.new README.md
fi

echo "rename: done"
