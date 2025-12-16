#include "lcdemulatorwidget.h"
#include "touch_port.h"
#include <QPainter>
#include <cstring>
#include <QDebug.h>

LcdEmulatorWidget::LcdEmulatorWidget(int w, int h, uint8_t *fbuffer, int format, QWidget *parent)
    : QWidget(parent),
    lcdWidth(w),
    lcdHeight(h)
{
    //fb = new uint8_t[w * h * 3];   // RGB888
    fb = fbuffer;
    imgFormat = format;
    //std::memset(fb, 0, w*h*3);

    setFixedSize(w+LCD_EMU_OFS_PIX*2, h+LCD_EMU_OFS_PIX*2);

    // 30Hz 刷新
    connect(&timer, &QTimer::timeout, this, &LcdEmulatorWidget::updateLcd);
    timer.start(33);
}

LcdEmulatorWidget::~LcdEmulatorWidget()
{
    //delete[] fb;
}

uint8_t* LcdEmulatorWidget::buffer()
{
    return fb;
}

int LcdEmulatorWidget::width()
{
    return lcdWidth;
}

int LcdEmulatorWidget::height()
{
    return lcdHeight;
}

void LcdEmulatorWidget::updateLcd()
{
    update();   // 触发 paintEvent()
}

void LcdEmulatorWidget::paintEvent(QPaintEvent *)
{
//    QImage img(fb, lcdWidth, lcdHeight, QImage::Format_RGB888);
    QImage img(fb, lcdWidth, lcdHeight, (QImage::Format)imgFormat);

    QPainter p(this);
    p.drawImage(LCD_EMU_OFS_PIX, LCD_EMU_OFS_PIX, img);
}

void LcdEmulatorWidget::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<<"TOUCH_EVENT_DOWN:"<<e->x()-LCD_EMU_OFS_PIX<<","<<e->y()-LCD_EMU_OFS_PIX;
    touch_port_input(TOUCH_EVENT_DOWN, e->x()-LCD_EMU_OFS_PIX, e->y()-LCD_EMU_OFS_PIX);
}

void LcdEmulatorWidget::mouseReleaseEvent(QMouseEvent *e)
{
    touch_port_input(TOUCH_EVENT_UP, e->x()-LCD_EMU_OFS_PIX, e->y()-LCD_EMU_OFS_PIX);
}

void LcdEmulatorWidget::mouseMoveEvent(QMouseEvent *e)
{
    touch_port_input(TOUCH_EVENT_MOVE, e->x()-LCD_EMU_OFS_PIX, e->y()-LCD_EMU_OFS_PIX);
}

