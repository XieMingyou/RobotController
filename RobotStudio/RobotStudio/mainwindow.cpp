#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <QDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QFile>
#include <iostream>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->treeWidget, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(clickTreeWidgetItem(QTreeWidgetItem *))); //单击treeWidget时的响应
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(doubleClickRobotItem(QTreeWidgetItem *))); //双击robotItem时编辑
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newRobot()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveRobot()));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copyRobot()));
    ui->actionCopy->setEnabled(false);
    connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(pasteRobot()));
    ui->actionPaste->setEnabled(false);
    connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clearRobot()));
    ui->actionClear->setEnabled(false);
    connect(ui->actionRename, SIGNAL(triggered()), this, SLOT(renameRobot()));
    ui->actionRename->setEnabled(false);
    connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(deleteRobot()));
    ui->actionDelete->setEnabled(false);
    resizeDocks({ui->dockWidget},{210},Qt::Horizontal);//初始化dockWidget_5的大小
    ui->treeWidget->expandAll(); //让treeWidget保持展开
    ui->tabWidget->setCurrentIndex(0); //让tabWidget显示第一个tab
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //让tableWidget可以随窗口大小伸缩
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //初始化两个tableWidget，全部设为""
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    for(int i = 0; i < ui->tableWidget_2->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget_2->columnCount(); j++)
        {
            ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    //查找是否有RobotConfig.xml文件，若没有则新建
    configFileName = ".//RobotConfig.xml";
    QFile configFile(configFileName);
    if(!configFile.exists())
    {
//        configFile.open(QIODevice::ReadWrite | QIODevice::Text); //创建RobotConfig.xml
//        configFile.close();

        TiXmlDeclaration *dec = new TiXmlDeclaration("1.0", "UTF-8", "yes"); //xml文件声明
        doc.LinkEndChild(dec);
        TiXmlComment *comment = new TiXmlComment("机器人配置文件"); //xml文件注释
        doc.LinkEndChild(comment);
        rootElem = new TiXmlElement("Config");
        doc.LinkEndChild(rootElem);
        doc.SaveFile(configFileName.toStdString().c_str());
    }
    else
    {
        //加载机器人配置文件
        doc.LoadFile(configFileName.toStdString().c_str());
        rootElem = doc.RootElement();
        TiXmlElement *robot = nullptr;
        for(robot = rootElem->FirstChildElement(); robot; robot = robot->NextSiblingElement())
        {
            //在treeWidget中插入robotItem，并显示名称和状态信息
            robotName = robot->Value();
            QString available = robot->FirstChildElement()->Attribute("available");
            if(available == "true")
            {
                available = "available";
            }
            else
            {
                available = "";
            }
            QTreeWidgetItem *robotItem = new QTreeWidgetItem(QStringList({robotName, available}));
            ui->treeWidget->topLevelItem(0)->addChild(robotItem);
            numRobot++;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickTreeWidgetItem(QTreeWidgetItem *item)
{
    curItem = item;
    if(curItem->text(0) == "Robot") //点击Robot项时的响应
    {
        //给 Robot项添加菜单
        QMenu *menuRobot = new QMenu(ui->treeWidget);
        QAction *pNewRobot = new QAction("新建");
        menuRobot->addAction(pNewRobot);
        connect(pNewRobot, SIGNAL(triggered()), this, SLOT(newRobot())); //这句一定要在menuRobot->exec(QCursor::pos());之前
        QAction *pPasteRobot = new QAction("粘贴");
        menuRobot->addAction(pPasteRobot);
        //尚未复制机器人实例时，粘贴键为灰色表示无效
        if(robotInstance == nullptr)
        {
            pPasteRobot->setEnabled(false);
            ui->actionPaste->setEnabled(false);
        }
        else
        {
            ui->actionPaste->setEnabled(true);
            connect(pPasteRobot, SIGNAL(triggered()), this, SLOT(pasteRobot()));
        }
        //工具栏的复制键为灰色表示无效
        ui->actionCopy->setEnabled(false);
        menuRobot->exec(QCursor::pos());
        return;
    }
    else if(curItem->text(0) == "IO Device") //点击IO Device项时的响应
    {
        return;
    }
    else if(curItem->parent()->text(0) == "Robot") //点击具体机器人实例时的响应
    {
        ui->actionCopy->setEnabled(true);
        //尚未复制机器人实例时，粘贴键为灰色表示无效
        if(robotInstance == nullptr)
        {
            ui->actionPaste->setEnabled(false);
        }
        else
        {
            ui->actionPaste->setEnabled(true);
        }
        ui->actionClear->setEnabled(true);
        ui->actionRename->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        if(curRobot != 0)
        {
            ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(0, QColor(255,255,255));
            ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(1, QColor(255,255,255));
            saveRobot(); //保存上次选中的机器人实例
        }
        else
        {
            ui->tabWidget->setCurrentIndex(0); //删除后点击某一机器人实例时，默认显示第一个tab
        }
        //判断点击的是哪个机器人实例并显示
        for(int i = 0; i < numRobot; i++)
        {
            if(ui->treeWidget->topLevelItem(0)->child(i)->text(0) == curItem->text(0))
            {
                curRobot = i + 1;
                break;
            }
        }
        curItem->setBackgroundColor(0, QColor(30, 144, 255));
        curItem->setBackgroundColor(1, QColor(30, 144, 255));
        showRobot();
        if(qApp->mouseButtons() == Qt::RightButton) //右击击机器人实例
        {
            //给具体机器人项添加菜单
            QMenu *menuRobotItem = new QMenu(ui->treeWidget);
            QAction *pNewRobot = new QAction("新建");
            menuRobotItem->addAction(pNewRobot);
            connect(pNewRobot, SIGNAL(triggered()), this, SLOT(newRobot()));
            QAction *pSaveRobot = new QAction("保存");
            menuRobotItem->addAction(pSaveRobot);
            connect(pSaveRobot, SIGNAL(triggered()), this, SLOT(saveRobot()));
            QAction *pCopyRobot = new QAction("复制");
            menuRobotItem->addAction(pCopyRobot);
            connect(pCopyRobot, SIGNAL(triggered()), this, SLOT(copyRobot()));
            QAction *pPasteRobot = new QAction("粘贴");
            menuRobotItem->addAction(pPasteRobot);
            connect(pPasteRobot, SIGNAL(triggered()), this, SLOT(pasteRobot()));
            QAction *pClearRobot = new QAction("清空");
            menuRobotItem->addAction(pClearRobot);
            connect(pClearRobot, SIGNAL(triggered()), this, SLOT(clearRobot()));
            QAction *pRenameRobot = new QAction("重命名");
            menuRobotItem->addAction(pRenameRobot);
            connect(pRenameRobot, SIGNAL(triggered()), this, SLOT(renameRobot()));
            QAction *pDeleteRobot = new QAction("删除");
            menuRobotItem->addAction(pDeleteRobot);
            connect(pDeleteRobot, SIGNAL(triggered()), this, SLOT(deleteRobot()));
            menuRobotItem->exec(QCursor::pos());
        }
    }
}

void MainWindow::newRobot()
{
    QDialog* dialog = new QDialog(ui->centralWidget);//新建机器人对话框
    dialog->setWindowTitle("新建机器人");
    QFormLayout form(dialog);
    QString nameLabel("Name");
    QLineEdit *nameEdit = new QLineEdit(dialog);
    form.addRow(nameLabel, nameEdit);
    QString typeLabel("Type");
    QComboBox *typeCombox = new QComboBox(dialog);
    typeCombox->addItem("General Robot(six axis)");
    form.addRow(typeLabel, typeCombox);
    QString baseLabel("Number of base axes");
    QComboBox *baseCombox = new QComboBox(dialog);
    baseCombox->addItem("3");
    form.addRow(baseLabel, baseCombox);
    QString wistLabel("Number of wist axes");
    QComboBox *wistCombox = new QComboBox(dialog);
    wistCombox->addItem("3");
    form.addRow(wistLabel, wistCombox);
    //添加OK和Cancle按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    if(dialog->exec() == QDialog::Accepted)
    {
        robotName = nameEdit->text();
        robotType = typeCombox->currentText();
        baseNum = baseCombox->currentText();
        wristNum = wistCombox->currentText();
        if(!strcmp(robotName.toStdString().c_str(), "") || robotName.toStdString().find(" ") != std::string::npos)
        {
            QMessageBox::warning(ui->centralWidget, "警告提示", "请输入有效的机器人名称。");
            newRobot();
        }
        else
        {          
            int i;
            for(i = 0; i < numRobot; i++)
            {
                if(ui->treeWidget->topLevelItem(0)->child(i)->text((0)) == robotName)
                {
                    QMessageBox::warning(ui->centralWidget, "警告提示", "该机器人名称已存在，请重新命名机器人。");
                    newRobot();
                    break;
                }
            }
            if(i == numRobot) //说明没有重名的情况
            {
                QTreeWidgetItem *newRobot = new QTreeWidgetItem(QStringList({robotName, ""}));
                ui->treeWidget->topLevelItem(0)->addChild(newRobot);
                //还没建有机器人或上一步操作为删除机器人的情况
                if(numRobot == 0 || curRobot == 0)
                {
                   ui->tabWidget->setCurrentIndex(0); //新建第一个机器人时默认显示tab1
                }
                //当前已选中机器人的情况
                if(curRobot != 0)
                {
                    ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(0, QColor(255, 255, 255));
                    ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(1, QColor(255, 255, 255));
                    saveRobot(); //更新当前机器人的配置
                }
                numRobot++;
                ui->treeWidget->topLevelItem(0)->child(numRobot - 1)->setBackgroundColor(0, QColor(30, 144, 255));
                ui->treeWidget->topLevelItem(0)->child(numRobot - 1)->setBackgroundColor(1, QColor(30, 144, 255));
                curRobot = numRobot; //将当前机器人设为新建的机器人
                clearRobot(); //清空stackWidget中的配置数据，并保存为""
            }
        }
    }
    ui->actionCopy->setEnabled(true);
    ui->actionClear->setEnabled(true);
    ui->actionRename->setEnabled(true);
    ui->actionDelete->setEnabled(true);
}

bool MainWindow::getElementByName(TiXmlElement *rootElem, const char *destElemName, TiXmlElement **destElem)
{
    //如何等于根节点则返回
    if(0 == strcmp(destElemName, rootElem->Value()))
    {
        *destElem = rootElem;
        return true;
    }

    TiXmlElement *pElem = nullptr;
    for(pElem = rootElem->FirstChildElement(); pElem; pElem = pElem->NextSiblingElement())
    {
        // 递归查找子元素返回元素指针
        if(0 != strcmp(destElemName, pElem->Value()))
        {
            getElementByName(pElem, destElemName, destElem);
        }
        else
        {
            *destElem = pElem;
            return true;
        }
    }
    return false;
}

void MainWindow::setAxisAttribute(TiXmlElement *pElem, QTableWidget *tableWidget, int column)
{
    for(int i = 0; i < tableWidget->rowCount(); i++)
    {
        QString attributeName = "axis" + QString::number(i + 1);
        pElem->SetAttribute(attributeName.toStdString().c_str(), tableWidget->item(i, column)->text().toStdString().c_str());
    }
}

void MainWindow::getAxisAttribute(TiXmlElement *pElem, QTableWidget *tableWidget, int column)
{
    for(int i = 0; i < tableWidget->rowCount(); i++)
    {
        QString attributeName = "axis" + QString::number(i + 1);
        tableWidget->item(i, column)->setText(pElem->Attribute(attributeName.toStdString().c_str()));
    }
}

void MainWindow::saveRobot()
{
//    有两种实现方法：（1）每次保存时都新建一个TiXmlElement的robot，并替换原来的robot，这种方法new的调用次数较多，占较大的运行内存，注释部分即为该方法的实现；
//                 （2）新建一个机器人实例时才新建一个TiXmlElement的robot，如需更新，只需改变其中的属性值等参数，目前采用这种方法；

    //只有当curRobot不为0时才保存
    if(curRobot != 0)
    {

//        TiXmlElement *oldRobot = nullptr; //以前已建的机器人实例
//        TiXmlElement *newRobot = nullptr; //新建或更新的机器人实例
//        //保存复制的机器人实例的名字以便之后的更新
//        QString robotInstanceName;
//        bool hasCopy = false;
//        if(robotInstance != nullptr)
//        {
//            robotInstanceName = robotInstance->Value();
//            hasCopy = true;
//        }


        robotName = ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->text(0);

//        if(!getElementByName(rootElem, robotName.toStdString().c_str(), &oldRobot)) //true时表示新建机器人实例，false时表示已建机器人的配置更新
//        {
//            newRobot = new TiXmlElement(robotName.toStdString().c_str());
//            TiXmlComment *comment1 = new TiXmlComment("机器人基本信息");
//            newRobot->LinkEndChild(comment1);
//            TiXmlElement *baseInfo = new TiXmlElement("BaseInfo");
//            baseInfo->SetAttribute("robotType", robotType.toStdString().c_str());
//            baseInfo->SetAttribute("baseNum", baseNum.toStdString().c_str());
//            baseInfo->SetAttribute("wristNum", wristNum.toStdString().c_str());
//            baseInfo->SetAttribute("available", "");
//            newRobot->LinkEndChild(baseInfo);
//        }
//        else
//        {
//            newRobot = new TiXmlElement(oldRobot->Value());
//            TiXmlComment *comment1 = new TiXmlComment("机器人基本信息");
//            newRobot->LinkEndChild(comment1);
//            TiXmlElement *baseInfo = new TiXmlElement("BaseInfo");
//            baseInfo->SetAttribute("robotType", oldRobot->FirstChildElement()->Attribute("robotType"));
//            baseInfo->SetAttribute("baseNum", oldRobot->FirstChildElement()->Attribute("baseNum"));
//            baseInfo->SetAttribute("wristNum", oldRobot->FirstChildElement()->Attribute("wristNum"));
//            baseInfo->SetAttribute("available", oldRobot->FirstChildElement()->Attribute("available"));
//            newRobot->LinkEndChild(baseInfo);
//        }
//        TiXmlComment *comment2 = new TiXmlComment("机器人D-H参数");
//        newRobot->LinkEndChild(comment2);
//        TiXmlElement *DH = new TiXmlElement("DH");
//        TiXmlElement *alpha = new TiXmlElement("alpha");
//        setAxisAttribute(alpha, ui->tableWidget, 0);
//        DH->LinkEndChild(alpha);
//        TiXmlElement *a = new TiXmlElement("a");
//        setAxisAttribute(a, ui->tableWidget, 1);
//        DH->LinkEndChild(a);
//        TiXmlElement *d = new TiXmlElement("d");
//        setAxisAttribute(d, ui->tableWidget, 2);
//        DH->LinkEndChild(d);
//        TiXmlElement *offset1 = new TiXmlElement("offset1");
//        setAxisAttribute(offset1, ui->tableWidget, 3);
//        DH->LinkEndChild(offset1);
//        newRobot->LinkEndChild(DH);
//        TiXmlComment *comment3 = new TiXmlComment("机器人各轴伺服参数");
//        newRobot->LinkEndChild(comment3);
//        TiXmlElement *servo = new TiXmlElement("Servo");
//        TiXmlElement *maxPos = new TiXmlElement("maxPos");
//        setAxisAttribute(maxPos, ui->tableWidget_2, 0);
//        servo->LinkEndChild(maxPos);
//        TiXmlElement *minPos = new TiXmlElement("minPos");
//        setAxisAttribute(minPos, ui->tableWidget_2, 1);
//        servo->LinkEndChild(minPos);
//        TiXmlElement *maxVel = new TiXmlElement("maxVel");
//        setAxisAttribute(maxVel, ui->tableWidget_2, 2);
//        servo->LinkEndChild(maxVel);
//        TiXmlElement *maxAcc = new TiXmlElement("maxAcc");
//        setAxisAttribute(maxAcc, ui->tableWidget_2, 3);
//        servo->LinkEndChild(maxAcc);
//        TiXmlElement *maxDec = new TiXmlElement("maxDec");
//        setAxisAttribute(maxDec, ui->tableWidget_2, 4);
//        servo->LinkEndChild(maxDec);
//        TiXmlElement *maxJerk = new TiXmlElement("maxJerk");
//        setAxisAttribute(maxJerk, ui->tableWidget_2, 5);
//        servo->LinkEndChild(maxJerk);
//        TiXmlElement *offset2 = new TiXmlElement("offset2");
//        setAxisAttribute(offset2, ui->tableWidget_2, 6);
//        servo->LinkEndChild(offset2);
//        TiXmlElement *direction = new TiXmlElement("direction");
//        setAxisAttribute(direction, ui->tableWidget_2, 7);
//        servo->LinkEndChild(direction);
//        TiXmlElement *ratio = new TiXmlElement("ratio");
//        setAxisAttribute(ratio, ui->tableWidget_2, 8);
//        servo->LinkEndChild(ratio);
//        TiXmlElement *encoder = new TiXmlElement("encoder");
//        setAxisAttribute(encoder, ui->tableWidget_2, 9);
//        servo->LinkEndChild(encoder);
//        TiXmlElement *coupling = new TiXmlElement("coupling");
//        coupling->SetAttribute("axis4ToAxis5", ui->lineEdit->text().toStdString().c_str());
//        coupling->SetAttribute("axis4ToAxis6", ui->lineEdit_2->text().toStdString().c_str());
//        coupling->SetAttribute("axis5ToAxis6", ui->lineEdit_3->text().toStdString().c_str());
//        servo->LinkEndChild(coupling);
//        newRobot->LinkEndChild(servo);
//        TiXmlComment *comment4 = new TiXmlComment("机器人运动参数");
//        newRobot->LinkEndChild(comment4);
//        TiXmlElement *motion = new TiXmlElement("Motion");
//        TiXmlElement *dynamic = new TiXmlElement("dynamic");
//        dynamic->SetAttribute("velAxis", ui->lineEdit_4->text().toStdString().c_str());
//        dynamic->SetAttribute("accAxis", ui->lineEdit_5->text().toStdString().c_str());
//        dynamic->SetAttribute("jerkAxis", ui->lineEdit_6->text().toStdString().c_str());
//        dynamic->SetAttribute("velPath", ui->lineEdit_7->text().toStdString().c_str());
//        dynamic->SetAttribute("accPath", ui->lineEdit_8->text().toStdString().c_str());
//        dynamic->SetAttribute("jerkPath", ui->lineEdit_9->text().toStdString().c_str());
//        dynamic->SetAttribute("velOri", ui->lineEdit_10->text().toStdString().c_str());
//        dynamic->SetAttribute("accOri", ui->lineEdit_11->text().toStdString().c_str());
//        dynamic->SetAttribute("jerkOri", ui->lineEdit_12->text().toStdString().c_str());
//        motion->LinkEndChild(dynamic);
//        TiXmlElement *jogSpeed = new TiXmlElement("jogSpeed");
//        jogSpeed->SetAttribute("velAxis", ui->lineEdit_25->text().toStdString().c_str());
//        jogSpeed->SetAttribute("accAxis", ui->lineEdit_26->text().toStdString().c_str());
//        jogSpeed->SetAttribute("jerkAxis", ui->lineEdit_27->text().toStdString().c_str());
//        jogSpeed->SetAttribute("velPath", ui->lineEdit_28->text().toStdString().c_str());
//        jogSpeed->SetAttribute("accPath", ui->lineEdit_29->text().toStdString().c_str());
//        jogSpeed->SetAttribute("jerkPath", ui->lineEdit_30->text().toStdString().c_str());
//        jogSpeed->SetAttribute("velOri", ui->lineEdit_31->text().toStdString().c_str());
//        jogSpeed->SetAttribute("accOri", ui->lineEdit_32->text().toStdString().c_str());
//        jogSpeed->SetAttribute("jerkOri", ui->lineEdit_33->text().toStdString().c_str());
//        motion->LinkEndChild(jogSpeed);
//        newRobot->LinkEndChild(motion);
//        TiXmlComment *comment5 = new TiXmlComment("基坐标系和工具坐标系");
//        newRobot->LinkEndChild(comment5);
//        TiXmlElement *coordinate = new TiXmlElement("Coordinate");
//        TiXmlElement *base = new TiXmlElement("base");
//        base->SetAttribute("x", ui->lineEdit_13->text().toStdString().c_str());
//        base->SetAttribute("y", ui->lineEdit_14->text().toStdString().c_str());
//        base->SetAttribute("z", ui->lineEdit_15->text().toStdString().c_str());
//        base->SetAttribute("a", ui->lineEdit_16->text().toStdString().c_str());
//        base->SetAttribute("b", ui->lineEdit_17->text().toStdString().c_str());
//        base->SetAttribute("c", ui->lineEdit_18->text().toStdString().c_str());
//        coordinate->LinkEndChild(base);
//        TiXmlElement *tool = new TiXmlElement("tool");
//        tool->SetAttribute("x", ui->lineEdit_19->text().toStdString().c_str());
//        tool->SetAttribute("y", ui->lineEdit_20->text().toStdString().c_str());
//        tool->SetAttribute("z", ui->lineEdit_21->text().toStdString().c_str());
//        tool->SetAttribute("a", ui->lineEdit_22->text().toStdString().c_str());
//        tool->SetAttribute("b", ui->lineEdit_23->text().toStdString().c_str());
//        tool->SetAttribute("c", ui->lineEdit_24->text().toStdString().c_str());
//        coordinate->LinkEndChild(tool);
//        newRobot->LinkEndChild(coordinate);
//        if(oldRobot == nullptr) //true时表示新建机器人实例，false时表示已建机器人的配置更新
//        {
//           rootElem->LinkEndChild(newRobot);
//        }
//        else
//        {
//            rootElem->ReplaceChild(oldRobot, *newRobot);
//        }
//        //更新robotInstance
//        if(hasCopy)
//        {
//            getElementByName(rootElem, robotInstanceName.toStdString().c_str(), &robotInstance);
//        }


        TiXmlElement *robot = nullptr;
        if(!getElementByName(rootElem, robotName.toStdString().c_str(), &robot)) //true时表示新建机器人实例，false时表示已建机器人的配置更新
        {
            robot = new TiXmlElement(robotName.toStdString().c_str());
            TiXmlComment *comment1 = new TiXmlComment("机器人基本信息");
            robot->LinkEndChild(comment1);
            TiXmlElement *baseInfo = new TiXmlElement("BaseInfo");
            baseInfo->SetAttribute("robotType", robotType.toStdString().c_str());
            baseInfo->SetAttribute("baseNum", baseNum.toStdString().c_str());
            baseInfo->SetAttribute("wristNum", wristNum.toStdString().c_str());
            baseInfo->SetAttribute("available", "");
            robot->LinkEndChild(baseInfo);
            TiXmlComment *comment2 = new TiXmlComment("机器人D-H参数");
            robot->LinkEndChild(comment2);
            TiXmlElement *DH = new TiXmlElement("DH");
            TiXmlElement *alpha = new TiXmlElement("alpha");
            setAxisAttribute(alpha, ui->tableWidget, 0);
            DH->LinkEndChild(alpha);
            TiXmlElement *a = new TiXmlElement("a");
            setAxisAttribute(a, ui->tableWidget, 1);
            DH->LinkEndChild(a);
            TiXmlElement *d = new TiXmlElement("d");
            setAxisAttribute(d, ui->tableWidget, 2);
            DH->LinkEndChild(d);
            TiXmlElement *offset1 = new TiXmlElement("offset1");
            setAxisAttribute(offset1, ui->tableWidget, 3);
            DH->LinkEndChild(offset1);
            robot->LinkEndChild(DH);
            TiXmlComment *comment3 = new TiXmlComment("机器人各轴伺服参数");
            robot->LinkEndChild(comment3);
            TiXmlElement *servo = new TiXmlElement("Servo");
            TiXmlElement *maxPos = new TiXmlElement("maxPos");
            setAxisAttribute(maxPos, ui->tableWidget_2, 0);
            servo->LinkEndChild(maxPos);
            TiXmlElement *minPos = new TiXmlElement("minPos");
            setAxisAttribute(minPos, ui->tableWidget_2, 1);
            servo->LinkEndChild(minPos);
            TiXmlElement *maxVel = new TiXmlElement("maxVel");
            setAxisAttribute(maxVel, ui->tableWidget_2, 2);
            servo->LinkEndChild(maxVel);
            TiXmlElement *maxAcc = new TiXmlElement("maxAcc");
            setAxisAttribute(maxAcc, ui->tableWidget_2, 3);
            servo->LinkEndChild(maxAcc);
            TiXmlElement *maxDec = new TiXmlElement("maxDec");
            setAxisAttribute(maxDec, ui->tableWidget_2, 4);
            servo->LinkEndChild(maxDec);
            TiXmlElement *maxJerk = new TiXmlElement("maxJerk");
            setAxisAttribute(maxJerk, ui->tableWidget_2, 5);
            servo->LinkEndChild(maxJerk);
            TiXmlElement *offset2 = new TiXmlElement("offset2");
            setAxisAttribute(offset2, ui->tableWidget_2, 6);
            servo->LinkEndChild(offset2);
            TiXmlElement *direction = new TiXmlElement("direction");
            setAxisAttribute(direction, ui->tableWidget_2, 7);
            servo->LinkEndChild(direction);
            TiXmlElement *ratio = new TiXmlElement("ratio");
            setAxisAttribute(ratio, ui->tableWidget_2, 8);
            servo->LinkEndChild(ratio);
            TiXmlElement *encoder = new TiXmlElement("encoder");
            setAxisAttribute(encoder, ui->tableWidget_2, 9);
            servo->LinkEndChild(encoder);
            TiXmlElement *coupling = new TiXmlElement("coupling");
            coupling->SetAttribute("axis4ToAxis5", ui->lineEdit->text().toStdString().c_str());
            coupling->SetAttribute("axis4ToAxis6", ui->lineEdit_2->text().toStdString().c_str());
            coupling->SetAttribute("axis5ToAxis6", ui->lineEdit_3->text().toStdString().c_str());
            servo->LinkEndChild(coupling);
            robot->LinkEndChild(servo);
            TiXmlComment *comment4 = new TiXmlComment("机器人运动参数");
            robot->LinkEndChild(comment4);
            TiXmlElement *motion = new TiXmlElement("Motion");
            TiXmlElement *dynamic = new TiXmlElement("dynamic");
            dynamic->SetAttribute("velAxis", ui->lineEdit_4->text().toStdString().c_str());
            dynamic->SetAttribute("accAxis", ui->lineEdit_5->text().toStdString().c_str());
            dynamic->SetAttribute("jerkAxis", ui->lineEdit_6->text().toStdString().c_str());
            dynamic->SetAttribute("velPath", ui->lineEdit_7->text().toStdString().c_str());
            dynamic->SetAttribute("accPath", ui->lineEdit_8->text().toStdString().c_str());
            dynamic->SetAttribute("jerkPath", ui->lineEdit_9->text().toStdString().c_str());
            dynamic->SetAttribute("velOri", ui->lineEdit_10->text().toStdString().c_str());
            dynamic->SetAttribute("accOri", ui->lineEdit_11->text().toStdString().c_str());
            dynamic->SetAttribute("jerkOri", ui->lineEdit_12->text().toStdString().c_str());
            motion->LinkEndChild(dynamic);
            TiXmlElement *jogSpeed = new TiXmlElement("jogSpeed");
            jogSpeed->SetAttribute("velAxis", ui->lineEdit_25->text().toStdString().c_str());
            jogSpeed->SetAttribute("accAxis", ui->lineEdit_26->text().toStdString().c_str());
            jogSpeed->SetAttribute("jerkAxis", ui->lineEdit_27->text().toStdString().c_str());
            jogSpeed->SetAttribute("velPath", ui->lineEdit_28->text().toStdString().c_str());
            jogSpeed->SetAttribute("accPath", ui->lineEdit_29->text().toStdString().c_str());
            jogSpeed->SetAttribute("jerkPath", ui->lineEdit_30->text().toStdString().c_str());
            jogSpeed->SetAttribute("velOri", ui->lineEdit_31->text().toStdString().c_str());
            jogSpeed->SetAttribute("accOri", ui->lineEdit_32->text().toStdString().c_str());
            jogSpeed->SetAttribute("jerkOri", ui->lineEdit_33->text().toStdString().c_str());
            motion->LinkEndChild(jogSpeed);
            robot->LinkEndChild(motion);
            TiXmlComment *comment5 = new TiXmlComment("基坐标系和工具坐标系");
            robot->LinkEndChild(comment5);
            TiXmlElement *coordinate = new TiXmlElement("Coordinate");
            TiXmlElement *base = new TiXmlElement("base");
            base->SetAttribute("x", ui->lineEdit_13->text().toStdString().c_str());
            base->SetAttribute("y", ui->lineEdit_14->text().toStdString().c_str());
            base->SetAttribute("z", ui->lineEdit_15->text().toStdString().c_str());
            base->SetAttribute("a", ui->lineEdit_16->text().toStdString().c_str());
            base->SetAttribute("b", ui->lineEdit_17->text().toStdString().c_str());
            base->SetAttribute("c", ui->lineEdit_18->text().toStdString().c_str());
            coordinate->LinkEndChild(base);
            TiXmlElement *tool = new TiXmlElement("tool");
            tool->SetAttribute("x", ui->lineEdit_19->text().toStdString().c_str());
            tool->SetAttribute("y", ui->lineEdit_20->text().toStdString().c_str());
            tool->SetAttribute("z", ui->lineEdit_21->text().toStdString().c_str());
            tool->SetAttribute("a", ui->lineEdit_22->text().toStdString().c_str());
            tool->SetAttribute("b", ui->lineEdit_23->text().toStdString().c_str());
            tool->SetAttribute("c", ui->lineEdit_24->text().toStdString().c_str());
            coordinate->LinkEndChild(tool);
            robot->LinkEndChild(coordinate);
            rootElem->LinkEndChild(robot);
        }
        else
        {
            //更新选中的机器人实例的xml配置数据
            TiXmlElement *DH = nullptr;
            getElementByName(robot, "DH", &DH);
            TiXmlElement *alpha = nullptr;
            getElementByName(DH, "alpha", &alpha);
            setAxisAttribute(alpha, ui->tableWidget, 0);
            TiXmlElement *a = nullptr;
            getElementByName(DH, "a", &a);
            setAxisAttribute(a, ui->tableWidget, 1);
            TiXmlElement *d = nullptr;
            getElementByName(DH, "d", &d);
            setAxisAttribute(d, ui->tableWidget, 2);
            TiXmlElement *offset1 = nullptr;
            getElementByName(DH, "offset1", &offset1);
            setAxisAttribute(offset1, ui->tableWidget, 3);
            TiXmlElement *servo = nullptr;
            getElementByName(robot, "Servo", &servo);
            TiXmlElement *maxPos = nullptr;
            getElementByName(servo, "maxPos", &maxPos);
            setAxisAttribute(maxPos, ui->tableWidget_2, 0);
            TiXmlElement *minPos = nullptr;
            getElementByName(servo, "minPos", &minPos);
            setAxisAttribute(minPos, ui->tableWidget_2, 1);
            TiXmlElement *maxVel = nullptr;
            getElementByName(servo, "maxVel", &maxVel);
            setAxisAttribute(maxVel, ui->tableWidget_2, 2);
            TiXmlElement *maxAcc = nullptr;
            getElementByName(servo, "maxAcc", &maxAcc);
            setAxisAttribute(maxAcc, ui->tableWidget_2, 3);
            TiXmlElement *maxDec = nullptr;
            getElementByName(servo, "maxDec", &maxDec);
            setAxisAttribute(maxDec, ui->tableWidget_2, 4);
            TiXmlElement *maxJerk = nullptr;
            getElementByName(servo, "maxJerk", &maxJerk);
            setAxisAttribute(maxJerk, ui->tableWidget_2, 5);
            TiXmlElement *offset2 = nullptr;
            getElementByName(servo, "offset2", &offset2);
            setAxisAttribute(offset2, ui->tableWidget_2, 6);
            TiXmlElement *direction = nullptr;
            getElementByName(servo, "direction", &direction);
            setAxisAttribute(direction, ui->tableWidget_2, 7);
            TiXmlElement *ratio = nullptr;
            getElementByName(servo, "ratio", &ratio);
            setAxisAttribute(ratio, ui->tableWidget_2, 8);
            TiXmlElement *encoder = nullptr;
            getElementByName(servo, "encoder", &encoder);
            setAxisAttribute(encoder, ui->tableWidget_2, 9);
            TiXmlElement *coupling = nullptr;
            getElementByName(servo, "coupling", &coupling);
            coupling->SetAttribute("axis4ToAxis5", ui->lineEdit->text().toStdString().c_str());
            coupling->SetAttribute("axis4ToAxis6", ui->lineEdit_2->text().toStdString().c_str());
            coupling->SetAttribute("axis5ToAxis6", ui->lineEdit_3->text().toStdString().c_str());
            TiXmlElement *motion = nullptr;
            getElementByName(robot, "Motion", &motion);
            TiXmlElement *dynamic = nullptr;
            getElementByName(motion, "dynamic", &dynamic);
            dynamic->SetAttribute("velAxis", ui->lineEdit_4->text().toStdString().c_str());
            dynamic->SetAttribute("accAxis", ui->lineEdit_5->text().toStdString().c_str());
            dynamic->SetAttribute("jerkAxis", ui->lineEdit_6->text().toStdString().c_str());
            dynamic->SetAttribute("velPath", ui->lineEdit_7->text().toStdString().c_str());
            dynamic->SetAttribute("accPath", ui->lineEdit_8->text().toStdString().c_str());
            dynamic->SetAttribute("jerkPath", ui->lineEdit_9->text().toStdString().c_str());
            dynamic->SetAttribute("velOri", ui->lineEdit_10->text().toStdString().c_str());
            dynamic->SetAttribute("accOri", ui->lineEdit_11->text().toStdString().c_str());
            dynamic->SetAttribute("jerkOri", ui->lineEdit_12->text().toStdString().c_str());
            TiXmlElement *jogSpeed = nullptr;
            getElementByName(motion, "jogSpeed", &jogSpeed);
            jogSpeed->SetAttribute("velAxis", ui->lineEdit_25->text().toStdString().c_str());
            jogSpeed->SetAttribute("accAxis", ui->lineEdit_26->text().toStdString().c_str());
            jogSpeed->SetAttribute("jerkAxis", ui->lineEdit_27->text().toStdString().c_str());
            jogSpeed->SetAttribute("velPath", ui->lineEdit_28->text().toStdString().c_str());
            jogSpeed->SetAttribute("accPath", ui->lineEdit_29->text().toStdString().c_str());
            jogSpeed->SetAttribute("jerkPath", ui->lineEdit_30->text().toStdString().c_str());
            jogSpeed->SetAttribute("velOri", ui->lineEdit_31->text().toStdString().c_str());
            jogSpeed->SetAttribute("accOri", ui->lineEdit_32->text().toStdString().c_str());
            jogSpeed->SetAttribute("jerkOri", ui->lineEdit_33->text().toStdString().c_str());
            TiXmlElement *coordinate = nullptr;
            getElementByName(robot, "Coordinate", &coordinate);
            TiXmlElement *base = nullptr;
            getElementByName(coordinate, "base", &base);
            base->SetAttribute("x", ui->lineEdit_13->text().toStdString().c_str());
            base->SetAttribute("y", ui->lineEdit_14->text().toStdString().c_str());
            base->SetAttribute("z", ui->lineEdit_15->text().toStdString().c_str());
            base->SetAttribute("a", ui->lineEdit_16->text().toStdString().c_str());
            base->SetAttribute("b", ui->lineEdit_17->text().toStdString().c_str());
            base->SetAttribute("c", ui->lineEdit_18->text().toStdString().c_str());
            TiXmlElement *tool = nullptr;
            getElementByName(coordinate, "tool", &tool);
            tool->SetAttribute("x", ui->lineEdit_19->text().toStdString().c_str());
            tool->SetAttribute("y", ui->lineEdit_20->text().toStdString().c_str());
            tool->SetAttribute("z", ui->lineEdit_21->text().toStdString().c_str());
            tool->SetAttribute("a", ui->lineEdit_22->text().toStdString().c_str());
            tool->SetAttribute("b", ui->lineEdit_23->text().toStdString().c_str());
            tool->SetAttribute("c", ui->lineEdit_24->text().toStdString().c_str());
        }

        statusCheck();
        doc.SaveFile(configFileName.toStdString().c_str());
    }
}

void MainWindow::showRobot()
{
    robotName = ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->text(0);
    TiXmlElement *robot = nullptr;
    if(getElementByName(rootElem, robotName.toStdString().c_str(), &robot))
    {
        TiXmlElement *DH = nullptr;
        getElementByName(robot, "DH", &DH);
        TiXmlElement *alpha = nullptr;
        getElementByName(DH, "alpha", &alpha);
        getAxisAttribute(alpha, ui->tableWidget, 0);
        TiXmlElement *a = nullptr;
        getElementByName(DH, "a", &a);
        getAxisAttribute(a, ui->tableWidget, 1);
        TiXmlElement *d = nullptr;
        getElementByName(DH, "d", &d);
        getAxisAttribute(d, ui->tableWidget, 2);
        TiXmlElement *offset1 = nullptr;
        getElementByName(DH, "offset1", &offset1);
        getAxisAttribute(offset1, ui->tableWidget, 3);
        TiXmlElement *servo = nullptr;
        getElementByName(robot, "Servo", &servo);
        TiXmlElement *maxPos = nullptr;
        getElementByName(servo, "maxPos", &maxPos);
        getAxisAttribute(maxPos, ui->tableWidget_2, 0);
        TiXmlElement *minPos = nullptr;
        getElementByName(servo, "minPos", &minPos);
        getAxisAttribute(minPos, ui->tableWidget_2, 1);
        TiXmlElement *maxVel = nullptr;
        getElementByName(servo, "maxVel", &maxVel);
        getAxisAttribute(maxVel, ui->tableWidget_2, 2);
        TiXmlElement *maxAcc = nullptr;
        getElementByName(servo, "maxAcc", &maxAcc);
        getAxisAttribute(maxAcc, ui->tableWidget_2, 3);
        TiXmlElement *maxDec = nullptr;
        getElementByName(servo, "maxDec", &maxDec);
        getAxisAttribute(maxDec, ui->tableWidget_2, 4);
        TiXmlElement *maxJerk = nullptr;
        getElementByName(servo, "maxJerk", &maxJerk);
        getAxisAttribute(maxJerk, ui->tableWidget_2, 5);
        TiXmlElement *offset2 = nullptr;
        getElementByName(servo, "offset2", &offset2);
        getAxisAttribute(offset2, ui->tableWidget_2, 6);
        TiXmlElement *direction = nullptr;
        getElementByName(servo, "direction", &direction);
        getAxisAttribute(direction, ui->tableWidget_2, 7);
        TiXmlElement *ratio = nullptr;
        getElementByName(servo, "ratio", &ratio);
        getAxisAttribute(ratio, ui->tableWidget_2, 8);
        TiXmlElement *encoder = nullptr;
        getElementByName(servo, "encoder", &encoder);
        getAxisAttribute(encoder, ui->tableWidget_2, 9);
        TiXmlElement *coupling = nullptr;
        getElementByName(servo, "coupling", &coupling);
        ui->lineEdit->setText(coupling->Attribute("axis4ToAxis5"));
        ui->lineEdit_2->setText(coupling->Attribute("axis4ToAxis6"));
        ui->lineEdit_3->setText(coupling->Attribute("axis5ToAxis6"));
        TiXmlElement *motion = nullptr;
        getElementByName(robot, "Motion", &motion);
        TiXmlElement *dynamic = nullptr;
        getElementByName(motion, "dynamic", &dynamic);
        ui->lineEdit_4->setText(dynamic->Attribute("velAxis"));
        ui->lineEdit_5->setText(dynamic->Attribute("accAxis"));
        ui->lineEdit_6->setText(dynamic->Attribute("jerkAxis"));
        ui->lineEdit_7->setText(dynamic->Attribute("velPath"));
        ui->lineEdit_8->setText(dynamic->Attribute("accPath"));
        ui->lineEdit_9->setText(dynamic->Attribute("jerkPath"));
        ui->lineEdit_10->setText(dynamic->Attribute("velOri"));
        ui->lineEdit_11->setText(dynamic->Attribute("accOri"));
        ui->lineEdit_12->setText(dynamic->Attribute("jerkOri"));
        TiXmlElement *jogSpeed = nullptr;
        getElementByName(motion, "jogSpeed", &jogSpeed);
        ui->lineEdit_25->setText(jogSpeed->Attribute("velAxis"));
        ui->lineEdit_26->setText(jogSpeed->Attribute("accAxis"));
        ui->lineEdit_27->setText(jogSpeed->Attribute("jerkAxis"));
        ui->lineEdit_28->setText(jogSpeed->Attribute("velPath"));
        ui->lineEdit_29->setText(jogSpeed->Attribute("accPath"));
        ui->lineEdit_30->setText(jogSpeed->Attribute("jerkPath"));
        ui->lineEdit_31->setText(jogSpeed->Attribute("velOri"));
        ui->lineEdit_32->setText(jogSpeed->Attribute("accOri"));
        ui->lineEdit_33->setText(jogSpeed->Attribute("jerkOri"));
        TiXmlElement *coordinate = nullptr;
        getElementByName(robot, "Coordinate", &coordinate);
        TiXmlElement *base = nullptr;
        getElementByName(coordinate, "base", &base);
        ui->lineEdit_13->setText(base->Attribute("x"));
        ui->lineEdit_14->setText(base->Attribute("y"));
        ui->lineEdit_15->setText(base->Attribute("z"));
        ui->lineEdit_16->setText(base->Attribute("a"));
        ui->lineEdit_17->setText(base->Attribute("b"));
        ui->lineEdit_18->setText(base->Attribute("c"));
        TiXmlElement *tool = nullptr;
        getElementByName(coordinate, "tool", &tool);
        ui->lineEdit_19->setText(tool->Attribute("x"));
        ui->lineEdit_19->update();
        ui->lineEdit_20->setText(tool->Attribute("y"));
        ui->lineEdit_21->setText(tool->Attribute("z"));
        ui->lineEdit_22->setText(tool->Attribute("a"));
        ui->lineEdit_23->setText(tool->Attribute("b"));
        ui->lineEdit_24->setText(tool->Attribute("c"));
    }
}

void MainWindow::copyRobot()
{
    robotInstance = nullptr;
    robotName = ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->text(0);
    getElementByName(rootElem, robotName.toStdString().c_str(), &robotInstance);
    ui->actionPaste->setEnabled(true);
}

void MainWindow::pasteRobot()
{
    if(robotInstance == nullptr)
    {
        return;
    }
    TiXmlElement *robot = new TiXmlElement(*robotInstance);

    //设置粘贴机器人实例后的名称默认命名的规则
    int i = 1;
    QString pasteRobotName; //粘贴后的机器人实例的名称
    for(int j = 0; j < numRobot; j++)
    {
        robotName = ui->treeWidget->topLevelItem(0)->child(j)->text(0);
        pasteRobotName =  QString(robotInstance->Value()) + "_" + QString::fromStdString(to_string(i));
        if(!strcmp(robotName.toStdString().c_str(), pasteRobotName.toStdString().c_str()))
        {
            i++;
            j = -1; //重新返回检查
        }
    }
    robotName = QString(robotInstance->Value()) + "_" + QString::fromStdString(to_string(i));
    robot->SetValue(robotName.toStdString().c_str()); //设置机器人名称

    //显示粘贴后的机器人实例的状态
    QTreeWidgetItem *robotItem;
    if(!strcmp(robot->FirstChildElement()->Attribute("available"), "true"))
    {
        robotItem = new QTreeWidgetItem(QStringList({robot->Value(), "available"}));
    }
    else
    {
        robotItem = new QTreeWidgetItem(QStringList({robot->Value(), ""}));
    }

    ui->treeWidget->topLevelItem(0)->insertChild(curRobot, robotItem); //注意此时curRobot不用加1在后面插入，否则在前面插入

    //在当前的机器人实例后插入粘贴的机器人实例
    TiXmlElement *currentRobot = nullptr;
    robotName = ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->text(0);
    getElementByName(rootElem, robotName.toStdString().c_str(), &currentRobot);
    rootElem->InsertAfterChild(currentRobot, *robot);

    //设置当前机器人高亮
    ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(0, QColor(255,255,255));
    ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(1, QColor(255,255,255));
    curRobot++;
    numRobot++;
    ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(0, QColor(30, 144, 255));
    ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setBackgroundColor(1, QColor(30, 144, 255));

    //显示粘贴后的机器人实例的配置数据
    showRobot();
}

void MainWindow::clearRobot()
{
    //清空两个tableWidget中的内容
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    for(int i = 0; i < ui->tableWidget_2->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget_2->columnCount(); j++)
        {
            ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(""));
        }
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_17->clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_19->clear();
    ui->lineEdit_20->clear();
    ui->lineEdit_21->clear();
    ui->lineEdit_22->clear();
    ui->lineEdit_23->clear();
    ui->lineEdit_24->clear();
    ui->lineEdit_25->clear();
    ui->lineEdit_26->clear();
    ui->lineEdit_27->clear();
    ui->lineEdit_28->clear();
    ui->lineEdit_29->clear();
    ui->lineEdit_30->clear();
    ui->lineEdit_31->clear();
    ui->lineEdit_32->clear();
    ui->lineEdit_33->clear();
}

void MainWindow::renameRobot()
{
    QLineEdit *rename = new QLineEdit(ui->treeWidget);
    oldName = curItem->text(0);
    rename->setText(oldName);
    connect(rename, SIGNAL(editingFinished()), this, SLOT(finishEdit()));
    ui->treeWidget->setItemWidget(curItem, 0, rename);
}

void MainWindow::deleteRobot()
{
    clearRobot();
    TiXmlElement *robot = nullptr;

    robotName = ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->text(0);
    ui->treeWidget->topLevelItem(0)->takeChild(curRobot - 1);
    getElementByName(rootElem, robotName.toStdString().c_str(), &robot);
    if(robotInstance != nullptr && robotInstance == robot) //此时删除的机器人实例正好是复制的机器人实例
    {
        robotInstance = nullptr;
    }

    rootElem->RemoveChild(robot);
    numRobot--;
    curRobot = 0;
    doc.SaveFile(configFileName.toStdString().c_str());
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionClear->setEnabled(false);
    ui->actionRename->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionDelete->setEnabled(false);
}

//判断一个字符串是否为double型
bool isDouble(const string str)
{
    if(str == "")
    {
        return false;
    }
    char* p = nullptr;
    strtod(str.c_str(), &p);
    return *p == '\0';
}

void MainWindow::statusCheck()
{
    //任一输入项不为double，则设机器人的available属性为false
    bool available = true;
    TiXmlElement *robot = nullptr;
    robotName = ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->text(0);
    getElementByName(rootElem, robotName.toStdString().c_str(), &robot);
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            if(!isDouble(ui->tableWidget->item(i, j)->text().toStdString()))
            {
                available = false;
                break;
            }
        }
    }
    if(available)
    {
        for(int i = 0; i < ui->tableWidget_2->rowCount(); i++)
        {
            for(int j = 0; j < ui->tableWidget_2->columnCount(); j++)
            {
                if(!isDouble(ui->tableWidget_2->item(i, j)->text().toStdString()))
                {
                    available = false;
                    break;
                }
            }
        }
    }
    if(available && isDouble(ui->lineEdit->text().toStdString()) && isDouble(ui->lineEdit_2->text().toStdString()) \
            && isDouble(ui->lineEdit_3->text().toStdString()) && isDouble(ui->lineEdit_4->text().toStdString()) \
            && isDouble(ui->lineEdit_5->text().toStdString()) && isDouble(ui->lineEdit_6->text().toStdString()) \
            && isDouble(ui->lineEdit_7->text().toStdString()) && isDouble(ui->lineEdit_8->text().toStdString()) \
            && isDouble(ui->lineEdit_9->text().toStdString()) && isDouble(ui->lineEdit_10->text().toStdString()) \
            && isDouble(ui->lineEdit_11->text().toStdString()) && isDouble(ui->lineEdit_12->text().toStdString()) \
            && isDouble(ui->lineEdit_13->text().toStdString()) && isDouble(ui->lineEdit_14->text().toStdString()) \
            && isDouble(ui->lineEdit_15->text().toStdString()) && isDouble(ui->lineEdit_16->text().toStdString()) \
            && isDouble(ui->lineEdit_17->text().toStdString()) && isDouble(ui->lineEdit_18->text().toStdString()) \
            && isDouble(ui->lineEdit_19->text().toStdString()) && isDouble(ui->lineEdit_20->text().toStdString()) \
            && isDouble(ui->lineEdit_21->text().toStdString()) && isDouble(ui->lineEdit_22->text().toStdString()) \
            && isDouble(ui->lineEdit_23->text().toStdString()) && isDouble(ui->lineEdit_24->text().toStdString()) \
            && isDouble(ui->lineEdit_25->text().toStdString()) && isDouble(ui->lineEdit_26->text().toStdString()) \
            && isDouble(ui->lineEdit_27->text().toStdString()) && isDouble(ui->lineEdit_28->text().toStdString()) \
            && isDouble(ui->lineEdit_29->text().toStdString()) && isDouble(ui->lineEdit_30->text().toStdString()) \
            && isDouble(ui->lineEdit_31->text().toStdString()) && isDouble(ui->lineEdit_32->text().toStdString()) \
            && isDouble(ui->lineEdit_33->text().toStdString()))
    {

        ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setText(1, "available");
        robot->FirstChildElement()->SetAttribute("available", "true");
    }
    else
    {
        ui->treeWidget->topLevelItem(0)->child(curRobot - 1)->setText(1, "");
        robot->FirstChildElement()->SetAttribute("available", "false");
    }
}

