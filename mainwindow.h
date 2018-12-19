#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QDialog>
#include <QProgressBar>
#include <QProgressDialog>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnCmpress_clicked();

    void on_btnUncompress_clicked();

    void on_btnUnCancel_clicked();

    void on_btnComCancel_clicked();

    void on_btnComChose_clicked();

    void on_btnComAim_clicked();

    void on_btnUnChose_clicked();

    void on_btnUnAim_clicked();

    void on_btnComsure_clicked();

    void on_btnUnSure_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
