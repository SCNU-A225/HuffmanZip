#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zip.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    //Line Edit样式（QSS样式表）
    ui->leComAim->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
                                  "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    ui->leComChose->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
                                  "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    ui->leUnAim->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
                                  "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    ui->leUnChose->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
                                  "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    ui->leUnname->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
                                  "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");

    //PushButton 样式
    ui->btnComChose->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnComAim->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnComsure->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnComCancel->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnUnAim->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnUnCancel->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnUnChose->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnUnSure->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                  "QPushButton:hover{background-color:white; color: gray;}"
                                 "QPushButton:pressed{background-color:rgb(70, 200, 50); border-style: inset;}");
    ui->btnUnname->setStyleSheet("QPushButton{background-color:gray;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}");

    //设置Line Edit阴影效果
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *effect4 = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *effect5 = new QGraphicsDropShadowEffect();
    effect1->setOffset(2,2);
    effect2->setOffset(2,2);
    effect3->setOffset(2,2);
    effect4->setOffset(2,2);
    effect5->setOffset(2,2);
    ui->leComAim->setGraphicsEffect(effect1);
    ui->leComChose->setGraphicsEffect(effect2);
    ui->leUnAim->setGraphicsEffect(effect3);
    ui->leUnChose->setGraphicsEffect(effect4);
    ui->leUnname->setGraphicsEffect(effect5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//主页 压缩按钮
void MainWindow::on_btnCmpress_clicked()
{
    //转到压缩页
    ui->stackedWidget->setCurrentIndex(1);
}

//主页 解压按钮
void MainWindow::on_btnUncompress_clicked()
{
    //转到解压页
    ui->stackedWidget->setCurrentIndex(2);
}

//解压页 取消按钮
void MainWindow::on_btnUnCancel_clicked()
{
    //返回主页
    ui->stackedWidget->setCurrentIndex(0);
}

//压缩页 取消按钮
void MainWindow::on_btnComCancel_clicked()
{
    //返回主页
    ui->stackedWidget->setCurrentIndex(0);
}

//压缩页 选择文件按钮
void MainWindow::on_btnComChose_clicked()
{
    //定义文件对话类框
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle("Please Select one file");
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //文本框显示选择的文件路径
    QStringList filenames;
    if(fileDialog->exec())
    {
        filenames = fileDialog->selectedFiles();
    }
    for(auto tmp:filenames)
    {
        ui->leComChose->setText(tmp);
        //qDebug()<<tmp<<endl;
    }
}

//压缩页 压缩到按钮：选择压缩文件放置路径
void MainWindow::on_btnComAim_clicked()
{
//    //定义文件对话类框
//    QFileDialog *fileDialog = new QFileDialog(this);
//    //定义文件对话框标题
//    //fileDialog->setWindowTitle("Please Select filter");
//    //设置默认文件路径
//    //fileDialog->setDirectory(".");
//    //设置视图模式
//    fileDialog->setViewMode(QFileDialog::Detail);
//    //文本框显示选择的文件路径
//    QString filenames;
//    filenames = fileDialog->getExistingDirectory(this,"Please Select Directory","C:");
//    ui->leComAim->setText(filenames);
//    //qDebug()<<tmp<<endl;
<<<<<<< HEAD

//定义文件对话类框
=======
    //定义文件对话类框
>>>>>>> 99fdd2a092498a4ee200e5493de58fe0c7f50787
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle("Please Select one file");
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setNameFilter("None");
    //文本框显示选择的文件路径
    QStringList filenames;
    if(fileDialog->exec())
    {
        filenames = fileDialog->selectedFiles();
    }
<<<<<<< HEAD
    for(auto tmp:filenames)
    {
        ui->leComAim->setText(tmp);
        //qDebug()<<tmp<<endl;
    }
=======
    QString names;
    QString renames="djin";
    for(auto tmp:filenames)
    {
        names.append(tmp);
        //ui->leComAim->setText(tmp);
        //qDebug()<<tmp<<endl;
    }
    int flag=0;
    for(int i=0; i<names.length();i++)
    {
        if(names[i]=='.') flag=i;
    }
    if(flag!=0)
    {
        names = names.remove(flag,names.length()-flag);
    }
    names.append(".hzip");
    if(names.length()==5) ui->leComAim->setText("");
    else ui->leComAim->setText(names);
>>>>>>> 99fdd2a092498a4ee200e5493de58fe0c7f50787
}

//解压页 选择文件按钮
void MainWindow::on_btnUnChose_clicked()
{
    //定义文件对话类框
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle("Please Select one zip file");
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter("All Files(*.hzip)");
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //文本框显示选择的文件路径
    QStringList filenames;
    if(fileDialog->exec())
    {
        filenames = fileDialog->selectedFiles();
    }

    for(auto tmp:filenames)
    {
        ui->leUnChose->setText(tmp);
        //qDebug()<<tmp<<endl;
    }

}

//解压页 解压到按钮
void MainWindow::on_btnUnAim_clicked()
{
    //定义文件对话类框
    QFileDialog *fileDialog = new QFileDialog(this);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //文本框显示选择的文件路径
    QString filenames;
    filenames = fileDialog->getExistingDirectory(this,"Please Select Directory","C:");
    ui->leUnAim->setText(filenames);
    //qDebug()<<tmp<<endl;
}

//压缩页 确定按钮
void MainWindow::on_btnComsure_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//解压页 确定按钮
void MainWindow::on_btnUnSure_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
