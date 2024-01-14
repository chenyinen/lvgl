#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>

struct volice_adjust_info {
    lv_obj_t *slider;
    lv_obj_t *slider_label;
};

static struct volice_adjust_info* get_voilce_adjust()
{
    static struct volice_adjust_info g_volice_adjust;
    return &g_volice_adjust;
}
static void adjust_slider_label_pos()
{
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();

    lv_obj_align_to(volice_info->slider_label, volice_info->slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    return ;
}
static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();
    
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(volice_info->slider_label, buf);
    adjust_slider_label_pos();
}
static void anim_x_cb(void * var, int32_t v)
{
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();

    lv_obj_set_x(var, v);
    adjust_slider_label_pos();
}
static void anim_size_cb(void * var, int32_t v)
{
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();

    lv_obj_set_height(var, v);
    adjust_slider_label_pos();
}

void audio_volue_come(bool back)
{
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();
    lv_anim_t animation;
    if (!back) {
        lv_obj_clear_flag(volice_info->slider, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(volice_info->slider_label, LV_OBJ_FLAG_HIDDEN);
    }

    lv_anim_init(&animation);
    lv_anim_set_var(&animation, volice_info->slider);
    if (!back) {
        lv_anim_set_values(&animation, 30, -20);
    }
    else {
        lv_anim_set_values(&animation, -20, 30);
    }
    lv_anim_set_time(&animation, 200);
    lv_anim_set_path_cb(&animation, lv_anim_path_ease_in);
    lv_anim_set_exec_cb(&animation, anim_x_cb);
    lv_anim_start(&animation);
    lv_anim_set_exec_cb(&animation, anim_size_cb);
    if (!back) {
        lv_anim_set_values(&animation, 10, 240);
    }
    else {
        lv_anim_set_values(&animation, 240, 10);
    }
    
    lv_anim_start(&animation);

    return ;
}
static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();

    if(code == LV_EVENT_CLICKED) {
        audio_volue_come(false);
    }
}
static void event_handler2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();

    if(code == LV_EVENT_CLICKED) {
        audio_volue_come(true);
    }
}
void audio_volue_init(lv_obj_t *parent)
{   
    struct volice_adjust_info* volice_info  =  get_voilce_adjust();
    lv_obj_t *slider = lv_slider_create(parent);
    lv_obj_set_size(slider, 15, 240); 
    lv_obj_align(slider, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *slider_label = lv_label_create(parent);
    lv_label_set_text(slider_label, "0%");
    lv_obj_add_flag(slider_label, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * btn1 = lv_btn_create(parent);
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t * btn2 = lv_btn_create(parent);
    lv_obj_add_event_cb(btn2, event_handler2, LV_EVENT_CLICKED, NULL);
    lv_obj_align(btn2, LV_ALIGN_TOP_MID, 0, 0);

    volice_info->slider = slider;
    volice_info->slider_label = slider_label;

    adjust_slider_label_pos();

    return ;
}