#ifndef LCDEMULATORWIDGET_H
#define LCDEMULATORWIDGET_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QMouseEvent>

/* 类私有宏（只影响这个类） */
#define LCD_EMU_OFS_PIX 10

class LcdEmulatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LcdEmulatorWidget(int w, int h, uint8_t *fbuffer, int format, QWidget *parent = nullptr);
    ~LcdEmulatorWidget();

    uint8_t* buffer();        // 外部填充帧缓冲
    int width();
    int height();
    void updateLcd();         // 主动刷新

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    int lcdWidth;
    int lcdHeight;
    int imgFormat;
    uint8_t *fb;              // framebuffer
    QTimer timer;             // 定时刷新
};

#endif // LCDEMULATORWIDGET_H
