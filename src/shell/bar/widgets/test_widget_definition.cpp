#include "shell/bar/widgets/test_widget_definition.h"

const chiroptera::bar::WidgetDefinition<std::monostate>& testWidgetDefinition() {
  static const chiroptera::bar::WidgetDefinition<std::monostate> definition{
      .type = "test",
  };
  return definition;
}
