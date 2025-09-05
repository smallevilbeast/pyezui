#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
微信风格 EzUI Python 示例
展示完整的Style系统，创建仿微信界面
"""

import sys
import ezui

# 微信配色方案
class WeChatColors:
    # 主色调
    GREEN = ezui.Color(87, 177, 91)        # 微信绿 #57B15A
    DARK_GREEN = ezui.Color(65, 154, 69)   # 深绿色
    
    # 背景色
    BACKGROUND = ezui.Color(245, 245, 245)  # 浅灰背景
    WHITE = ezui.Color(255, 255, 255)       # 纯白
    
    # 文字颜色
    TEXT_PRIMARY = ezui.Color(51, 51, 51)   # 主文字
    TEXT_SECONDARY = ezui.Color(153, 153, 153) # 次要文字
    
    # 边框和分隔线
    BORDER = ezui.Color(228, 228, 228)      # 边框灰
    DIVIDER = ezui.Color(238, 238, 238)     # 分隔线

class WeChatMessageItem:
    """微信消息条目"""
    
    def __init__(self, sender_name, message_text, is_self=False):
        self.is_self = is_self
        self.container = ezui.VLayout()
        self.create_message_ui(sender_name, message_text)
        
    def create_message_ui(self, sender_name, message_text):
        # 设置消息项背景
        self.container.style.back_color = WeChatColors.BACKGROUND
        self.container.set_fixed_height(80)
        
        # 创建消息容器 - 使用水平布局实现左右对齐
        message_container = ezui.HLayout()
        
        if self.is_self:
            # 自己的消息：右对齐布局
            # 添加弹性空间把消息推到右边
            spacer = ezui.VLayout()
            spacer.style.back_color = WeChatColors.BACKGROUND
            message_container.add(spacer)
            
            # 消息内容区域
            content_area = ezui.VLayout()
            content_area.set_fixed_width(300)
            
            # 消息气泡
            message_bubble = ezui.Label()
            message_bubble.set_text(message_text)
            message_bubble.style.font_size = 14
            message_bubble.style.font_family = "Microsoft YaHei"
            message_bubble.style.back_color = WeChatColors.GREEN
            message_bubble.style.fore_color = WeChatColors.WHITE
            message_bubble.style.border.top_left_radius = 12
            message_bubble.style.border.top_right_radius = 12  
            message_bubble.style.border.bottom_left_radius = 12
            message_bubble.style.border.bottom_right_radius = 12
            
            # 发送者姓名（自己的消息可以省略或显示"我"）
            name_label = ezui.Label()
            name_label.set_text("我")
            name_label.style.font_size = 12
            name_label.style.fore_color = WeChatColors.TEXT_SECONDARY
            name_label.style.font_family = "Microsoft YaHei"
            
            content_area.add(name_label)
            content_area.add(message_bubble)
            message_container.add(content_area)
            
            # 头像
            avatar = ezui.Label()
            avatar.set_text("🙋")
            avatar.style.font_size = 28
            avatar.style.back_color = WeChatColors.GREEN
            avatar.style.fore_color = WeChatColors.WHITE
            avatar.style.border.top_left_radius = 20
            avatar.style.border.top_right_radius = 20
            avatar.style.border.bottom_left_radius = 20
            avatar.style.border.bottom_right_radius = 20
            avatar.set_fixed_size(ezui.Size(40, 40))
            message_container.add(avatar)
            
        else:
            # 对方的消息：左对齐布局
            # 头像
            avatar = ezui.Label()
            avatar.set_text("👤")
            avatar.style.font_size = 28
            avatar.style.back_color = WeChatColors.BACKGROUND
            avatar.style.border.top_left_radius = 20
            avatar.style.border.top_right_radius = 20
            avatar.style.border.bottom_left_radius = 20
            avatar.style.border.bottom_right_radius = 20
            avatar.set_fixed_size(ezui.Size(40, 40))
            message_container.add(avatar)
            
            # 消息内容区域
            content_area = ezui.VLayout()
            content_area.set_fixed_width(300)
            
            # 发送者姓名
            name_label = ezui.Label()
            name_label.set_text(sender_name)
            name_label.style.font_size = 12
            name_label.style.fore_color = WeChatColors.TEXT_SECONDARY
            name_label.style.font_family = "Microsoft YaHei"
            
            # 消息气泡
            message_bubble = ezui.Label()
            message_bubble.set_text(message_text)
            message_bubble.style.font_size = 14
            message_bubble.style.font_family = "Microsoft YaHei"
            message_bubble.style.back_color = WeChatColors.WHITE
            message_bubble.style.fore_color = WeChatColors.TEXT_PRIMARY
            message_bubble.style.border.left = 1
            message_bubble.style.border.top = 1
            message_bubble.style.border.right = 1
            message_bubble.style.border.bottom = 1
            message_bubble.style.border.color = WeChatColors.BORDER
            message_bubble.style.border.style = ezui.StrokeStyle.Solid
            message_bubble.style.border.top_left_radius = 12
            message_bubble.style.border.top_right_radius = 12
            message_bubble.style.border.bottom_left_radius = 12
            message_bubble.style.border.bottom_right_radius = 12
            
            content_area.add(name_label)
            content_area.add(message_bubble)
            message_container.add(content_area)
            
            # 添加弹性空间
            spacer = ezui.VLayout()
            spacer.style.back_color = WeChatColors.BACKGROUND
            message_container.add(spacer)
        
        self.container.add(message_container)

class WeChatMainWindow:
    """微信主窗口"""
    
    def __init__(self):
        self.window = ezui.Window(800, 600)
        self.setup_window()
        self.create_layout()
        
    def setup_window(self):
        """设置窗口属性"""
        self.window.set_text("微信风格演示 - EzUI Python")
        self.window.center_to_screen()
        
        # 设置最小尺寸
        self.window.set_mini_size(ezui.Size(600, 400))
        
    def create_layout(self):
        """创建主布局"""
        # 主容器
        main_container = ezui.HLayout()
        main_container.style.back_color = WeChatColors.BACKGROUND
        
        # 左侧边栏
        sidebar = self.create_sidebar()
        
        # 中间聊天列表
        chat_list = self.create_chat_list()
        
        # 右侧聊天区域
        chat_area = self.create_chat_area()
        
        # 添加到主容器
        main_container.add(sidebar)
        main_container.add(chat_list)
        main_container.add(chat_area)
        
        # 设置到窗口
        self.window.set_layout(main_container)
        
    def create_sidebar(self):
        """创建左侧边栏"""
        sidebar = ezui.VLayout()
        sidebar.set_fixed_width(60)
        sidebar.style.back_color = WeChatColors.TEXT_PRIMARY
        
        # 头像
        profile_btn = ezui.Button()
        profile_btn.set_text("👤")
        profile_btn.style.font_size = 24
        profile_btn.style.back_color = WeChatColors.TEXT_PRIMARY
        profile_btn.style.fore_color = WeChatColors.WHITE
        profile_btn.hover_style.back_color = WeChatColors.DARK_GREEN
        profile_btn.set_fixed_size(ezui.Size(50, 50))
        
        # 聊天按钮
        chat_btn = ezui.Button()
        chat_btn.set_text("💬")
        chat_btn.style.font_size = 20
        chat_btn.style.back_color = WeChatColors.GREEN
        chat_btn.style.fore_color = WeChatColors.WHITE
        chat_btn.style.border.top_left_radius = 8
        chat_btn.style.border.top_right_radius = 8
        chat_btn.style.border.bottom_left_radius = 8
        chat_btn.style.border.bottom_right_radius = 8
        chat_btn.hover_style.back_color = WeChatColors.DARK_GREEN
        chat_btn.set_fixed_size(ezui.Size(40, 40))
        
        # 通讯录按钮
        contact_btn = ezui.Button()
        contact_btn.set_text("📋")
        contact_btn.style.font_size = 20
        contact_btn.style.back_color = WeChatColors.TEXT_PRIMARY
        contact_btn.style.fore_color = WeChatColors.WHITE
        contact_btn.hover_style.back_color = WeChatColors.DARK_GREEN
        contact_btn.set_fixed_size(ezui.Size(40, 40))
        
        # 添加按钮到侧边栏
        sidebar.add(profile_btn)
        sidebar.add(chat_btn)
        sidebar.add(contact_btn)
        
        return sidebar
        
    def create_chat_list(self):
        """创建聊天列表"""
        chat_list_container = ezui.VLayout()
        chat_list_container.set_fixed_width(280)
        chat_list_container.style.back_color = WeChatColors.WHITE
        chat_list_container.style.border.right = 1
        chat_list_container.style.border.color = WeChatColors.BORDER
        chat_list_container.style.border.style = ezui.StrokeStyle.Solid
        
        # 搜索框
        search_box = ezui.TextBox()
        search_box.set_text("搜索")
        search_box.style.back_color = WeChatColors.BACKGROUND
        search_box.style.fore_color = WeChatColors.TEXT_SECONDARY
        search_box.style.font_size = 14
        search_box.style.font_family = "Microsoft YaHei"
        search_box.style.border.left = 1
        search_box.style.border.top = 1
        search_box.style.border.right = 1
        search_box.style.border.bottom = 1
        search_box.style.border.color = WeChatColors.BORDER
        search_box.style.border.style = ezui.StrokeStyle.Solid
        search_box.style.border.top_left_radius = 6
        search_box.style.border.top_right_radius = 6
        search_box.style.border.bottom_left_radius = 6
        search_box.style.border.bottom_right_radius = 6
        search_box.set_fixed_height(32)
        
        # 聊天项列表
        chat_items = ezui.VLayout()
        
        # 添加一些聊天项
        chat_names = ["张三", "李四", "王五", "工作群", "家人群", "同学群"]
        last_messages = [
            "你好，最近怎么样？",
            "明天的会议准备好了吗",
            "周末一起吃饭吧",
            "项目进度如何？",
            "今晚回家吃饭",
            "同学聚会定在下周"
        ]
        
        for i, (name, message) in enumerate(zip(chat_names, last_messages)):
            chat_item = self.create_chat_item(name, message)
            chat_items.add(chat_item)
            
        chat_list_container.add(search_box)
        chat_list_container.add(chat_items)
        
        return chat_list_container
        
    def create_chat_item(self, name, last_message):
        """创建聊天项"""
        item = ezui.HLayout()
        item.style.back_color = WeChatColors.WHITE
        item.style.border.bottom = 1
        item.style.border.color = WeChatColors.DIVIDER
        item.style.border.style = ezui.StrokeStyle.Solid
        item.hover_style.back_color = WeChatColors.BACKGROUND
        item.set_fixed_height(70)
        
        # 头像
        avatar = ezui.Label()
        avatar.set_text("👤")
        avatar.style.font_size = 28
        avatar.style.back_color = WeChatColors.BACKGROUND
        avatar.style.border.top_left_radius = 20
        avatar.style.border.top_right_radius = 20
        avatar.style.border.bottom_left_radius = 20
        avatar.style.border.bottom_right_radius = 20
        avatar.set_fixed_size(ezui.Size(40, 40))
        
        # 内容区域
        content = ezui.VLayout()
        
        # 姓名
        name_label = ezui.Label()
        name_label.set_text(name)
        name_label.style.font_size = 16
        name_label.style.fore_color = WeChatColors.TEXT_PRIMARY
        name_label.style.font_family = "Microsoft YaHei"
        
        # 最后消息
        message_label = ezui.Label()
        message_label.set_text(last_message)
        message_label.style.font_size = 12
        message_label.style.fore_color = WeChatColors.TEXT_SECONDARY
        message_label.style.font_family = "Microsoft YaHei"
        
        content.add(name_label)
        content.add(message_label)
        
        item.add(avatar)
        item.add(content)
        
        return item
        
    def create_chat_area(self):
        """创建聊天区域"""
        chat_area = ezui.VLayout()
        chat_area.style.back_color = WeChatColors.BACKGROUND
        
        # 聊天标题栏
        title_bar = ezui.HLayout()
        title_bar.style.back_color = WeChatColors.WHITE
        title_bar.style.border.bottom = 1
        title_bar.style.border.color = WeChatColors.BORDER
        title_bar.style.border.style = ezui.StrokeStyle.Solid
        title_bar.set_fixed_height(50)
        
        title_label = ezui.Label()
        title_label.set_text("张三")
        title_label.style.font_size = 18
        title_label.style.fore_color = WeChatColors.TEXT_PRIMARY
        title_label.style.font_family = "Microsoft YaHei"
        
        title_bar.add(title_label)
        
        # 消息列表区域
        messages_area = ezui.VLayout()
        
        # 添加一些示例消息
        messages = [
            ("张三", "你好！最近怎么样？", False),
            ("我", "还不错，工作比较忙", True),
            ("张三", "理解理解，要注意休息哦", False),
            ("我", "好的，谢谢关心！", True),
            ("张三", "周末有空一起吃饭吗？", False),
            ("我", "好啊，什么时候？", True),
        ]
        
        for sender, message, is_self in messages:
            msg_item = WeChatMessageItem(sender, message, is_self)
            messages_area.add(msg_item.container)
        
        # 输入区域
        input_area = ezui.VLayout()
        input_area.set_fixed_height(120)
        input_area.style.back_color = WeChatColors.WHITE
        input_area.style.border.top = 1
        input_area.style.border.color = WeChatColors.BORDER
        input_area.style.border.style = ezui.StrokeStyle.Solid
        
        # 工具栏
        toolbar = ezui.HLayout()
        toolbar.set_fixed_height(40)
        
        emoji_btn = ezui.Button()
        emoji_btn.set_text("😀")
        emoji_btn.style.font_size = 16
        emoji_btn.style.back_color = WeChatColors.WHITE
        emoji_btn.hover_style.back_color = WeChatColors.BACKGROUND
        emoji_btn.set_fixed_size(ezui.Size(30, 30))
        
        toolbar.add(emoji_btn)
        
        # 输入框
        input_box = ezui.TextBox()
        input_box.set_text("")
        input_box.style.font_size = 14
        input_box.style.font_family = "Microsoft YaHei"
        input_box.style.back_color = WeChatColors.WHITE
        input_box.style.fore_color = WeChatColors.TEXT_PRIMARY
        
        # 发送按钮
        send_area = ezui.HLayout()
        send_area.set_fixed_height(35)
        
        send_btn = ezui.Button()
        send_btn.set_text("发送")
        send_btn.style.back_color = WeChatColors.GREEN
        send_btn.style.fore_color = WeChatColors.WHITE
        send_btn.style.font_size = 14
        send_btn.style.font_family = "Microsoft YaHei"
        send_btn.style.border.top_left_radius = 6
        send_btn.style.border.top_right_radius = 6
        send_btn.style.border.bottom_left_radius = 6
        send_btn.style.border.bottom_right_radius = 6
        send_btn.hover_style.back_color = WeChatColors.DARK_GREEN
        send_btn.set_fixed_size(ezui.Size(80, 32))
        
        # 设置发送按钮点击事件
        send_btn.set_click_handler(lambda: self.send_message(input_box, messages_area))
        
        send_area.add(send_btn)
        
        input_area.add(toolbar)
        input_area.add(input_box)
        input_area.add(send_area)
        
        chat_area.add(title_bar)
        chat_area.add(messages_area)
        chat_area.add(input_area)
        
        return chat_area
        
    def send_message(self, input_box, messages_area):
        """发送消息"""
        message_text = input_box.get_text()
        if message_text.strip():
            # 添加新消息
            msg_item = WeChatMessageItem("我", message_text, True)
            messages_area.add(msg_item.container)
            
            # 清空输入框
            input_box.set_text("")
            
            print(f"发送消息: {message_text}")
            
    def show(self):
        """显示窗口"""
        self.window.show()

def main():
    """主函数"""
    print("微信风格 EzUI Python 演示")
    print("=" * 40)
    print("展示完整的Style系统和微信风格界面")
    
    try:
        # 创建应用程序
        app = ezui.Application()
        app.enable_high_dpi()
        print("应用程序已创建")
        
        # 创建微信风格主窗口
        window = WeChatMainWindow()
        print("微信风格窗口已创建")
        
        # 显示窗口
        window.show()
        print("窗口已显示")
        
        print("\n=== 微信风格界面特性 ===")
        print("- 完整的配色方案 (微信绿、背景灰等)")
        print("- 圆角边框和阴影效果")
        print("- 分层布局 (侧边栏、聊天列表、聊天区域)")
        print("- 样式化的按钮和输入框")
        print("- 消息气泡效果")
        print("- 悬浮样式和交互效果")
        print("- 完整的Style系统演示")
        
        print("\n开始GUI消息循环...")
        
        # 启动消息循环
        exit_code = app.exec()
        return exit_code
        
    except Exception as e:
        print(f"错误: {e}")
        import traceback
        traceback.print_exc()
        return -1

if __name__ == "__main__":
    exit_code = main()
    print(f"\n微信风格演示结束，退出代码: {exit_code}")
    sys.exit(exit_code)