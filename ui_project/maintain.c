#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

enum {
    LV_MENU_ITEM_BUILDER_VARIANT_1,
    LV_MENU_ITEM_BUILDER_VARIANT_2
};
typedef uint8_t lv_menu_builder_variant_t;
lv_obj_t * menu;
static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                              lv_menu_builder_variant_t builder_variant)
{
    lv_obj_t * obj = lv_menu_cont_create(parent);

    lv_obj_t * img = NULL;
    lv_obj_t * label = NULL;

    if(icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if(txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }

    if(builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }

    return obj;
}

static lv_obj_t * create_slider(lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max,
                                int32_t val)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

    lv_obj_t * slider = lv_slider_create(obj);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_OFF);

    if(icon == NULL) {
        lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    }

    return obj;
}
static lv_obj_t * create_switch(lv_obj_t * parent, const char * icon, const char * txt, bool chk)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t * sw = lv_switch_create(obj);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);

    return obj;
}
static lv_obj_t* create_wifi_page(lv_obj_t *parent)
{
    lv_obj_t *cont, *label;
    cont = lv_menu_cont_create(parent);
    lv_obj_set_layout(cont, 0);
    lv_obj_set_height(cont,  760);
    label = lv_label_create(cont);
    lv_label_set_text(label, "wifi information");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    return cont;
}
static lv_obj_t* create_user_page(lv_obj_t *parent)
{
    lv_obj_t *cont, *label;
    cont = lv_menu_cont_create(parent);
    lv_obj_set_layout(cont, 0);
    lv_obj_set_height(cont,  760);
    label = lv_label_create(cont);
    lv_label_set_text(label, "user information");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    return cont;
}
void ui_maintain_init(lv_obj_t *parent)
{
    lv_group_remove_all_objs(lv_group_get_default());

    menu = lv_menu_create(parent);
    //lv_obj_set_style_bg_color(menu, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
    //lv_obj_add_event_cb(menu, back_event_handler, LV_EVENT_CLICKED, menu);
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);

    lv_obj_t * root_page;
    lv_obj_t * cont, *section;
    lv_obj_t * label, *img;
    lv_obj_t *user_page, *wifi_page, *soft_page;
    lv_obj_t *user_item, *wifi_item, *soft_item;
    root_page = lv_menu_page_create(menu, "infomation");
    section = lv_menu_section_create(root_page);
    /* 用户菜单 */
    user_item = lv_menu_cont_create(section);
    lv_group_add_obj(lv_group_get_default(), user_item);
    img = lv_img_create(user_item);
    lv_img_set_src(img, LV_SYMBOL_SETTINGS);
    label = lv_label_create(user_item);
    lv_label_set_text(label, "user item");
    
    /* wifi菜单 */
    wifi_item = lv_menu_cont_create(section);
    lv_group_add_obj(lv_group_get_default(), wifi_item);
    img = lv_img_create(wifi_item);
    lv_img_set_src(img, LV_SYMBOL_SETTINGS);
    label = lv_label_create(wifi_item);
    lv_label_set_text(label, "wifi item");

    //section = lv_menu_section_create(root_page);

    /* 其他菜单 */
    // soft_item = lv_menu_cont_create(root_page);
    // label = lv_label_create(soft_item);
    // lv_label_set_text(label, "other");


    /* 用户页 */
    user_page = lv_menu_page_create(menu, NULL);
    cont = create_user_page(user_page);

    /* wifi 页 */
    wifi_page = lv_menu_page_create(menu, NULL);
    cont = create_wifi_page(wifi_page);

    lv_menu_set_load_page_event(menu, user_item, user_page);
    lv_menu_set_load_page_event(menu, wifi_item, wifi_page);

    lv_menu_set_sidebar_page(menu, root_page);
    lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
    return;
}