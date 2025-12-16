#include <QApplication>
#include "LCDSim/lcdemulatorwidget.h"
#include "LCDSim/touch_port.h"
#include <QDebug>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "lvgl.h"
#include "demos/lv_demos.h"

#define  TFT_HOR_RES        800
#define  TFT_VER_RES        480

QTimer timer_systick;             // systick_handler定时器
uint32_t g_sys_tick_ms = 0;

lv_color_t fb_buffer[TFT_HOR_RES * TFT_VER_RES];


/* 系统时钟中断服务函数，设置为10ms中断一次 */
void systick_handler(void)
{
    g_sys_tick_ms += 10;
    lv_timer_handler();
}

static uint32_t my_tick_cb(void)
{
    return g_sys_tick_ms;
}

static void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    /*Write px_map to the area->x1, area->x2, area->y1, area->y2 area of the
     *frame buffer or external display controller. */
    int32_t w = area->x2 - area->x1 + 1;
    int32_t h = area->y2 - area->y1 + 1;

    lv_color_t *src = (lv_color_t *)px_map;

    for(int y = 0; y < h; y++) {
        memcpy(&fb_buffer[(area->y1 + y) * TFT_HOR_RES + area->x1],
               src + y * w,
               w * sizeof(lv_color_t));
    }
    lv_display_flush_ready(disp);
}

static void my_touch_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
{
    if(tp_get_is_pressed()) {
        data->point.x = tp_get_x();
        data->point.y = tp_get_y();
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

int main(int argc,char**argv){
    QApplication a(argc,argv);

    LcdEmulatorWidget lcd(TFT_HOR_RES, TFT_VER_RES, (uint8_t*)fb_buffer, QImage::Format_BGR888);
    lcd.show();

    lv_init();
    lv_tick_set_cb(my_tick_cb);
    lv_display_t * display = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    static uint8_t buf[TFT_HOR_RES * TFT_VER_RES / 10 * 3]; /* x2 because of 16-bit color depth */
    lv_display_set_buffers(display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, my_flush_cb);
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touch_read_cb);


    if (!lv_demos_create(&argv[1], argc - 1)) {
        lv_demos_show_help();
    }


    QObject::connect(&timer_systick, &QTimer::timeout, [](){
        systick_handler();
    });
    timer_systick.start(10);


    return a.exec();
}
