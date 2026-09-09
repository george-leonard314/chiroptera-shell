#include "shell/bar/widgets/theme_mode_widget_definition.h"

const chiroptera::bar::WidgetDefinition<std::monostate>& themeModeWidgetDefinition() {
  static const chiroptera::bar::WidgetDefinition<std::monostate> definition{
      .type = "theme_mode",
  };
  return definition;
}
