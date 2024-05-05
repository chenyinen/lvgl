#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

int angle = 0;

static void move(void * obj, int32_t v)
{
    angle = v;
    lv_obj_invalidate(obj);
}
static void add_mask_event_cb(lv_event_t * e)
{
    static lv_draw_mask_map_param_t m;
    static lv_draw_mask_fade_param_t fade_mask;
    static int16_t mask_id;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    lv_opa_t * mask_map = lv_event_get_user_data(e);
    

    if(code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);
    }
    else if (code == LV_EVENT_DRAW_MAIN) {
        // lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);
        // lv_draw_img_dsc_t draw_img_dsc;
        // //lv_obj_draw_part_dsc_t * draw_part = lv_event_get_draw_part_dsc(e);
        // lv_draw_img_dsc_init(&draw_img_dsc);
        // draw_img_dsc.opa = 64;
        // lv_draw_img(draw_ctx, &draw_img_dsc, &obj->coords, "A:/home/share/test2.jpg");
    }
    else if(code == LV_EVENT_DRAW_MAIN_BEGIN) {
        
        lv_draw_mask_map_init(&m, &obj->coords, mask_map);
        //lv_draw_mask_fade_init(&fade_mask, &obj->coords, );
        mask_id = lv_draw_mask_add(&m, NULL);
    }
    else if(code == LV_EVENT_DRAW_MAIN_END) {
         lv_draw_mask_remove_id(mask_id);
         lv_draw_mask_free_param(&m);
        
    }
}

void ui_app_init(lv_obj_t *parent)
{

    /* Create the mask of a text by drawing it to a canvas*/
    static lv_opa_t mask_map[480 * 800];
    lv_draw_rect_dsc_t draw_rect;
    lv_draw_arc_dsc_t draw_arc;
    lv_point_t point[4];
    /*Create a "8 bit alpha" canvas and clear it*/
    lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, mask_map, 480, 800, LV_IMG_CF_ALPHA_8BIT);
    lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);

    point[0].x = 40;
    point[0].y = 800;
    point[1].x = 400;
    point[1].y = 600;
    point[2].x = 450;
    point[2].y = 650;

    lv_draw_rect_dsc_init(&draw_rect);
    draw_rect.bg_color = lv_color_make(0x88, 0x88, 0x88);
    lv_canvas_draw_polygon(canvas, point, 3, &draw_rect);

    lv_draw_arc_dsc_init(&draw_arc);
    draw_arc.color = lv_color_white();
    //draw_arc.color = lv_color_black();
    draw_arc.width = 50;
    lv_canvas_draw_arc(canvas, 450, 600, 50, 0, 180, &draw_arc);
    #if 0
    point[0].x = 40;
    point[0].y = 800;
    point[1].x = 450;
    point[1].y = 650;
    point[2].x = 480;
    point[2].y = 650;
    point[3].x = 480;
    point[3].y = 800;
    draw_rect.bg_color = lv_color_black();
    lv_canvas_draw_polygon(canvas, point, 4, &draw_rect);
    #endif

    lv_obj_del(canvas);
    

    lv_obj_t *img = lv_img_create(parent);
    lv_obj_set_size(img, 480, 800);
    #if 0
    lv_obj_set_style_bg_color(img, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(img, 128, 0);
    lv_obj_set_style_img_opa(img, 128, 0);
    #endif
    lv_img_set_src(img, "A:/home/share/test2.jpg");
    lv_obj_center(img);
    lv_obj_add_event_cb(img, add_mask_event_cb, LV_EVENT_ALL, mask_map);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, img);
    lv_anim_set_exec_cb(&a, move);
    lv_anim_set_time(&a, 1500);
    lv_anim_set_values(&a, 0, 360);
    //lv_anim_start(&a);

    return ;
}