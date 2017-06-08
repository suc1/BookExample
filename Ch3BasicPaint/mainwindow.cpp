#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image = QImage(this->size(), QImage::Format_RGB32);
    image.fill(Qt::white);
    drawing = false;
    brushColor = Qt::black;
    brushSize = 2;

    QAction* menuAll[]={ui->action2px, ui->action5px, ui->action10px,
                       ui->actionBlack, ui->actionBlue, ui->actionGreen, ui->actionRed, ui->actionWhite};
    for(QAction* item : menuAll) item->setCheckable(true);

    CheckMenuPoint();
    CheckMenuColor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawing = true;
        lastPoint = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing)
    {
        QPainter painter(&image);
        painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine,
        Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        this->update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
    drawing = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter canvasPainter(this);
    canvasPainter.drawImage(this->rect(), image, image.rect());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //image.size();
}

void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPEG (*.jpg *.jpeg);;All files(*.*)");
    if (filePath == "")
    return;
    image.save(filePath);
}

void MainWindow::on_actionClear_triggered()
{
    image.fill(Qt::white);
    this->update();
}

void MainWindow::on_action2px_triggered()
{
    brushSize = 2;
    CheckMenuPoint();
}

void MainWindow::on_action5px_triggered()
{
    brushSize = 5;
    CheckMenuPoint();
}

void MainWindow::on_action10px_triggered()
{
    brushSize = 10;
    CheckMenuPoint();
}

void MainWindow::on_actionBlack_triggered()
{
    brushColor = Qt::black;
    CheckMenuColor();
}

void MainWindow::on_actionWhite_triggered()
{
    brushColor = Qt::white;
    CheckMenuColor();
}

void MainWindow::on_actionRed_triggered()
{
    brushColor = Qt::red;
    CheckMenuColor();
}

void MainWindow::on_actionGreen_triggered()
{
    brushColor = Qt::green;
    CheckMenuColor();
}

void MainWindow::on_actionBlue_triggered()
{
    brushColor = Qt::blue;
    CheckMenuColor();
}

void MainWindow::CheckMenuPoint()
{
    struct MenuSize
    {
    QAction *it;
    int size;
    };
    MenuSize allMenu[]={{ui->action2px, 2}, {ui->action5px, 5}, {ui->action10px, 10} };

    for(MenuSize one : allMenu ) one.it->setChecked(brushSize==one.size);
    //Todo: define a template
}

void MainWindow::CheckMenuColor()
{
    //todo: use template
    ui->actionBlack->setChecked(brushColor == Qt::black);
    ui->actionBlue->setChecked(brushColor == Qt::blue);
    ui->actionGreen->setChecked(brushColor == Qt::green);
    ui->actionRed->setChecked(brushColor == Qt::red);
    ui->actionWhite->setChecked(brushColor == Qt::white);
}
