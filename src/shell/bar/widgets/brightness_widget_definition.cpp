#include "shell/bar/widgets/brightness_widget_definition.h"

const chiroptera::bar::WidgetDefinition<BrightnessWidget::Options>& brightnessWidgetDefinition() {
  using chiroptera::bar::field;
  using Options = BrightnessWidget::Options;

  static const chiroptera::bar::WidgetDefinition<Options> definition{
      .type = "brightness",
      .fields = {
          field<&Options::showLabel>({
              .key = "show_label",
          }),
      },
  };
  return definition;
}
