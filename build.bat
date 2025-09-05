@echo off
REM EzUI Python绑定构建脚本

echo 正在构建 EzUI Python 绑定...

REM 检查Python和pip
python --version >nul 2>&1
if errorlevel 1 (
    echo 错误: 未找到Python。请确保Python已安装并在PATH中。
    pause
    exit /b 1
)

REM 检查是否有pybind11
python -c "import pybind11" >nul 2>&1
if errorlevel 1 (
    echo 安装pybind11...
    pip install pybind11
)

REM 清理之前的构建
if exist build rmdir /s /q build
if exist dist rmdir /s /q dist
if exist *.egg-info rmdir /s /q *.egg-info

REM 构建扩展
echo 开始构建...
python setup.py build_ext --inplace

if errorlevel 1 (
    echo 构建失败!
    pause
    exit /b 1
)

echo 构建成功!

REM 可选：创建wheel包
set /p CREATE_WHEEL="是否创建wheel包? (y/n): "
if /i "%CREATE_WHEEL%"=="y" (
    echo 创建wheel包...
    pip install wheel
    python setup.py bdist_wheel
    echo Wheel包已创建在 dist/ 目录中
)

echo 完成!
pause