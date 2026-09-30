#include "core/build_info.h"

#include "chiroptera_git_revision.h"

namespace chiroptera::build_info {

  std::string_view version() noexcept { return CHIROPTERA_VERSION; }

  std::string_view revision() noexcept { return CHIROPTERA_GIT_REVISION; }

  std::string displayVersion() {
    std::string label = "v";
    label += version();

    constexpr std::string_view unknownRevision = "unknown";
    const std::string_view rev = revision();
    if (!rev.empty() && rev != unknownRevision) {
      label += " (";
      label += rev;
      label += ')';
    }
    return label;
  }

} // namespace chiroptera::build_info
