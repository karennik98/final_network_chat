#include "ConnectionProperties.h"
#include "ui_ConnectionProperties.h"
#include <QIcon>

ConnectionProperties::ConnectionProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionProperties)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("icon.png"));
}

ConnectionProperties::~ConnectionProperties()
{
    emit properties(ui->hostEdit->text(), ui->portEdit->text().toUInt());
    delete ui;
}
