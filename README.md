# oop-experiment
## 2024年西电软工面向对象实验题解总结
## 使用注意：
编译器为g++，需要支持c++ 11标准
使用vscode+cmake构建项目，克隆代码后请使用ctrl+shift+p打开命令界面，输入CMake: Configure选择g++编译器完成配置
克隆代码后，需要修改 People.cpp 和 Store.cpp 开头处定义的表示文件位置的宏
同时需要修改 ShoppingCartData.cpp 和 HistoryData.cpp 中在函数中定义的文件路径字符串，每个.cpp文件中均需要修改3处
修改完成后，请预先在指定路径创建文件夹，以及 People.cpp 和 Store.cpp 中由宏定义的txt文件，否则无法正常运行
