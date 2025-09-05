#!/bin/bash

# EzUI Python绑定构建脚本 (Linux/macOS)

set -e  # 遇到错误立即退出

echo "正在构建 EzUI Python 绑定..."

# 检查Python
if ! command -v python3 &> /dev/null; then
    echo "错误: 未找到python3。请安装Python 3.7+。"
    exit 1
fi

# 检查pip
if ! command -v pip3 &> /dev/null; then
    echo "错误: 未找到pip3。请安装pip。"
    exit 1
fi

# 检查pybind11
python3 -c "import pybind11" 2>/dev/null || {
    echo "安装pybind11..."
    pip3 install pybind11
}

# 清理之前的构建
echo "清理构建目录..."
rm -rf build/
rm -rf dist/
rm -rf *.egg-info/

# 构建扩展
echo "开始构建..."
python3 setup.py build_ext --inplace

echo "构建成功!"

# 询问是否创建wheel包
read -p "是否创建wheel包? (y/n): " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo "创建wheel包..."
    pip3 install wheel
    python3 setup.py bdist_wheel
    echo "Wheel包已创建在 dist/ 目录中"
fi

echo "完成!"