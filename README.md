# Windows Default Assistant
## 提要
如果你是一个信息学竞赛生，当你来到机房打开电脑，看到桌面上一堆的无用软件，不美观的桌面壁纸，特定文件类型的打开方式需要重新设置，更何况没有编码软件和评测软件，你会不会觉得有些烦躁？这些东西都需要你进行配置，而且还不能在短时间内完成。

Windows Default Assistant改变了这一状况。它是为信息学竞赛生(OIer)打造的Windows初始化工具。可以直接下载Dev-C++ 5.9.2编码工具，CCR-Plus评测工具(同时完成环境变量的配置)，清除桌面上无用的快捷方式图标和文件，将.in/.out/.ans文件重定向到记事本打开，安装Windows计算器等。只要你具有Internet连接，且软件的放置位置合适，则以上这些设置可以在1~2分钟内完成。更高级地，它还可以下载Typora，Sublime Text和Microsoft Edge等软件。以及允许你激活Windows。
## 兼容性和可用性
Windows Default Assistant可以兼容Windows10 1809及更新系统以及所有的Windows11系统。 
目前 Windows Default Assistant 1.0.1及以上版本的核心功能可以正常使用；Windows Default Assistant 1.0.2及以上的完整功能可以正常使用。
对于Windows Default Assistant 1.0.1及以上版本的核心功能部分，若无不可抗因素，我们将持续支持其在线资源直至最少2026年10月31日。
## 注意事项
Windows Default Assistant具有高密度的指令。若发生错误，则可能对计算机及其文件造成严重损坏。因此在使用软件时，请严格遵循以下条目。

1.Windows Default Assistant不应用于个人电脑，只适合用于诸如学校机房等**公用电脑**且具有**恢复**功能的电脑。

2.Windows Default Assistant应放置在桌面且**桌面和公用桌面**无任何重要的个人文件。否则它们都会被删除。
## 内置组件的设置与隐私
Windows Default Assistant内置了一些组件。以下是关于这些组件的说明。
### Remote Collection and Analysis
Remote Collection and Analysis(远程收集与分析，RCaA)是内置于Windows Default Assistant 1.1.0 Beta及以上的数据反馈程序。这个内置程序可以发送运行日志，崩溃报告，系统信息给我们，以便我们改进软件。当RCaA启用时，软件顶部会显示一个箭头图标。你也可以将它关闭。RCaA数据通过电子邮件发送，且其的数据不会与你个人相关联。

**注意：为了保护我们的用户，我们在给出的源代码中删去了发送电子邮件需要给出的信息，以防电子邮件被截获。若你重新编译源代码，则RCaA功能将不再可用。**
### Version Check and Update
Version Checking and Updating(版本检查和更新，VCaU)是内置于Windows Default Assistant 1.0.2及以上的版本更新程序。这个内置程序用于检查是否有新版本并下载新版本。
## 许可证
本程序基于GPLv3，请在获取源代码后遵循此许可证。
