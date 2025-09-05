# EzUI Python Bindings

基于pybind11的EzUI C++ GUI框架Python绑定，为Python开发者提供高性能的Windows原生GUI开发能力。

## 快速开始

### 1. 拉取项目

```bash
# 克隆项目（包含子模块）
git clone --recursive https://github.com/smallevilbeast/pyezui.git
cd pyezui

# 如果已经克隆但忘记了 --recursive，可以单独拉取子模块
git submodule update --init --recursive
```

### 2. 环境要求

**系统要求：**
- Windows 10/11 (推荐)
- Visual Studio 2019/2022 (包含C++ Build Tools)
- Python 3.7 或更高版本

**依赖库：**
```bash
# 安装Python依赖
pip install -r requirements.txt

# 或者直接安装pybind11
pip install pybind11>=2.6.0
```

### 3. 编译项目

#### 方法一：使用setup.py编译（推荐）

```bash
# 编译并安装到当前目录
python setup.py build_ext --inplace

# 或者安装到Python环境
pip install .

# 开发模式安装（修改代码后无需重新安装）
pip install -e .
```


### 4. 验证安装

```python
# 测试导入
import ezui
print("EzUI Python bindings imported successfully!")

# 创建简单窗口示例
app = ezui.Application()
window = ezui.Window()
window.set_title("Hello EzUI")
window.set_size(400, 300)
window.show()
# app.run()  # 取消注释以运行事件循环
```

## 项目结构

```
pyezui/
├── src/                    # C++ 绑定源代码
│   ├── core/              # 核心绑定
│   │   ├── object.cpp     # Object类绑定
│   │   ├── control.cpp    # Control类绑定
│   │   ├── window.cpp     # Window类绑定
│   │   ├── application.cpp # Application类绑定
│   │   └── events.cpp     # 事件系统绑定
│   ├── controls/          # 控件绑定
│   │   └── controls.cpp   # 各种控件绑定
│   ├── graphics/          # 图形相关
│   │   └── graphics.cpp   # 图形和渲染绑定
│   └── main.cpp           # pybind11模块定义入口
├── EzUI/                  # EzUI C++库子模块
├── examples/              # Python示例代码
├── include/               # 头文件包装
├── build/                 # 构建输出目录
├── setup.py              # Python包构建文件
├── pyproject.toml        # Python项目配置
├── requirements.txt      # Python依赖列表
└── README.md             # 项目文档
```

## 常见问题

### 编译错误

**Q: 编译时出现 "EventFilter" 或 "EventPassThrough" 不存在的错误**
A: 这些属性在当前版本的EzUI中不存在，已在最新版本中修复。请确保使用最新的代码。

**Q: 编译时出现大量类型转换警告**
A: 这些是正常的类型转换警告，不会影响编译结果。可以忽略这些警告。

**Q: 找不到Visual Studio编译器**
A: 确保安装了Visual Studio 2019/2022并包含C++ Build Tools，或者安装Visual Studio Build Tools。

### 运行时错误

**Q: 导入ezui模块时出现DLL加载错误**
A: 确保系统上安装了Visual C++ Redistributable，并且Python版本与编译时使用的版本匹配。

**Q: 在非Windows系统上运行**
A: EzUI是Windows专用的GUI框架，依赖Direct2D和Windows API，无法在其他操作系统上运行。

## 开发指南

### 添加新的绑定

1. 在 `src/` 目录下的相应子目录中创建新的 `.cpp` 文件
2. 包含必要的头文件和pybind11相关头文件
3. 使用pybind11的语法定义Python绑定
4. 在 `setup.py` 中添加新的源文件路径

### 构建配置

- **Debug模式**: 添加 `--debug` 参数到 `python setup.py build_ext` 命令
- **并行编译**: 设置环境变量 `NPY_NUM_BUILD_JOBS` 来控制并行编译线程数
- **自定义编译选项**: 修改 `setup.py` 中的 `CustomBuildExt` 类

## 示例代码

### 基础窗口应用

```python
import ezui

# 创建应用程序实例
app = ezui.Application()

# 创建主窗口
window = ezui.Window()
window.set_title("EzUI Python 示例")
window.set_size(800, 600)
window.set_location(100, 100)

# 创建按钮控件
button = ezui.Button()
button.set_text("点击我")
button.set_location(50, 50)
button.set_size(100, 30)

# 添加控件到窗口
window.add(button)

# 显示窗口
window.show()

# 运行消息循环
app.run()
```

### 事件处理

```python
import ezui

def on_button_click(control, event):
    print(f"按钮被点击了！控件: {control}")

app = ezui.Application()
window = ezui.Window()

button = ezui.Button()
button.set_text("事件示例")
button.event_handler = on_button_click  # 设置事件处理器

window.add(button)
window.show()
app.run()
```

## 技术细节

### 支持的控件类型

- **基础控件**: Control, Window, Button, Label
- **输入控件**: TextBox, CheckBox, RadioButton
- **容器控件**: Panel, TabControl
- **列表控件**: ListView, TreeView
- **高级控件**: ComboBox, ProgressBar

### 绑定特性

- 自动内存管理（通过pybind11的智能指针支持）
- Python风格的属性访问
- 事件处理机制
- 异常安全的API调用
- 类型安全的参数传递

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件

## 贡献

欢迎提交Issue和Pull Request！请确保：

1. 代码符合项目的编码规范
2. 添加必要的测试用例
3. 更新相关文档
4. 提交前运行所有测试

## 联系方式

- GitHub: https://github.com/smallevilbeast/pyezui
- Issues: https://github.com/smallevilbeast/pyezui/issues