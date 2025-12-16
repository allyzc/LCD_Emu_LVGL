# LVGL Qt Simulator

一个基于 **Qt 5.15.2 + LVGL** 的桌面模拟器工程，用于在 PC（Windows）环境下快速开发、调试和验证嵌入式 LVGL UI。

该项目的目标是：
- **在不依赖真实硬件的情况下** 调试 LVGL 界面逻辑
- **最大限度复用嵌入式端代码**，做到“PC 调通 → 上板即用”
- 作为一个**可开源、可复现、可二次开发**的 LVGL PC 仿真参考工程

---

## ✨ 特性（Features）

- ✅ 基于 Qt Widget 的 LVGL PC 模拟器
- ✅ 使用 Qt 绘制 LVGL Framebuffer（RGB888 / ARGB8888）
- ✅ 鼠标模拟触摸输入（Press / Release / Move）
- ✅ LVGL Tick 定时器与事件循环对接
- ✅ 与嵌入式工程保持一致的 `lv_conf.h` 配置方式
- ✅ 适合调试：
  - UI 布局
  - 控件事件逻辑
  - 动画 / 样式

---

## 🧱 架构说明（Architecture）

```
+-------------------+        +-------------------+
|     Qt Window     |        |   Mouse / Timer   |
|  (Widget / View) |<------>|   Event Adapter   |
+---------+---------+        +---------+---------+
          |                              |
          v                              v
+-----------------------------------------------+
|                   LVGL Core                   |
|  - lv_obj / lv_draw / lv_event / lv_timer     |
+-----------------------------------------------+
          |
          v
+-------------------+
|   Framebuffer     |
|  (Qt QImage)      |
+-------------------+
```

- Qt 负责：
  - 窗口管理
  - 绘制显示
  - 鼠标事件
- LVGL 负责：
  - UI 控件
  - 布局 / 动画 / 样式
  - 业务逻辑

---

## 📦 目录结构（Directory Layout）

```
.
├─ app/                    # 应用层（你的 UI / 业务代码）
│  └─ ui/
├─ lvgl/                   # LVGL 源码（官方仓库）
│  ├─ src/
│  └─ lv_conf.h
├─ port/                   # 平台适配层（PC / Qt）
│  ├─ display_port.cpp     # 显示接口适配
│  ├─ touch_port.cpp       # 触摸接口适配
│  └─ tick_port.cpp        # LVGL Tick 适配
├─ qt/                     # Qt 相关代码
│  ├─ LcdEmulatorWidget.*
│  └─ mainwindow.*
├─ main.cpp
├─ *.pro
└─ README.md
```

> 💡 `port/` 目录的职责与嵌入式中的 `bsp / drv` 层一致，用于隔离平台差异。

---

## 🛠 构建环境（Build Environment）

- 操作系统：Windows 10 / 11
- Qt：**Qt 5.15.2**
- 编译器：MinGW 64-bit
- LVGL：v8.x（可自行替换）

> ⚠️ 目前未验证 MSVC，如需支持可自行调整 `.pro` 配置。

---

## 🚀 快速开始（Quick Start）

1. 克隆仓库
   ```bash
   git clone https://github.com/allyzc/LCD_Emu_LVGL.git
   ```

2. 使用 **Qt Creator** 打开 `.pro` 文件

3. 编译并运行

4. 启动后即可在 PC 窗口中看到 LVGL UI

---

## 🖱 输入说明（Input）

- 鼠标左键：模拟触摸按下 / 释放
- 鼠标移动：模拟触摸滑动（如启用）

> 输入事件通过 `touch_port` 转换为 LVGL 的 `lv_indev` 接口。

---

## 🧪 调试建议（Debug Tips）

- 建议在 **Debug 模式** 下运行
- 可在 `lv_conf.h` 中打开：
  ```c
  #define LV_USE_LOG 1
  #define LV_LOG_LEVEL LV_LOG_LEVEL_INFO
  ```
- Qt Creator 可直接：
  - 单步调试 LVGL 内部逻辑
  - 实时查看 Framebuffer 数据

---

## 📄 License

This project is licensed under the **MIT License**.

It is based on **LVGL**, which is also licensed under the MIT License.

- LVGL: https://github.com/lvgl/lvgl

> 使用、修改和分发本项目时，请保留原始版权声明。

---

## 🤝 适用人群（Who is this for）

- 嵌入式 GUI / HMI 工程师
- 使用 LVGL 的物联网 / 工控开发者
- 希望在 PC 上快速验证 UI 的开发者

---

## 📌 说明

- 本项目定位为 **LVGL PC 仿真参考工程**，而非官方模拟器
- 欢迎 issue / PR / fork

---

## ⭐ 致谢（Acknowledgements）

- [LVGL](https://lvgl.io)
- Qt Framework

如果这个项目对你有帮助，欢迎 Star ⭐

