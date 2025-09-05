#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EzUI/EzUI.h"
#include "EzUI/Button.h"
#include "EzUI/Label.h"
#include "EzUI/TextBox.h"
#include "EzUI/CheckBox.h"
#include "EzUI/RadioButton.h"
#include "EzUI/ComboBox.h"
#include "EzUI/PictureBox.h"
#include "EzUI/VLayout.h"
#include "EzUI/HLayout.h"
// #include "EzUI/Spacer.h"  // 暂时移除

namespace py = pybind11;

void bind_controls(py::module& m) {
    // Label控件
    py::class_<ezui::Label, ezui::Control>(m, "Label")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr)
        .def("set_text", [](ezui::Label& self, const std::wstring& text) {
            self.SetText(text);
        }, "Set label text")
        .def("get_text", [](ezui::Label& self) -> std::wstring {
            return self.GetText().unicode();
        }, "Get label text");
    
    // Button控件 (继承自Label)
    py::class_<ezui::Button, ezui::Label>(m, "Button")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr);
    
    // TextBox控件  
    py::class_<ezui::TextBox, ezui::Control>(m, "TextBox")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr)
        .def("set_text", [](ezui::TextBox& self, const std::wstring& text) {
            self.SetText(text);
        }, "Set textbox text")
        .def("get_text", [](ezui::TextBox& self) -> std::wstring {
            return self.GetText().unicode();
        }, "Get textbox text");
    
    // CheckBox控件
    py::class_<ezui::CheckBox, ezui::Control>(m, "CheckBox")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr);
    
    // RadioButton控件
    py::class_<ezui::RadioButton, ezui::Control>(m, "RadioButton")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr);
    
    // ComboBox控件
    py::class_<ezui::ComboBox, ezui::Control>(m, "ComboBox")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr);
    
    // PictureBox控件
    py::class_<ezui::PictureBox, ezui::Control>(m, "PictureBox")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr);
    
    // VLayout垂直布局
    py::class_<ezui::VLayout, ezui::Control>(m, "VLayout")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr)
        .def("add", [](ezui::VLayout& self, ezui::Control* control) -> ezui::Control* {
            // EzUI会自动管理子控件的生命周期，所以这里我们需要确保Python对象不被过早释放
            ezui::Control* result = self.Add(control);
            return result;
        }, py::return_value_policy::reference_internal, py::keep_alive<1, 2>(), "Add control to layout");
    
    // HLayout水平布局
    py::class_<ezui::HLayout, ezui::Control>(m, "HLayout")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr)
        .def("add", [](ezui::HLayout& self, ezui::Control* control) -> ezui::Control* {
            // EzUI会自动管理子控件的生命周期，所以这里我们需要确保Python对象不被过早释放
            ezui::Control* result = self.Add(control);
            return result;
        }, py::return_value_policy::reference_internal, py::keep_alive<1, 2>(), "Add control to layout");
    
    // 暂时移除Spacer绑定，因为没有公开构造函数
    // py::class_<ezui::Spacer, ezui::Control>(m, "Spacer")
    //     .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr);
}