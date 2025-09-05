#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EzUI/EzUI.h"

namespace py = pybind11;

void bind_events(py::module& m) {
    // 基础事件参数类
    py::class_<ezui::EventArgs>(m, "EventArgs")
        .def(py::init<ezui::Event>())
        .def_readwrite("event_type", &ezui::EventArgs::EventType);
        
    // 鼠标事件参数
    py::class_<ezui::MouseEventArgs, ezui::EventArgs>(m, "MouseEventArgs")
        .def(py::init<ezui::Event, const ezui::Point&, ezui::MouseButton, int>(),
             py::arg("event_type"), py::arg("location") = ezui::Point(0, 0), 
             py::arg("mouse_button") = ezui::MouseButton::None, py::arg("z_delta") = 0)
        .def_readwrite("button", &ezui::MouseEventArgs::Button)
        .def_readwrite("z_delta", &ezui::MouseEventArgs::ZDelta)
        .def_readwrite("location", &ezui::MouseEventArgs::Location);
        
    // 键盘事件参数
    py::class_<ezui::KeyboardEventArgs, ezui::EventArgs>(m, "KeyboardEventArgs")
        .def(py::init<ezui::Event, WPARAM, LPARAM>())
        .def_readwrite("w_param", &ezui::KeyboardEventArgs::wParam)
        .def_readwrite("l_param", &ezui::KeyboardEventArgs::lParam);
        
    // 暂时移除焦点事件参数绑定，因为依赖Control类
    // py::class_<ezui::FocusEventArgs, ezui::EventArgs>(m, "FocusEventArgs")
    //     .def(py::init<ezui::Control*>())
    //     .def_readwrite("control", &ezui::FocusEventArgs::Control);
    //     
    // py::class_<ezui::KillFocusEventArgs, ezui::EventArgs>(m, "KillFocusEventArgs")
    //     .def(py::init<ezui::Control*>())
    //     .def_readwrite("control", &ezui::KillFocusEventArgs::Control);
        
    // 移动事件参数
    py::class_<ezui::MoveEventArgs, ezui::EventArgs>(m, "MoveEventArgs")
        .def(py::init<const ezui::Point&>())
        .def_property_readonly("location", [](const ezui::MoveEventArgs& self) -> const ezui::Point& { return self.Location; });
        
    // 大小改变事件参数
    py::class_<ezui::SizeEventArgs, ezui::EventArgs>(m, "SizeEventArgs")
        .def(py::init<const ezui::Size&>())
        .def_property_readonly("size", [](const ezui::SizeEventArgs& self) -> const ezui::Size& { return self.Size; });
        
    // DPI改变事件参数
    py::class_<ezui::DpiChangeEventArgs, ezui::EventArgs>(m, "DpiChangeEventArgs")
        .def(py::init<float>())
        .def_readwrite("scale", &ezui::DpiChangeEventArgs::Scale);
        
    // 绘制事件参数（简化版本，因为包含复杂的渲染器对象）
    py::class_<ezui::PaintEventArgs, ezui::EventArgs>(m, "PaintEventArgs")
        .def_readonly("hwnd", &ezui::PaintEventArgs::HWND)
        .def_readonly("dc", &ezui::PaintEventArgs::DC)
        .def_readwrite("invalid_rectangle", &ezui::PaintEventArgs::InvalidRectangle)
        .def("push_offset", &ezui::PaintEventArgs::PushOffset, "Push drawing offset")
        .def("pop_offset", &ezui::PaintEventArgs::PopOffset, "Pop drawing offset")
        .def("pop_layer", &ezui::PaintEventArgs::PopLayer, "Pop clipping layer");
}