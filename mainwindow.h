#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QSignalMapper>

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
    void slotLoad();
    void slotSave();
    void slotAbout();

    void slotWindows();
    void slotSetActiveSubWindow(QWidget* widget);
    void closeAllWindows();

private:
    // TODO: Зарефакторить по стилю
    QMenu* windowsMenu;
    QMenu* helpMenu;

    QMdiArea* mdiArea;
    Ui::MainWindow *ui;

    QSignalMapper* signalMapper;

};

#endif // MAINWINDOW_H
