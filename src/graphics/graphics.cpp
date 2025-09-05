#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EzUI/EzUI.h"

namespace py = pybind11;

void bind_graphics(py::module& m) {
    // 颜色类（简化绑定）
    py::class_<ezui::Color>(m, "Color")
        .def(py::init<>())
        .def(py::init<DWORD>(), "Create color from RGBA value")
        .def(py::init<BYTE, BYTE, BYTE, BYTE>(), "Create color from R, G, B, A values",
             py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a") = 255)
        .def("get_r", &ezui::Color::GetR, "Get red component")
        .def("get_g", &ezui::Color::GetG, "Get green component") 
        .def("get_b", &ezui::Color::GetB, "Get blue component")
        .def("get_a", &ezui::Color::GetA, "Get alpha component")
        .def_property_readonly("r", &ezui::Color::GetR, "Red component")
        .def_property_readonly("g", &ezui::Color::GetG, "Green component")
        .def_property_readonly("b", &ezui::Color::GetB, "Blue component")
        .def_property_readonly("a", &ezui::Color::GetA, "Alpha component")
        .def_static("make", &ezui::Color::Make, "Create color from string", 
                    py::arg("color_str"), py::arg("is_good") = nullptr);

#if USED_DIRECT2D
    // 图片类（简化绑定）
    py::class_<ezui::Image>(m, "Image")
        .def(py::init<int, int>(), "Create image with width and height")
        .def(py::init<const std::wstring&>(), "Create image from file")
        .def_static("make", &ezui::Image::Make, "Create image from file or resource",
                    py::arg("file_or_res"), py::return_value_policy::take_ownership);
#endif

    // StrokeStyle枚举
    py::enum_<ezui::StrokeStyle>(m, "StrokeStyle")
        .value("None", ezui::StrokeStyle::None)
        .value("Solid", ezui::StrokeStyle::Solid) 
        .value("Dash", ezui::StrokeStyle::Dash)
        .export_values();

    // 边框结构
    py::class_<ezui::Border>(m, "Border")
        .def(py::init<>())
        .def_readwrite("left", &ezui::Border::Left)
        .def_readwrite("top", &ezui::Border::Top)
        .def_readwrite("right", &ezui::Border::Right)
        .def_readwrite("bottom", &ezui::Border::Bottom)
        .def_property("color", 
            [](const ezui::Border& self) -> ezui::Color { return ezui::Color(self.Color); },
            [](ezui::Border& self, const ezui::Color& color) { self.Color = color; })
        .def_readwrite("style", &ezui::Border::Style)
        .def_readwrite("top_left_radius", &ezui::Border::TopLeftRadius)
        .def_readwrite("top_right_radius", &ezui::Border::TopRightRadius)
        .def_readwrite("bottom_left_radius", &ezui::Border::BottomLeftRadius)
        .def_readwrite("bottom_right_radius", &ezui::Border::BottomRightRadius);
        
    // 控件样式（简化绑定，避免赋值问题）
    py::class_<ezui::ControlStyle>(m, "ControlStyle")
        .def(py::init<>())
        .def_property_readonly("border", [](ezui::ControlStyle& self) -> ezui::Border& { return self.Border; }, py::return_value_policy::reference_internal)
        .def_readwrite("back_color", &ezui::ControlStyle::BackColor)
        .def_readwrite("back_image", &ezui::ControlStyle::BackImage)
        .def_readwrite("fore_image", &ezui::ControlStyle::ForeImage)
        .def_readwrite("font_family", &ezui::ControlStyle::FontFamily)
        .def_readwrite("font_size", &ezui::ControlStyle::FontSize)
        .def_readwrite("fore_color", &ezui::ControlStyle::ForeColor)
        .def_readwrite("angle", &ezui::ControlStyle::Angle)
        .def("scale", &ezui::ControlStyle::Scale, "Scale style by factor");
}