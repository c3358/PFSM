# PFSM
personal file security management
注：
1、文件过滤驱动使用的源码是看雪论坛某位大神的
/****************************************
 *  代码作者:   看雪论坛 tianhz  
 *  姓名:       Francisco Edylas Tian
 ****************************************/
2、 OverlayIcon使用的国外某博客的事例源码

文件夹介绍：
------client      客户端登陆程序，用于打开策略管理程序，与过滤驱动通信，VS2010开发，需要配置WDK
------driver      文件过滤驱动，隐藏指定的文件，基于minifilter
------OverlayIcon 文件图标覆盖组件，给隐藏的文件加锁标记，VS2010开发
------policy      策略模块，用于用户自定义策略，指定保护的文件，Qt5开发

目前驱动还未支持开机自恢复原来的策略，每次开机需要重新配置策略，希望有大神能够完善。
服务的安装方式默认为手动安装，如需开机自启动可修改passThrough.inf文件。
