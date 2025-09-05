#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EzUI/EzUI.h"

namespace py = pybind11;

void bind_object(py::module& m) {
    py::class_<ezui::Object>(m, "Object")
        .def(py::init<ezui::Object*>(), py::arg("parent_object") = nullptr)
        .def_readwrite("tag", &ezui::Object::Tag, "User-defined data")
        
        // 属性系统
        .def("set_attribute", &ezui::Object::SetAttribute, "Set attribute value", 
             py::arg("attr_name"), py::arg("attr_value"))
        .def("get_attribute", &ezui::Object::GetAttribute, "Get attribute value", 
             py::arg("attr_name"))
        .def("get_attributes", &ezui::Object::GetAttributes, "Get all attributes", 
             py::return_value_policy::reference)
        .def("remove_attribute", &ezui::Object::RemoveAttribute, "Remove attribute", 
             py::arg("attr_name"))
             
        // 对象管理
        .def("attach", &ezui::Object::Attach, "Attach child object for automatic cleanup", 
             py::arg("obj"), py::return_value_policy::reference_internal)
        .def("detach", &ezui::Object::Detach, "Detach child object from automatic cleanup", 
             py::arg("obj"))
        .def("delete_later", &ezui::Object::DeleteLater, "Schedule object for deletion");
}