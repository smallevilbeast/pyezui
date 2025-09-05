#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EzUI/EzUI.h"

namespace py = pybind11;

void bind_core(py::module& m) {
    // 绑定基础结构体
    py::class_<ezui::Point>(m, "Point")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def_readwrite("x", &ezui::Point::X)
        .def_readwrite("y", &ezui::Point::Y)
        .def("__repr__", [](const ezui::Point& p) {
            return "Point(" + std::to_string(p.X) + ", " + std::to_string(p.Y) + ")";
        });
        
    py::class_<ezui::Size>(m, "Size")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def_readwrite("width", &ezui::Size::Width)
        .def_readwrite("height", &ezui::Size::Height)
        .def("__repr__", [](const ezui::Size& s) {
            return "Size(" + std::to_string(s.Width) + ", " + std::to_string(s.Height) + ")";
        });
        
    py::class_<ezui::Rect>(m, "Rect")
        .def(py::init<>())
        .def(py::init<int, int, int, int>())
        .def_readwrite("x", &ezui::Rect::X)
        .def_readwrite("y", &ezui::Rect::Y)
        .def_readwrite("width", &ezui::Rect::Width)
        .def_readwrite("height", &ezui::Rect::Height)
        .def("get_left", &ezui::Rect::GetLeft)
        .def("get_top", &ezui::Rect::GetTop)
        .def("get_right", &ezui::Rect::GetRight)
        .def("get_bottom", &ezui::Rect::GetBottom)
        .def("get_location", &ezui::Rect::GetLocation)
        .def("get_size", &ezui::Rect::GetSize)
        .def("contains", py::overload_cast<const ezui::Point&>(&ezui::Rect::Contains, py::const_))
        .def("contains", py::overload_cast<const ezui::Rect&>(&ezui::Rect::Contains, py::const_))
        .def("__repr__", [](const ezui::Rect& r) {
            return "Rect(" + std::to_string(r.X) + ", " + std::to_string(r.Y) + ", " + 
                   std::to_string(r.Width) + ", " + std::to_string(r.Height) + ")";
        });
        
    py::class_<ezui::SizeF>(m, "SizeF")
        .def(py::init<>())
        .def(py::init<float, float>())
        .def_readwrite("width", &ezui::SizeF::Width)
        .def_readwrite("height", &ezui::SizeF::Height);
        
    py::class_<ezui::Distance>(m, "Distance")
        .def(py::init<>())
        .def(py::init<WORD>())
        .def_readwrite("left", &ezui::Distance::Left)
        .def_readwrite("top", &ezui::Distance::Top)
        .def_readwrite("right", &ezui::Distance::Right)
        .def_readwrite("bottom", &ezui::Distance::Bottom);
        
    // 绑定枚举
    py::enum_<ezui::Event>(m, "Event")
        .value("None", ezui::Event::None)
        .value("OnMouseWheel", ezui::Event::OnMouseWheel)
        .value("OnMouseEnter", ezui::Event::OnMouseEnter)
        .value("OnMouseMove", ezui::Event::OnMouseMove)
        .value("OnMouseLeave", ezui::Event::OnMouseLeave)
        .value("OnMouseDoubleClick", ezui::Event::OnMouseDoubleClick)
        .value("OnMouseDown", ezui::Event::OnMouseDown)
        .value("OnMouseUp", ezui::Event::OnMouseUp)
        .value("OnKeyDown", ezui::Event::OnKeyDown)
        .value("OnKeyUp", ezui::Event::OnKeyUp)
        .value("OnPaint", ezui::Event::OnPaint)
        .value("OnFocus", ezui::Event::OnFocus)
        .value("OnKillFocus", ezui::Event::OnKillFocus)
        .value("OnKeyChar", ezui::Event::OnKeyChar)
        .value("OnMove", ezui::Event::OnMove)
        .value("OnSize", ezui::Event::OnSize)
        .value("OnRect", ezui::Event::OnRect)
        .value("OnDpiChange", ezui::Event::OnDpiChange)
        .value("OnActive", ezui::Event::OnActive)
        .value("OnHover", ezui::Event::OnHover)
        .value("OnMouseDrag", ezui::Event::OnMouseDrag)
        .value("OnMouseEvent", ezui::Event::OnMouseEvent)
        .value("OnKeyBoardEvent", ezui::Event::OnKeyBoardEvent)
        .export_values();
        
    py::enum_<ezui::ControlAction>(m, "ControlAction")
        .value("None", ezui::ControlAction::None)
        .value("Title", ezui::ControlAction::Title)
        .value("MoveWindow", ezui::ControlAction::MoveWindow)
        .value("Mini", ezui::ControlAction::Mini)
        .value("Max", ezui::ControlAction::Max)
        .value("Close", ezui::ControlAction::Close)
        .export_values();
        
    py::enum_<ezui::ControlState>(m, "ControlState")
        .value("None", ezui::ControlState::None)
        .value("Static", ezui::ControlState::Static)
        .value("Disabled", ezui::ControlState::Disabled)
        .value("Checked", ezui::ControlState::Checked)
        .value("Hover", ezui::ControlState::Hover)
        .value("Active", ezui::ControlState::Active)
        .export_values();
        
    py::enum_<ezui::DockStyle>(m, "DockStyle")
        .value("None", ezui::DockStyle::None)
        .value("Horizontal", ezui::DockStyle::Horizontal)
        .value("Vertical", ezui::DockStyle::Vertical)
        .value("Fill", ezui::DockStyle::Fill)
        .export_values();
        
    py::enum_<ezui::MouseButton>(m, "MouseButton")
        .value("None", ezui::MouseButton::None)
        .value("Left", ezui::MouseButton::Left)
        .value("Right", ezui::MouseButton::Right)
        .value("Middle", ezui::MouseButton::Middle)
        .value("XButton1", ezui::MouseButton::XButton1)
        .value("XButton2", ezui::MouseButton::XButton2)
        .export_values();
        
    py::enum_<ezui::Cursor>(m, "Cursor")
        .value("None", ezui::Cursor::None)
        .value("ARROW", ezui::Cursor::ARROW)
        .value("IBEAM", ezui::Cursor::IBEAM)
        .value("WAIT", ezui::Cursor::WAIT)
        .value("CROSS", ezui::Cursor::CROSS)
        .value("HAND", ezui::Cursor::HAND)
        .value("HELP", ezui::Cursor::HELP)
        .value("NO", ezui::Cursor::NO)
        .value("SIZEALL", ezui::Cursor::SIZEALL)
        .value("SIZENESW", ezui::Cursor::SIZENESW)
        .value("SIZENS", ezui::Cursor::SIZENS)
        .value("SIZENWSE", ezui::Cursor::SIZENWSE)
        .value("SIZEWE", ezui::Cursor::SIZEWE)
        .export_values();
        
    py::enum_<ezui::LayoutState>(m, "LayoutState")
        .value("None", ezui::LayoutState::None)
        .value("Pend", ezui::LayoutState::Pend)
        .value("Layouting", ezui::LayoutState::Layouting)
        .export_values();
        
    // 绑定MonitorInfo结构体
    py::class_<ezui::MonitorInfo>(m, "MonitorInfo")
        .def(py::init<>())
        .def_readonly("monitor", &ezui::MonitorInfo::Monitor)
        .def_readwrite("rect", &ezui::MonitorInfo::Rect)
        .def_readwrite("work_rect", &ezui::MonitorInfo::WorkRect)
        .def_readwrite("physical", &ezui::MonitorInfo::Physical)
        .def_readwrite("scale", &ezui::MonitorInfo::Scale)
        .def_readwrite("fps", &ezui::MonitorInfo::FPS)
        .def_readwrite("primary", &ezui::MonitorInfo::Primary);
}