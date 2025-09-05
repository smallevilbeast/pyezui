#!/usr/bin/env python3
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

import ezui

def main():
    print("Style System Test")
    print("================")
    
    try:
        # 创建应用程序
        app = ezui.Application()
        app.enable_high_dpi()
        print("✓ Application created")
        
        # 创建窗口
        window = ezui.Window(600, 400)
        window.set_text("Style Test Window")
        window.center_to_screen()
        print("✓ Window created")
        
        # 创建布局
        layout = ezui.VLayout()
        print("✓ Layout created")
        
        # 测试颜色
        green = ezui.Color(87, 177, 91, 255)  # 微信绿
        white = ezui.Color(255, 255, 255, 255)  # 白色
        gray = ezui.Color(228, 228, 228, 255)  # 边框灰
        print("✓ Colors created")
        
        # 创建按钮并设置样式
        button = ezui.Button()
        button.set_text("Styled Button")
        
        # 设置按钮样式
        button.style.back_color = green
        button.style.fore_color = white
        button.style.font_size = 16
        button.style.font_family = "Microsoft YaHei"
        
        # 设置边框
        button.style.border.left = 2
        button.style.border.top = 2
        button.style.border.right = 2
        button.style.border.bottom = 2
        button.style.border.color = gray
        button.style.border.style = ezui.StrokeStyle.Solid
        button.style.border.top_left_radius = 8
        button.style.border.top_right_radius = 8
        button.style.border.bottom_left_radius = 8
        button.style.border.bottom_right_radius = 8
        
        # 设置悬浮样式
        button.hover_style.back_color = ezui.Color(65, 154, 69, 255)  # 深绿色
        
        print("✓ Button style configured")
        
        # 创建标签并设置样式
        label = ezui.Label()
        label.set_text("Styled Label with Border")
        
        label.style.back_color = white
        label.style.fore_color = ezui.Color(51, 51, 51, 255)  # 深灰文字
        label.style.font_size = 14
        label.style.font_family = "Microsoft YaHei"
        
        # 标签边框
        label.style.border.left = 1
        label.style.border.top = 1
        label.style.border.right = 1
        label.style.border.bottom = 1
        label.style.border.color = gray
        label.style.border.style = ezui.StrokeStyle.Solid
        label.style.border.top_left_radius = 4
        label.style.border.top_right_radius = 4
        label.style.border.bottom_left_radius = 4
        label.style.border.bottom_right_radius = 4
        
        print("✓ Label style configured")
        
        # 添加到布局
        layout.add(label)
        layout.add(button)
        
        # 设置窗口布局
        window.set_layout(layout)
        print("✓ Layout configured")
        
        # 显示窗口
        window.show()
        print("✓ Window shown - Style test ready!")
        
        print("\nStyle system test completed successfully!")
        print("Close the window to exit.")
        
        # 运行消息循环
        result = app.exec()
        print(f"App exited with code: {result}")
        
    except Exception as e:
        print(f"ERROR: {e}")
        import traceback
        traceback.print_exc()
        return -1
    
    return 0

if __name__ == "__main__":
    sys.exit(main())