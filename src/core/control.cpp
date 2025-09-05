#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "EzUI/EzUI.h"
#include "EzUI/Control.h"

namespace py = pybind11;

void bind_control(py::module& m) {
    py::class_<ezui::Control, ezui::Object>(m, "Control")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr)
        
        // 公共属性
        .def_readwrite("margin", &ezui::Control::Margin, "外边距")
        .def_readwrite("name", &ezui::Control::Name, "控件名称")
        .def_readwrite("action", &ezui::Control::Action, "控件行为")
        // ControlStyle的赋值操作符是私有的，使用getter方法代替
        .def_property_readonly("style", [](ezui::Control& self) -> ezui::ControlStyle& { return self.Style; }, "静态默认样式", py::return_value_policy::reference_internal)
        .def_property_readonly("disabled_style", [](ezui::Control& self) -> ezui::ControlStyle& { return self.DisabledStyle; }, "禁用状态样式", py::return_value_policy::reference_internal)
        .def_property_readonly("hover_style", [](ezui::Control& self) -> ezui::ControlStyle& { return self.HoverStyle; }, "鼠标悬浮样式", py::return_value_policy::reference_internal)
        .def_property_readonly("active_style", [](ezui::Control& self) -> ezui::ControlStyle& { return self.ActiveStyle; }, "鼠标按下样式", py::return_value_policy::reference_internal)
        .def_readonly("parent", &ezui::Control::Parent, "父控件指针")
        
        // 事件处理器
        .def_readwrite("event_handler", &ezui::Control::EventHandler, "事件处理函数")
        
        // 基础属性获取和设置方法
        .def("hwnd", &ezui::Control::Hwnd, "获取窗口句柄")
        .def("set_hwnd", &ezui::Control::SetHwnd, "设置窗口句柄")
        
        // 位置和大小
        .def("x", &ezui::Control::X, "获取X坐标")
        .def("y", &ezui::Control::Y, "获取Y坐标") 
        .def("width", &ezui::Control::Width, "获取宽度")
        .def("height", &ezui::Control::Height, "获取高度")
        .def("set_x", &ezui::Control::SetX, "设置X坐标")
        .def("set_y", &ezui::Control::SetY, "设置Y坐标")
        .def("set_location", &ezui::Control::SetLocation, "设置位置")
        .def("set_size", &ezui::Control::SetSize, "设置大小")
        .def("set_width", &ezui::Control::SetWidth, "设置宽度")
        .def("set_height", &ezui::Control::SetHeight, "设置高度")
        .def("set_rect", &ezui::Control::SetRect, "设置矩形", 
             py::return_value_policy::reference)
        
        // 固定大小
        .def("set_fixed_size", &ezui::Control::SetFixedSize, "设置绝对宽高")
        .def("set_fixed_width", &ezui::Control::SetFixedWidth, "设置绝对宽度")
        .def("set_fixed_height", &ezui::Control::SetFixedHeight, "设置绝对高度")
        .def("get_fixed_width", &ezui::Control::GetFixedWidth, "获取绝对宽度")
        .def("get_fixed_height", &ezui::Control::GetFixedHeight, "获取绝对高度")
        
        // 比例大小
        .def("set_rate_width", &ezui::Control::SetRateWidth, "设置宽度比例")
        .def("set_rate_height", &ezui::Control::SetRateHeight, "设置高度比例")
        
        // 自动大小
        .def("is_auto_width", &ezui::Control::IsAutoWidth, "是否自动宽度")
        .def("is_auto_height", &ezui::Control::IsAutoHeight, "是否自动高度")
        .def("set_auto_width", &ezui::Control::SetAutoWidth, "设置自动宽度")
        .def("set_auto_height", &ezui::Control::SetAutoHeight, "设置自动高度")
        .def("set_auto_size", &ezui::Control::SetAutoSize, "设置自动大小")
        
        // 获取方法
        .def("get_content_size", &ezui::Control::GetContentSize, "获取内容大小",
             py::return_value_policy::reference)
        .def("get_size", &ezui::Control::GetSize, "获取控件大小")
        .def("get_location", &ezui::Control::GetLocation, "获取控件位置")
        .def("get_rect", &ezui::Control::GetRect, "获取控件矩形",
             py::return_value_policy::reference)
        .def("get_client_rect", &ezui::Control::GetClientRect, "获取客户区矩形")
        .def("get_screen_rect", &ezui::Control::GetScreenRect, "获取屏幕矩形")
        .def("get_care_rect", &ezui::Control::GetCareRect, "获取光标位置")
        
        // 停靠样式
        .def("get_dock_style", &ezui::Control::GetDockStyle, "获取停靠样式")
        .def("set_dock_style", &ezui::Control::SetDockStyle, "设置停靠样式")
        
        // 缩放和布局
        .def("get_scale", &ezui::Control::GetScale, "获取缩放系数")
        .def("is_pend_layout", &ezui::Control::IsPendLayout, "是否有挂起的布局")
        .def("try_pend_layout", &ezui::Control::TryPendLayout, "尝试挂起布局")
        .def("get_layout_state", &ezui::Control::GetLayoutState, "获取布局状态")
        .def("end_layout", &ezui::Control::EndLayout, "结束布局")
        .def("refresh_layout", &ezui::Control::RefreshLayout, "刷新布局")
        
        // 提示文字
        .def("set_tips", &ezui::Control::SetTips, "设置提示文字")
        .def("get_tips", &ezui::Control::GetTips, "获取提示文字",
             py::return_value_policy::reference)
             
        // 暂时移除滚动条绑定
        // .def("get_scroll_bar", &ezui::Control::GetScrollBar, "获取滚动条",
        //      py::return_value_policy::reference_internal)
        
        // 事件派发
        .def("send_event", &ezui::Control::SendEvent, "派发事件")
        
        // 添加Python事件处理支持
        .def("set_click_handler", [](ezui::Control& self, py::function callback) {
            self.EventHandler = [callback](ezui::Control* ctrl, ezui::EventArgs& args) {
                // 只处理鼠标点击事件
                if (args.EventType == ezui::Event::OnMouseUp) {
                    try {
                        callback();
                    } catch (const std::exception& e) {
                        // 处理Python异常
                        py::print("Error in click handler:", e.what());
                    }
                }
            };
        }, "设置点击事件处理器")
        
        // 子控件管理
        .def("get_view_controls", &ezui::Control::GetViewControls, "获取可见子控件",
             py::return_value_policy::reference)
        .def("get_controls", &ezui::Control::GetControls, "获取所有子控件",
             py::return_value_policy::reference)
        .def("get_control", &ezui::Control::GetControl, "通过索引获取控件",
             py::return_value_policy::reference_internal)
        .def("contains", &ezui::Control::Contains, "是否包含指定控件")
        .def("index_of", &ezui::Control::IndexOf, "获取子控件索引")
        
        // 查找控件
        .def("find_control", py::overload_cast<const ezui::UIString&>(&ezui::Control::FindControl),
             "根据名称查找控件", py::return_value_policy::reference_internal)
        .def("find_control", py::overload_cast<const ezui::UIString&, const ezui::UIString&>(&ezui::Control::FindControl),
             "根据属性查找控件")
        .def("find_single_control", &ezui::Control::FindSingleControl,
             "根据属性查找单个控件", py::return_value_policy::reference_internal)
        .def("find_child", py::overload_cast<const ezui::UIString&>(&ezui::Control::FindChild),
             "根据名称查找子控件", py::return_value_policy::reference_internal)
        .def("find_child", py::overload_cast<const ezui::UIString&, const ezui::UIString&>(&ezui::Control::FindChild),
             "根据属性查找子控件")
        .def("find_single_child", &ezui::Control::FindSingleChild,
             "根据属性查找单个子控件", py::return_value_policy::reference_internal)
        
        // 控件操作
        .def("swap_child", &ezui::Control::SwapChild, "交换两个子控件位置")
        .def("insert", &ezui::Control::Insert, "插入子控件")
        .def("add", &ezui::Control::Add, 
             py::return_value_policy::reference_internal, py::keep_alive<1, 2>(), "添加子控件")
        .def("remove", &ezui::Control::Remove, "移除子控件",
             py::arg("child_ctl"), py::arg("free_ctrl") = false)
        .def("set_parent", &ezui::Control::SetParent, "设置父控件")
        .def("clear", py::overload_cast<>(&ezui::Control::Clear), "清空所有子控件")
        .def("clear", py::overload_cast<bool>(&ezui::Control::Clear), "清空所有子控件",
             py::arg("free_childs"))
        
        // 启用/禁用
        .def("set_enabled", &ezui::Control::SetEnabled, "设置启用状态")
        .def("set_disabled", &ezui::Control::SetDisabled, "设置禁用状态")
        .def("is_enabled", &ezui::Control::IsEnabled, "是否已启用")
        
        // 可见性
        .def("set_visible", &ezui::Control::SetVisible, "设置可见性")
        .def("is_visible", &ezui::Control::IsVisible, "获取可见性")
        .def("hide", &ezui::Control::Hide, "隐藏控件")
        .def("show", &ezui::Control::Show, "显示控件")
        
        // 刷新
        .def("invalidate", &ezui::Control::Invalidate, "标记无效区域")
        .def("refresh", &ezui::Control::Refresh, "立即刷新")
        
        // 样式
        .def("set_style", &ezui::Control::SetStyle, "设置样式")
        .def("set_style_sheet", &ezui::Control::SetStyleSheet, "设置样式表")
        
        // 状态
        .def("is_pressed", &ezui::Control::IsPressed, "是否被按住")
        
        // 图片管理
        .def("attach", py::overload_cast<ezui::Image*>(&ezui::Control::Attach),
             "绑定图片", py::return_value_policy::reference_internal)
        .def("detach", py::overload_cast<ezui::Image*>(&ezui::Control::Detach),
             "解绑图片")
        
        // 样式获取方法
        .def("get_style", &ezui::Control::GetStyle, "获取当前样式",
             py::return_value_policy::reference, py::arg("state") = ezui::ControlState::None)
        .def("get_border_color", &ezui::Control::GetBorderColor, "获取边框颜色")
        .def("get_back_color", &ezui::Control::GetBackColor, "获取背景颜色")
        .def("get_fore_color", &ezui::Control::GetForeColor, "获取前景颜色")
        .def("get_font_family", &ezui::Control::GetFontFamily, "获取字体族")
        .def("get_font_size", &ezui::Control::GetFontSize, "获取字体大小")
        .def("get_back_image", &ezui::Control::GetBackImage, "获取背景图片",
             py::return_value_policy::reference_internal)
        .def("get_fore_image", &ezui::Control::GetForeImage, "获取前景图片",
             py::return_value_policy::reference_internal)
        .def("get_angle", &ezui::Control::GetAngle, "获取旋转角度")
        .def("get_cursor", &ezui::Control::GetCursor, "获取鼠标光标");
}