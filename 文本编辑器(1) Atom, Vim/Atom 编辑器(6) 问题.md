# GBK 编码问题

1. 查找乱码: 查找面板中，只支持 utf8 编码字符的显示，gbk 编码的中文注释会显示乱码, 可在查找文件中随意输入一个字符, 即可更新显示为正确字符
2. 替换乱码: gbk 和 utf8 相互转换会出现经典的"锟斤拷"乱码, 为避免此问题, 应将所有存在替换操作的文件打开, 即加载到 buffer 中
3. 查找不到头文件中的标识符: 使用在项目中查找时，头文件中的标识符找不到，utf8 则没问题, 解决办法是不能在一行宏定义的后面使用中文注释

# 插件问题

1. 开启 activate-power-mode 后在 markdown 下会异常的卡顿, 关闭前者即可

# 快捷键问题

1. 升级 windows 10 周年版后, ctrl-shift-f 与操作系统的繁简切换冲突

# 参考

1. 以上纯属个人经验
