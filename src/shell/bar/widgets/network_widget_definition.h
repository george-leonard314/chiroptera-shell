#pragma once

#include "shell/bar/widget_definition.h"
#include "shell/bar/widgets/network_widget.h"

[[nodiscard]] const chiroptera::bar::WidgetDefinition<NetworkWidget::Options>& networkWidgetDefinition();
