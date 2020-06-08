# wuziqi2020
## 五子棋AI
    实现了4层极大极小值搜索的五子棋AI。
## 开发环境
    操作系统：Windows 10
    IDE：Clion2019.3.3
    GUI：Qt Creator 4.11.0
### 无法运行可能的原因
-     若报错Process finished with exit code -1073741515 (0xC0000135)
      则需要配置环境变量，例如path=D:\Qt\Qt5.14.1\5.14.1\mingw73_32\bin
-     若报错Process finished with exit code -1073741701 (0xC000007B)
      则可能是编译和配置环境变量时选择的mingw版本不一致。应该统一为32位或64位。
      例如，在Cmakelists.txt里是CMAKE_PREFIX_PATH D:/Qt/Qt5.14.1/5.14.1/mingw73_32
      在配置环境变量时也应该path=D:\Qt\Qt5.14.1\5.14.1\mingw73_32\bin
      同理，若在Cmakelists.txt里是CMAKE_PREFIX_PATH D:/Qt/Qt5.14.1/5.14.1/mingw73_64
      在配置环境变量时也应该path=D:\Qt\Qt5.14.1\5.14.1\mingw73_64\bin
