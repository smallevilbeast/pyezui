# EzUI Python Bindings

基于pybind11的EzUI C++ GUI框架Python绑定

## 目录结构

```
python_bindings/
├── src/                    # C++ 绑定源代码
│   ├── core/              # 核心绑定
│   │   ├── object.cpp     # Object类绑定
│   │   ├── control.cpp    # Control类绑定
│   │   ├── window.cpp     # Window类绑定
│   │   └── events.cpp     # 事件系统绑定
│   ├── controls/          # 控件绑定
│   │   ├── button.cpp     # Button控件
│   │   ├── label.cpp      # Label控件
│   │   ├── textbox.cpp    # TextBox控件
│   │   └── ...            # 其他控件
│   ├── graphics/          # 图形相关
│   │   ├── color.cpp      # Color类绑定
│   │   ├── image.cpp      # Image类绑定
│   │   └── render.cpp     # 渲染相关
│   └── main.cpp           # pybind11模块定义
├── include/               # 头文件包装
├── examples/              # Python示例代码
├── tests/                 # 测试代码
├── CMakeLists.txt         # CMake构建文件
├── setup.py              # Python包构建文件
└── pyproject.toml        # Python项目配置
```

## 构建要求

- C++17 或更高版本
- pybind11
- Windows SDK
- Direct2D
- Python 3.7+