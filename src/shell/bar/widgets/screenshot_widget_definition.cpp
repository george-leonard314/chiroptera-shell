#include "shell/bar/widgets/screenshot_widget_definition.h"

#include "shell/bar/widgets/glyph_button_definition.h"

const chiroptera::bar::WidgetDefinition<ScreenshotWidget::Options>& screenshotWidgetDefinition() {
  using Options = ScreenshotWidget::Options;

  static const chiroptera::bar::WidgetDefinition<Options> definition{
      .type = "screenshot",
      .fields = chiroptera::bar::glyphButtonFields<Options>(),
  };
  return definition;
}
