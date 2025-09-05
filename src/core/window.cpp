#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "EzUI/EzUI.h"
#include "EzUI/Window.h"

namespace py = pybind11;

void bind_window(py::module& m) {
    py::class_<ezui::Window, ezui::Object>(m, "Window")
        .def(py::init([](int width, int height){ 
            return new ezui::Window(width, height, NULL, WS_OVERLAPPEDWINDOW, 0); 
        }), py::arg("width"), py::arg("height"), "Create window with specified dimensions")
        
        // 基础属性  
        // HWND类型暂时移除，因为pybind11无法直接转换HWND类型
        // .def("hwnd", &ezui::Window::Hwnd, "获取窗口句柄")
        .def("x", &ezui::Window::X, "获取窗口X坐标")
        .def("y", &ezui::Window::Y, "获取窗口Y坐标")
        .def("width", &ezui::Window::Width, "获取窗口宽度")
        .def("height", &ezui::Window::Height, "获取窗口高度")
        
        // 矩形操作
        .def("get_window_rect", &ezui::Window::GetWindowRect, "获取窗口矩形",
             py::return_value_policy::reference)
        .def("get_client_rect", &ezui::Window::GetClientRect, "获取客户区矩形",
             py::return_value_policy::reference)
        .def("get_scale", &ezui::Window::GetScale, "获取DPI缩放系数")
        
        // 位置和大小设置
        .def("set_size", &ezui::Window::SetSize, "设置窗口大小")
        .def("set_location", &ezui::Window::SetLocation, "设置窗口位置")
        .def("set_rect", &ezui::Window::SetRect, "设置窗口矩形")
        .def("set_mini_size", &ezui::Window::SetMiniSize, "设置最小尺寸")
        .def("set_max_size", &ezui::Window::SetMaxSize, "设置最大尺寸")
        .def("set_fixed_size", &ezui::Window::SetFixedSize, "设置固定尺寸")
        
        // 窗口属性
        .def("set_icon", &ezui::Window::SetIcon, "设置窗口图标")
        .def("set_text", [](ezui::Window& self, const std::wstring& text) {
            self.SetText(ezui::UIString(text));
        }, "设置窗口标题")
        .def("get_text", [](ezui::Window& self) -> std::wstring {
            return self.GetText().unicode();
        }, "获取窗口标题")
        .def("set_top_most", &ezui::Window::SetTopMost, "设置窗口置顶")
        
        // 窗口状态查询
        .def("is_full_screen", &ezui::Window::IsFullScreen, "是否全屏")
        .def("is_minimized", &ezui::Window::IsMinimized, "是否最小化")
        .def("is_maximized", &ezui::Window::IsMaximized, "是否最大化")
        .def("is_top_most", &ezui::Window::IsTopMost, "是否置顶")
        .def("is_visible", &ezui::Window::IsVisible, "是否可见")
        
        // 窗口显示操作
        .def("show", py::overload_cast<>(&ezui::Window::Show), "显示窗口")
        .def("show", py::overload_cast<int>(&ezui::Window::Show), "显示窗口（带参数）")
        .def("hide", &ezui::Window::Hide, "隐藏窗口")
        .def("show_normal", &ezui::Window::ShowNormal, "正常显示窗口")
        .def("show_minimized", &ezui::Window::ShowMinimized, "最小化显示")
        .def("show_maximized", &ezui::Window::ShowMaximized, "最大化显示")
        .def("show_full_screen", &ezui::Window::ShowFullScreen, "全屏显示")
        .def("set_visible", &ezui::Window::SetVisible, "设置可见性")
        
        // 模态对话框
        .def("show_modal", &ezui::Window::ShowModal, "模态显示",
             py::arg("disable_owner") = true)
        
        // 窗口关闭和销毁
        .def("close", &ezui::Window::Close, "关闭窗口", py::arg("exit_code") = 0)
        .def("destroy", &ezui::Window::Destroy, "销毁窗口")
        
        // 窗口定位
        .def("center_to_screen", &ezui::Window::CenterToScreen, "居中到屏幕")
        .def("center_to_window", &ezui::Window::CenterToWindow, "居中到窗口",
             py::arg("wnd") = nullptr)
        
        // 布局管理
        .def("set_layout", &ezui::Window::SetLayout, py::keep_alive<1, 2>(), "设置主布局")
        .def("get_layout", &ezui::Window::GetLayout, "获取主布局",
             py::return_value_policy::reference_internal)
        
        // 控件查找
        .def("find_control", &ezui::Window::FindControl, "根据名称查找控件",
             py::return_value_policy::reference_internal)
        
        // 焦点管理
        .def("set_focus", &ezui::Window::SetFocus, "设置焦点控件")
        
        // 刷新
        .def("invalidate", &ezui::Window::Invalidate, "标记无效区域")
        .def("refresh", &ezui::Window::Refresh, "立即刷新")
        
        // 数据获取
        .def("get_public_data", &ezui::Window::GetPublicData, "获取公共数据",
             py::return_value_policy::reference_internal)
        
        // 图片管理
        .def("attach", py::overload_cast<ezui::Image*>(&ezui::Window::Attach),
             "绑定图片", py::return_value_policy::reference_internal)
        .def("detach", py::overload_cast<ezui::Image*>(&ezui::Window::Detach),
             "解绑图片");
}