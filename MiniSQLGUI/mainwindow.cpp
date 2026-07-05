#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Engine.h"
#include <QScrollBar>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableList->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableList,
            &QListWidget::customContextMenuRequested,
            this,
            &MainWindow::showTableContextMenu);
    ui->queryInput->installEventFilter(this);
    //Engine e;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_executeButton_clicked()
{
    QString query = ui->queryInput->toPlainText();

    if(query.trimmed().isEmpty())
        return;
    string result = engine.execute(query.toStdString());

    QString oldOutput = ui->outputBox->toPlainText();

    oldOutput += "> " + query + "\n";
    oldOutput += QString::fromStdString(result) + "\n\n";

    ui->outputBox->setPlainText(oldOutput);

    ui->outputBox->verticalScrollBar()->setValue(ui->outputBox->verticalScrollBar()->maximum());

    ui->queryInput->clear();

    refreshTableList();
}
void MainWindow::refreshTableList()
{
    ui->tableList->clear();

    vector<string> tableNames = engine.getTableNames();

    for(const auto &name : tableNames)
    {
        ui->tableList->addItem(QString::fromStdString(name));
    }
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        qDebug() << obj;
    }

    return QMainWindow::eventFilter(obj, event);
}
void MainWindow::on_tableList_itemDoubleClicked(QListWidgetItem *item)
{
    QString tableName = item->text();

    std::string result = engine.execute(
        "SELECT * FROM " + tableName.toStdString());

    ui->outputBox->appendPlainText("> SELECT * FROM " + tableName);
    ui->outputBox->appendPlainText(QString::fromStdString(result));
    ui->outputBox->appendPlainText("");
}
void MainWindow::showTableContextMenu(const QPoint &pos)
{
    QListWidgetItem *item = ui->tableList->itemAt(pos);

    if(item == nullptr)
        return;

    QMenu menu(this);

    QAction *deleteAction = menu.addAction("Delete Table");

    QAction *selectedAction = menu.exec(ui->tableList->mapToGlobal(pos));

    if(selectedAction == deleteAction)
    {
        QString tableName = item->text();

        QString result = QString::fromStdString(
            engine.dropTable(tableName.toStdString()));

        ui->outputBox->appendPlainText("> DROP TABLE " + tableName);
        ui->outputBox->appendPlainText(result);
        ui->outputBox->appendPlainText("");

        refreshTableList();
    }
}