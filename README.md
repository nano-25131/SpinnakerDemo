## 📁 1. 功能概述
只在 Linux 里面进行的，并未在 Win 端尝试！！！  
使用 **Blackfly USB3 相机（Spinnaker SDK）** 进行图像采集，采集到的图像放进共享内存，使用 Python 脚本即可实时读取（肉眼看不到的延迟），方便输入网络推理。  

共享内存结构如下：
```c
struct ShmImage {
   int ready;      // 0: writing, 1: ready
   int width;
   int height;
   int channels;
   unsigned char data[SHM_IMG_SIZE];
};
```

 运行程序后，直接运行**show.py**即可看到图像，想改变大小可通过Acquisition.cpp里面的#define SHM_WIDTH/SHM_HEIGHT 64 改变，同步的show.py也需要改变

---

## 🛠️ 2. 使用前准备

与主分支一致

---

## ✔️ 3. 注意事项

* 确保具有写入权限，**直接sudo运行**

---

