#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>

// 包含EzUI头文件
#include "EzUI/EzUI.h"

namespace py = pybind11;

// 前向声明绑定函数
void bind_core(py::module& m);
void bind_object(py::module& m);
void bind_control(py::module& m);
void bind_window(py::module& m);
void bind_application(py::module& m);
void bind_events(py::module& m);
void bind_graphics(py::module& m);
void bind_controls(py::module& m);

PYBIND11_MODULE(ezui, m) {
    m.doc() = "EzUI Python bindings - A lightweight Windows GUI framework (Basic version)";
    
    // 绑定核心类和枚举
    bind_core(m);
    bind_object(m);
    bind_control(m);
    bind_window(m);
    bind_application(m);
    bind_events(m);
    bind_graphics(m);
    bind_controls(m);
    
    // 暂时移除全局函数绑定，避免链接问题
    // m.def("is_float_equal", &ezui::IsFloatEqual, "Check if two floats are equal");
    // m.def("load_icon", &ezui::LoadIcon, "Load icon from file");
    // m.def("install_font", &ezui::InstallFont, "Install font from file");
    // m.def("uninstall_font", &ezui::UnstallFont, "Uninstall font");
    // m.def("copy_to_clipboard", py::overload_cast<const std::wstring&, HWND>(&ezui::CopyToClipboard), "Copy text to clipboard", py::arg("text"), py::arg("hwnd") = nullptr);
    // m.def("get_clipboard_data", py::overload_cast<std::wstring*, HWND>(&ezui::GetClipboardData), "Get text from clipboard", py::arg("out_str"), py::arg("hwnd") = nullptr);
    // m.def("get_resource", &ezui::GetResource, "Get resource data from file or embedded resource");
    
    // 模块版本信息
    m.attr("__version__") = "0.1.0-basic";
}