#include "shell/bar/widgets/settings_widget_definition.h"

#include "shell/bar/widgets/glyph_button_definition.h"

const chiroptera::bar::WidgetDefinition<SettingsWidget::Options>& settingsWidgetDefinition() {
  using Options = SettingsWidget::Options;

  static const chiroptera::bar::WidgetDefinition<Options> definition{
      .type = "settings",
      .fields = chiroptera::bar::glyphButtonFields<Options>(),
      .glyph = [](const Options& options) { return options.glyph; },
  };
  return definition;
}
