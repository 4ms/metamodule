#pragma once

#include "lvgl.h" //For events
#include <array>
#include <string_view>

namespace LVGLStrings
{
constexpr std::array<std::string_view, _LV_EVENT_LAST> Events{{
	{"LV_EVENT_PRESSED"},	 /**< The object has been pressed*/
	{"LV_EVENT_PRESSING"},	 /**< The object is being pressed (called continuously while pressing)*/
	{"LV_EVENT_PRESS_LOST"}, /**< User is still pressing but slid cursor/finger off of the object */
	{"LV_EVENT_SHORT_CLICKED"}, /**< User pressed object for a short period of time, then released it. Not called if dragged. */
	{"LV_EVENT_LONG_PRESSED"}, /**< Object has been pressed for at least `LV_INDEV_LONG_PRESS_TIME`. Not called if dragged.*/
	{"LV_EVENT_LONG_PRESSED_REPEAT"}, /**< Called after `LV_INDEV_LONG_PRESS_TIME` in every `LV_INDEV_LONG_PRESS_REP_TIME` ms. Not called if dragged.*/
	{"LV_EVENT_CLICKED"},  /**< Called on release if not dragged (regardless to long press)*/
	{"LV_EVENT_RELEASED"}, /**< Called in every cases when the object has been released*/
	{"LV_EVENT_DRAG_BEGIN"},
	{"LV_EVENT_DRAG_END"},
	{"LV_EVENT_DRAG_THROW_BEGIN"},
	{"LV_EVENT_GESTURE"}, /**< The object has been gesture*/
	{"LV_EVENT_KEY"},
	{"LV_EVENT_FOCUSED"},
	{"LV_EVENT_DEFOCUSED"},
	{"LV_EVENT_LEAVE"},
	{"LV_EVENT_VALUE_CHANGED"}, /**< The object's value has changed (i.e. slider moved) */
	{"LV_EVENT_INSERT"},
	{"LV_EVENT_REFRESH"},
	{"LV_EVENT_APPLY"},	 /**< "Ok", "Apply" or similar specific button has clicked*/
	{"LV_EVENT_CANCEL"}, /**< "Close", "Cancel" or similar specific button has clicked*/
	{"LV_EVENT_DELETE"}, /**< Object is being deleted */
}};

};
