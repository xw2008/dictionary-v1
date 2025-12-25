# 📘 C语言简易电子词典 (Electronic Dictionary)

这是一个基于 C 语言开发的控制台电子词典项目。支持英汉互译、单词管理以及智能模糊查找功能。readme文档由gemini生成

## ✨ 主要功能

- **英汉/汉英查询**：支持输入英文查中文，或输入中文查英文。
- **智能模糊查找**：
  - 支持前缀匹配联想（输入 `app` 联想 `apple`, `apply`）。
  - 支持中文包含查找（输入 `苹果` 可查到 `apple`）。
- **词库管理**：支持添加新词、修改释义、删除单词。
- **背单词模式**：包含单词预览、复习功能。
- **数据持久化**：所有数据保存在 `cet4.txt` 文件中，程序启动时自动加载。

## 🛠️ 技术栈

- **语言**：C (Standard C99)
- **构建工具**：CMake
- **开发工具**：CLion / Visual Studio Code

## 🚀 快速开始

### 1. 环境要求
确保你的电脑上安装了 C 语言编译器 (GCC/MinGW) 和 CMake。

### 2. 获取代码
```bash
git clone [https://github.com/xw2008/dictionary-v1.git](https://github.com/xw2008/dictionary-v1.git)
cd dictionary_v1
Maintainer: @xw2008
