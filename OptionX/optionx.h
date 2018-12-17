#ifndef OPTIONX_H
#define OPTIONX_H
#include <QtDataVisualization>
#include <QMainWindow>
#include <QWidget>

using namespace QtDataVisualization;

namespace Ui {
class OptionX;
}

class OptionX : public QWidget
{
    Q_OBJECT

public:
    explicit OptionX(QWidget *parent = nullptr);
    ~OptionX();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::OptionX *ui;
    QMainWindow window;
};

#endif // OPTIONX_H
