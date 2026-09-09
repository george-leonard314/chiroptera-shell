#include "shell/bar/widgets/text_widget_definition.h"

const chiroptera::bar::WidgetDefinition<TextWidget::Options>& textWidgetDefinition() {
  using chiroptera::bar::field;
  using Options = TextWidget::Options;

  static const chiroptera::bar::WidgetDefinition<Options> definition{
      .type = "text",
      .fields = {
          field<&Options::text>({
              .key = "text",
          }),
      },
  };
  return definition;
}
