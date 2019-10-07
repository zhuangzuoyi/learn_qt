一个简单的不能再简单工具，把头文件包含进去也才14行代码，如下

```c==
#include <QCoreApplication>
#include "QtSerialPort/QSerialPortInfo"
#include <iostream>
#include "QtDebug"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QString menu_temp = info.portName() + " : " + info.description();
        qDebug() << menu_temp;
    }
}
```



这个程序只能在命令行中打开，是用来显示电脑中串口的详细信息，因为工作学习中经常要使用到串口，几乎每次使用要打开设备管理器查看用的是哪个串口，有时候打开会很慢，要等上几秒钟，还有使用设备管理器查看串口设备需要如下步骤：

1、打开计算机管理

2、选择设备管理器

3、从众多硬件中找到串口

很浪费时间，于是，我就想着写了这个软件，把该软件的目录添加到环境变量，就可以在命令行中打开，如下，window 7  cmd中：

![cmd](img\cmd.png)

还有在VScode中的执行结果如下；

![vscode](img\vscode.png)