void MainWindow::closeEvent( QCloseEvent * event)
{
    saveRobot();
}

void MainWindow::doubleClickRobotItem(QTreeWidgetItem *item) {
    curItem = nullptr;
    if(item->text(0) == "Robot") //点击IO Device项时的响应
    {
        return;
    }
    else if(item->text(0) == "IO Device") //点击IO Device项时的响应
    {
        return;
    }
    else if(item->parent()->text(0) == "Robot")
    {
        curItem = item;
        renameRobot();
    }
}

void MainWindow::finishEdit() {
    if(curItem != nullptr)
    {
        QLineEdit *rename = qobject_cast<QLineEdit *>(ui->treeWidget->itemWidget(curItem, 0));
        if(!rename)
        {
            return;
        }
        QString newName = rename->text();
        QTreeWidgetItemIterator it(ui->treeWidget);
        while (*it)
        {
            if((*it)->text(0) == "Robot")
            {
                int i;
                for(i = 0; i < numRobot; i++)
                {
                    if((*it)->child(i)->text((0)) == newName && (*it)->child(i) != curItem)
                    {
                        QMessageBox::warning(ui->centralWidget, "警告提示", "该机器人名称已存在，请重新命名机器人。");
                        newName = curItem->text(0);
                        break;
                    }
                }
                break;
            }
            it++;
        }
        ui->treeWidget->removeItemWidget(curItem, 0);
        curItem->setText(0, newName);
        //xml文件保存新名称
        TiXmlElement *robot = nullptr;
        getElementByName(rootElem, oldName.toStdString().c_str(), &robot);
        robot->SetValue(newName.toStdString().c_str());
    }
}
