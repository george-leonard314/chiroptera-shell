#include "shell/bar/widgets/launcher_widget_definition.h"

#include "shell/bar/widgets/glyph_button_definition.h"

const chiroptera::bar::WidgetDefinition<LauncherWidget::Options>& launcherWidgetDefinition() {
  using Options = LauncherWidget::Options;

  static const chiroptera::bar::WidgetDefinition<Options> definition{
      .type = "launcher",
      .fields = chiroptera::bar::glyphButtonFields<Options>(),
      .glyph = [](const Options& options) { return options.glyph; },
  };
  return definition;
}
