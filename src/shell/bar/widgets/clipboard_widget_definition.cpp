#include "shell/bar/widgets/clipboard_widget_definition.h"

#include "shell/bar/widgets/glyph_button_definition.h"

const chiroptera::bar::WidgetDefinition<ClipboardWidget::Options>& clipboardWidgetDefinition() {
  using Options = ClipboardWidget::Options;

  static const chiroptera::bar::WidgetDefinition<Options> definition{
      .type = "clipboard",
      .fields = chiroptera::bar::glyphButtonFields<Options>(),
      .glyph = [](const Options& options) { return options.glyph; },
  };
  return definition;
}
