#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

void ui_app_init()
{
    ui_maintain_init(lv_scr_act());
    return ;
}