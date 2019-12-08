#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QFileInfo>
#include <QKeyEvent>





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    static bool Superadmin;
    static bool Is_Admin;



    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");

        //notes leave for ayako
        //QString homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
        // QString databaseFile = QStandardPaths::displayName(QStandardPaths::DocumentsLocation) + "/GitHub/CS1C_Project_2/Project2/database.db" ;


        QString databaseFile = QStandardPaths::locate(QStandardPaths::DocumentsLocation,QString("/GitHub/CS1C_Project_2/Project2/database.db"))  ;
        mydb.setDatabaseName(databaseFile);

        if (!mydb.open())
        {
            qDebug() << ("Failed to open the database");
            return false;
        }
        else
        {
            qDebug() << ("Database Connected...");
            return true;
        }
    }

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//public slots:
//    void buttonLogin();

private slots:
    void on_buttonCreate_clicked();
//    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushClear_clicked();

    void on_pushLogin_clicked();

    void on_checkPassword_stateChanged();

protected:
        void keyPressEvent(QKeyEvent* pe);

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
