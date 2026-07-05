#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Engine.h"
#include <QMainWindow>
#include <QListWidgetItem>
#include <QMenu>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_executeButton_clicked();

    void on_tableList_itemDoubleClicked(QListWidgetItem *item);

    void showTableContextMenu(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    Engine engine;

    void refreshTableList();
};
#endif // MAINWINDOW_H
