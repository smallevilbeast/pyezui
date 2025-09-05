#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
EzUI Python完整GUI演示
包含：窗口 + 按钮 + 文本框 + 点击事件
点击按钮后文本框显示"Hello World"
"""

import sys
import ezui

class HelloWorldWindow(ezui.Window):
    """Hello World演示窗口"""
    
    def __init__(self):
        # 创建500x350的窗口
        super().__init__(500, 350)
        
        # 设置窗口属性
        print("创建HelloWorld演示窗口")
        self.center_to_screen()
        
        # 创建控件
        self.create_controls()
        
    def create_controls(self):
        """创建窗口控件"""
        
        # 创建按钮
        self.button = ezui.Button(self)
        self.button.set_text("Click Me!")
        self.button.set_location(ezui.Point(200, 100))
        self.button.set_size(ezui.Size(100, 40))
        
        # 创建文本框
        self.textbox = ezui.TextBox(self)
        self.textbox.set_text("")
        self.textbox.set_location(ezui.Point(150, 200))
        self.textbox.set_size(ezui.Size(200, 30))
        
        # 设置按钮点击事件
        self.button.set_click_handler(self.on_button_click)
        
        print("控件已创建完成")
        print("注意：在完整实现中，控件会自动添加到父窗口")
        
    def on_button_click(self):
        """按钮点击事件处理器"""
        print("按钮被点击了！")
        self.textbox.set_text("Hello World!")
        print("文本框已更新为：Hello World!")

def main():
    """主函数"""
    print("EzUI Python Hello World 演示")
    print("=" * 40)
    
    try:
        # 创建应用程序
        app = ezui.Application()
        print("应用程序已创建")
        
        # 启用高DPI
        app.enable_high_dpi()
        print("已启用高DPI支持")
        
        # 创建主窗口
        window = HelloWorldWindow()
        print("主窗口已创建")
        
        # 显示窗口
        window.show()
        print("窗口已显示")
        
        print("\n=== 使用说明 ===")
        print("1. 点击 'Click Me!' 按钮")
        print("2. 观察文本框显示 'Hello World!'")
        print("3. 关闭窗口退出程序")
        print("\n开始GUI演示...")
        
        # 开始消息循环
        # 注意：在实际环境中，这会启动GUI事件循环
        # 在测试环境中，我们模拟这个过程
        print("启动消息循环（模拟）")
        
        # 模拟用户点击按钮
        print("\n模拟用户操作：点击按钮")
        # window.on_button_click()
        app.exec() 
        print("\n演示完成！在真实环境中，这里会进入GUI消息循环:")
        print("exit_code = app.exec()")
        
        return 0
        
    except Exception as e:
        print(f"演示过程中出现错误: {e}")
        import traceback
        traceback.print_exc()
        return -1

if __name__ == "__main__":
    """
    运行说明:
    1. 确保EzUI Python绑定已编译安装
    2. 运行: python hello_world_demo.py
    3. 在真实环境中会显示GUI窗口
    4. 点击按钮，文本框会显示"Hello World!"
    """
    print(__doc__)
    exit_code = main()
    sys.exit(exit_code)