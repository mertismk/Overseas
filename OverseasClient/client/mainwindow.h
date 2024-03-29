#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtNetwork/QTcpSocket>
#include <QObject>
#include <QString>
#include "chatclient.h"
#include "authorizationform.h"
#include "chat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QString updateResponse();

    void on_Exit_pushButton_clicked();

    void on_Chat1_pushButton_clicked();

    void on_Chat2_pushButton_clicked();

    void on_Chat3_pushButton_clicked();

    void on_Chat4_pushButton_clicked();

    void on_Chat5_pushButton_clicked();

    void on_NickEdit_pushButton_clicked();

    void on_Search_pushButton_clicked();

    void on_dialog_pushButton_clicked();

    void on_Search_lineEdit_returnPressed();

public slots:
    void updateField(const QString& newData);
    void eventInMainWindow(QString username, QString dialog_username);

private:
    Ui::MainWindow *ui;
    AuthorizationForm *ui_auth;
    Chat *ui_chat;
    ChatClient *chatClient;
};

#endif // MAINWINDOW_H
