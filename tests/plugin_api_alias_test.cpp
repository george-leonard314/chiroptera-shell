#include "core/process/process.h"
#include "core/toml.h"
#include "scripting/luau_host.h"
#include "scripting/script_api_context.h"
#include "tests/test_check.h"

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <optional>
#include <print>
#include <string>
#include <utility>

// Plugins written for Noctalia call `noctalia.*`. Chiroptera registers the API as
// `chiroptera` and must expose `noctalia` as an alias to the very same table.
int main() {
  scripting::ScriptApiContext api;
  api.setConfigSnapshot(std::make_shared<const toml::table>(toml::parse("[shell]\noffline_mode = true")));
  LuauHost host(api, "test/plugin:service");

  TEST_CHECK(host.exec("primary", "assert(type(chiroptera) == 'table', 'chiroptera API table missing')"));
  TEST_CHECK(host.exec("alias", "assert(type(noctalia) == 'table', 'noctalia alias missing')"));
  TEST_CHECK(host.exec("same", "assert(rawequal(noctalia, chiroptera), 'noctalia must be the same table as chiroptera')"));
  TEST_CHECK(host.exec("members", "assert(noctalia.state ~= nil and noctalia.json ~= nil and noctalia.sound ~= nil and noctalia.string ~= nil)"));
  return 0;
}
