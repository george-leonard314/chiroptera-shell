#pragma once

namespace chiroptera::ipc {

  // Entry point for `chiroptera msg <command> [args...]`. Returns a process exit
  // code. Forwards the command to the running instance over the IPC socket.
  int runCli(int argc, char* argv[]);

} // namespace chiroptera::ipc
