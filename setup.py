import os
import sys
import subprocess
from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11.setup_helpers import ParallelCompile
from setuptools import setup

# 并行编译
ParallelCompile("NPY_NUM_BUILD_JOBS", needs_recompile=True).install()

# 项目根目录
project_root = Path(__file__).parent
ezui_root = project_root / "EzUI"

# 源文件列表
ext_modules = [
    Pybind11Extension(
        "ezui",
        # 绑定源文件
        [
            str(project_root / "src/main.cpp"),
            str(project_root / "src/core/core.cpp"),
            str(project_root / "src/core/object.cpp"),
            str(project_root / "src/core/control.cpp"),
            str(project_root / "src/core/window.cpp"),
            str(project_root / "src/core/application.cpp"),
            str(project_root / "src/core/events.cpp"),
            str(project_root / "src/graphics/graphics.cpp"),
            str(project_root / "src/controls/controls.cpp"),
        ] + 
        # EzUI完整源文件
        list(map(str, (ezui_root / "sources").glob("*.cpp"))),
        
        # 包含目录
        include_dirs=[
            str(ezui_root / "include"),
            str(ezui_root / "include" / "EzUI"),  # 添加EzUI头文件目录支持直接包含
            str(project_root / "include"),
        ],
        
        # 预处理器定义
        define_macros=[
            ("VERSION_INFO", '"dev"'),
            ("_UNICODE", None),
            ("UNICODE", None),
            ("USED_DIRECT2D", "1"),
            ("WIN32_LEAN_AND_MEAN", None),
            # 移除NOMINMAX以兼容EzUI使用的min/max函数
        ],
        
        # 链接库 (Windows)
        libraries=[
            "d2d1", "dwrite", "windowscodecs", 
            "user32", "gdi32", "ole32", "oleaut32", 
            "uuid", "kernel32", "shell32", "advapi32",
            "comdlg32", "comctl32"
        ] if sys.platform == "win32" else [],
        
        # C++标准
        cxx_std=17,
    ),
]

# 读取README文件
long_description = ""
readme_file = project_root / "README.md"
if readme_file.exists():
    with open(readme_file, "r", encoding="utf-8") as f:
        long_description = f.read()

# 自定义构建扩展
class CustomBuildExt(build_ext):
    def build_extensions(self):
        # Windows特定编译选项
        if sys.platform == "win32":
            for ext in self.extensions:
                ext.extra_compile_args = [
                    "/utf-8",
                    "/EHsc",
                    "/std:c++17",
                ]
                # Release模式优化
                if not self.debug:
                    ext.extra_compile_args.extend([
                        "/O2",
                        "/DNDEBUG",
                        "/MT",
                    ])
                else:
                    ext.extra_compile_args.extend([
                        "/Od", 
                        "/D_DEBUG",
                        "/MTd",
                        "/Zi",
                    ])
        else:
            # Linux/Unix编译选项
            for ext in self.extensions:
                ext.extra_compile_args = [
                    "-finput-charset=UTF-8",
                    "-fexec-charset=UTF-8",
                    "-std=c++17",
                ]
        
        super().build_extensions()

setup(
    name="ezui",
    version="0.1.0",
    author="EzUI Team",
    author_email="support@ezui.com",
    description="Python bindings for EzUI - A lightweight Windows GUI framework",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/ezui/ezui-python",
    project_urls={
        "Bug Tracker": "https://github.com/ezui/ezui-python/issues",
        "Documentation": "https://docs.ezui.com/python",
        "Source Code": "https://github.com/ezui/ezui-python",
    },
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Microsoft :: Windows",
        "Programming Language :: C++",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: Python :: 3.12",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: Software Development :: User Interfaces",
    ],
    keywords="gui ui windows direct2d native",
    ext_modules=ext_modules,
    cmdclass={"build_ext": CustomBuildExt},
    zip_safe=False,
    python_requires=">=3.7",
    install_requires=[
        "pybind11>=2.6.0",
    ],
    extras_require={
        "dev": [
            "pytest>=6.0",
            "pytest-cov",
            "sphinx",
            "sphinx-rtd-theme",
        ],
    },
    package_data={
        "ezui": ["py.typed"],
    },
)