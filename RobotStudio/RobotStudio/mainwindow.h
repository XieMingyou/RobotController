#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTableWidget>
#include <QCloseEvent>
#include "tinystr.h"
#include "tinyxml.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool getElementByName(TiXmlElement *rootElem, const char *destElemName, TiXmlElement **destElem); //通过元素名称查找指定元素
    void setAxisAttribute(TiXmlElement *pElem, QTableWidget *tableWidget, int column); //设置机器人关于轴的属性
    void getAxisAttribute(TiXmlElement *pElem, QTableWidget *tableWidget, int column); //从xml配置文件中读取关于轴的属性并显示
    void showRobot(); //显示选中的机器人的配置数据
    void statusCheck(); //检查机器人是否已经配置完，如果是，则status属性置为"available"
    /*
     TiXmlDocument：文档类，它代表了整个xml文件
     TiXmlDeclaration：声明类，它表示文件的声明部分
     TiXmlComment：注释类，它表示文件的注释部分
     TiXmlElement：元素类，它是文件的主要部分，并且支持嵌套结构，一般使用这种结构来分类的存储信息，它可以包含属性类和文本类
     TiXmlAttribute/TiXmlAttributeSet：元素属性，它一般嵌套在元素中，用于记录此元素的一些属性
     TiXmlText：文本对象，它嵌套在某个元素内部
    */
    TiXmlDocument doc; //xml文件
    TiXmlElement *rootElem; //xml文件根元素
    QString configFileName; //配置文件名
    int numRobot = 0; //建有的机器人数量
    int curRobot = 0; //当前显示的机器人的序号
    QString robotName; //机器人名称
    QString robotType; //机器人类型
    QString baseNum; //机器人基本轴数量
    QString wristNum; //机器人手腕轴数量
    TiXmlElement *robotInstance = nullptr; //复制粘贴用的机器人实例
    QTreeWidgetItem *curItem = nullptr; //当前点击的item
    QString oldName; //旧的机器人名称，用于重命名

private:
    Ui::MainWindow *ui;

private slots:
    void clickTreeWidgetItem(QTreeWidgetItem *item); //单击treeWidget时的响应
    void doubleClickRobotItem(QTreeWidgetItem *); //双击robotItem时的响应
    void finishEdit(); //重命名完成编辑的响应
    void saveRobot(); //保存当前机器人的配置数据, flag为true时表示新建机器人的首次初始化保存，为false时表示已建机器人的更新保存
    void copyRobot(); //复制选中的机器人的所有配置数据
    void pasteRobot(); //粘贴选中的机器人的所有配置数据
    void clearRobot(); //清空选中的机器人的所有配置数据
    void renameRobot(); //重命名选中的机器人的所有配置数据
    void deleteRobot(); //删除选中的机器人的所有配置数据
    void newRobot();
    void closeEvent( QCloseEvent * event); //退出程序时的响应
};

#endif // MAINWINDOW_H
