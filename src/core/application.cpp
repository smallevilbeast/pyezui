#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "EzUI/EzUI.h"
#include "EzUI/Application.h"

namespace py = pybind11;

void bind_application(py::module& m) {
    py::class_<ezui::Application>(m, "Application")
        .def(py::init([](){ return new ezui::Application(NULL); }), 
             "Create application instance")
        
        // 实例方法
        .def("set_resource", &ezui::Application::SetResource,
             "Load resource package from local file or resource ID",
             py::arg("local_or_res_name"))
        .def("enable_high_dpi", &ezui::Application::EnableHighDpi,
             "Enable high DPI adaptation")
        .def("exec", &ezui::Application::Exec,
             "Execute message loop and return exit code")
        
        // 静态方法
        .def_static("exit", &ezui::Application::Exit,
                   "Exit message loop", py::arg("exit_code") = 0)
        .def_static("start_path", &ezui::Application::StartPath,
                   "Get application startup path");
}