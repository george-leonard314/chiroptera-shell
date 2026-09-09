#pragma once

namespace chiroptera::config {

  // Entry point for `chiroptera config <command> [options]`. Returns a process
  // exit code. Pure CLI helper; does not start Application or mutate live config.
  int runCli(int argc, char* argv[]);

} // namespace chiroptera::config
