#include "shell/bar/widgets/notification_widget_definition.h"

const chiroptera::bar::WidgetDefinition<NotificationWidget::Options>& notificationWidgetDefinition() {
  using chiroptera::bar::field;
  using Options = NotificationWidget::Options;

  static const chiroptera::bar::WidgetDefinition<Options> definition{
      .type = "notifications",
      .fields = {
          field<&Options::hideWhenNoUnread>({
              .key = "hide_when_no_unread",
          }),
      },
  };
  return definition;
}
