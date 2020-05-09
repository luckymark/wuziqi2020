# wuziqi2020
五子棋AI

本项目专门用于UESTC2020-C语言A班各位大神提交作业！

## 核心目标
利用所学C语言技能，实现五子棋AI算法

## GUI
是否使用图形界面随意！例如：
- 控制台绘制假图形界面
- [EasyX](https://easyx.cn/)
- [SFML](https://www.sfml-dev.org/)

## 参考

- [五子棋AI算法](https://blog.csdn.net/lihongxun945/category_6089493.html)

---

## 完成情况

### 第一版

* 第一版：只搜素了两层，但是个人认为AI胜率还是挺可观的（听说得到某专业人士的认可😜）快来找我试试😏（doge）不看错不轻敌的画你的胜率还是挺高的（后期还要改算法）

  方圆5*5内无棋子不考虑的简单优化，下棋挺快的，半秒不到，没有感觉很慢那种

  具体情况可以来看看  [我的五子棋AI说明博客](https://pluto-wei.github.io/2020/04/19/五子棋AI/)

  这次没有录屏，只放了几张界面截图

* 还需优化：

  显示最后一步的位置

  连赢/连输设计彩蛋

  下满显示平局

* 另外因为不熟悉c++的面向对象，就只有棋盘一个对象orz，下棋和AI都是在一个cpp里的widget...（只分了函数）还不是很清楚多个.cpp文件怎么弄（对于传参数方面）

---

### 第二版

* 第二版：实现搜索四层+$αβ$剪枝，明显变慢了，把方圆5 * 5改成3 * 3快了很多，但后期每一步还是要5-6步
* 增加了ai头文件和cpp
* 不足：下完一步以后不能立马显示（明明用了update()），必须等电脑下完一步以后才能一起显示；按键的按下与松开没有处理