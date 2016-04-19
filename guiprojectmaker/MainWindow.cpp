#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QtWidgets/qfiledialog.h>
#include <QtCore/qregexp.h>
#include <QtCore/qcoreapplication.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qfile.h>
#include <memory>
#include "../projectMaker/ArgvPack.hpp"
extern int run(ArgvPack pack);

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    {
        QString pro_funpath_=ui->pro_fullpath->text();
        if (pro_funpath_.isEmpty()) {
            pro_funpath_=qApp->applicationDirPath()+
                "/../../../OpenCVTestNew.pro";
            QFileInfo info_(pro_funpath_);
            if (info_.exists()) {
                pro_funpath_=QDir::cleanPath(pro_funpath_);
            }
            else {
                return;
            }
        }
        ui->pro_fullpath->setText(pro_funpath_);
        on_pro_fullpath_editingFinished();
    }

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_select_pro_fullpath_clicked() {
    QString var_=QFileDialog::getOpenFileName(
                nullptr,
                QString(),
                QString(),
                "*.pro");
    if (var_.isEmpty()) { return; }
    ui->pro_fullpath->setText(std::move(var_));
}

void MainWindow::on_select_dir_name_clicked() {
    QString var_;
    if (ui->dir_name->text().isEmpty()==false) {
        var_=QFileDialog::getExistingDirectory();
    }
    else {
        var_=QFileDialog::getExistingDirectory(
                    nullptr,QString(),
                    QDir::cleanPath(qApp->applicationDirPath()+"/../../.."));
    }
    if (var_.isEmpty()) { return; }
    const static QRegExp reg_("[/\\\\]");
    {
        auto var_1=var_;
        var_1.resize(var_.size()-1);
        auto var_pos=var_1.lastIndexOf(reg_);
        if (var_pos<=0) { return; }
        var_=var_.right(var_.size()-var_pos-1);
    }
    ui->dir_name->setText(std::move(var_));
}

void MainWindow::on_pro_fullpath_editingFinished() {
    QFile var_file(ui->pro_fullpath->text());
    if (var_file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream var_stream(&var_file);
        ui->textBrowser->setPlainText(var_stream.readAll());
    }
}

void MainWindow::on_dir_name_editingFinished() {

}

void MainWindow::on_project_name_editingFinished() {

}

void MainWindow::on_do_button_clicked() {
    {
        const QByteArray app_path_=qApp->applicationFilePath().toLocal8Bit();
        const QByteArray pro_path_=ui->pro_fullpath->text().toLocal8Bit();
        const QByteArray dir_path_=ui->dir_name->text().toLocal8Bit();
        const QByteArray pro_name_=ui->project_name->text().toLocal8Bit();

        if (app_path_.isEmpty()) { return; }
        if (pro_path_.isEmpty()) { return; }
        if (pro_name_.isEmpty()) { return; }

        char * argv[4]{
             const_cast<char *>(app_path_.data()),
             const_cast<char *>(pro_path_.data()),
             const_cast<char *>(dir_path_.data()),
             const_cast<char *>(pro_name_.data())
        };

        run(argv);
    }
    on_pro_fullpath_editingFinished();
}


