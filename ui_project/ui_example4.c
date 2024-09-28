#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

void async_btn(void *p)
{
    lv_event_send(p, LV_EVENT_PRESSED, lv_indev_get_act());
}
void async_btn2(void *p)
{

    lv_event_send(p, LV_EVENT_RELEASED, lv_indev_get_act());
}

static void event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_user_data(e);

    
    lv_async_call_timeout(async_btn, obj, 300);
    lv_async_call_timeout(async_btn2, obj, 500);

}

void ui_example_4(lv_obj_t *parent)
{
    //lv_obj_set_style_bg_color(lv_scr_act(), lv_palette_main(LV_PALETTE_BLUE), 0);

    lv_obj_t *obj = lv_btn_create(lv_scr_act());

    lv_obj_set_style_border_width(obj, 0, 0);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_size(obj, 40, 40);
    lv_obj_set_style_pad_all(obj, 0, 0);
    lv_obj_set_style_outline_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_outline_color(obj, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_t *img = lv_img_create(obj);
    lv_img_set_src(img, "A:/home/share/call4.png");
    lv_obj_center(img);

    lv_obj_center(obj);

    static lv_style_t style_pr;
    lv_style_init(&style_pr);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_pr, 300);
    lv_style_set_outline_color(&style_pr, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);

    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&style_pr, &trans);

    lv_obj_add_style(obj, &style_pr, LV_STATE_PRESSED);

    lv_obj_t *test = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(test, event_cb, LV_EVENT_CLICKED, obj);


    return ;
}