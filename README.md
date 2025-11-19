# 简单使用 Blackfly USB3 Camera 进行图像获取

本示例演示如何使用 **Blackfly USB3 相机（Spinnaker SDK）** 进行图像采集，并在按下 **Q 键** 时将当前图像保存到指定目录。支持自定义保存目录与图片组命名。

---

## 📁 1. 功能概述

* 实时获取相机图像并显示
* 按下 **空格** 即可保存当前帧
* 保存路径可指定，例如：`D:/CapturedImages/`
* 图片命名格式：`组名_编号.jpg`（如：`GroupA_0001.jpg`）
* 自动创建目录（若不存在）

---

## 🛠️ 2. 使用前准备

1. 安装 **Spinnaker SDK**
2. 安装 OpenCV（用于显示与保存图像）
3. 连接 Blackfly USB3 Camera

---

## 💻 3. 示例代码说明

以下代码实现：

* 指定保存目录：`std::string save_folder`
* 指定图片组名：`group_id`
* 按 **Q** 保存图像

你可以自由修改：
运行时可以填写保存路径
即可将保存目录更换为自己的实验路径。

```cpp
std::string save_dir = "D:/CapturedImages/";   // 保存路径
std::string group_name = "GroupA";             // 图片组名
```

保存后的文件示例：

```
D:/CapturedImages/
└── GroupA_0001.jpg
└── GroupA_0002.jpg
└── GroupA_0003.jpg
```

---

## ▶️ 4. 按键说明

| 按键    | 功能     |
| ----- | ------ |
| Q / q | 保存当前图像 |
| ESC   | 退出程序   |

---

## 📦 5. 程序流程

1. 初始化 Spinnaker 系统与相机
2. 开始图像采集
3. 实时显示图像
4. 检测按键：

   * 若按 Q → 保存图像到目录
5. 结束采集、释放相机

---

## ✔️ 6. 注意事项

* 路径必须使用 `/` 或 `\\`
* 确保具有写入权限
* 图像保存格式可更换为 PNG/JPG/TIFF
* 需要 OpenCV 支持图像编码

---

