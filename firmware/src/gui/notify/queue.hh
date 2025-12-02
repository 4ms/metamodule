#pragma once
#include "gui/notify/notification.hh"
#include "util/circular_buffer_opt.hh"

namespace MetaModule
{

using NotificationQueue = CircularBufferOpt<Notification, 8>;

} // namespace MetaModule
