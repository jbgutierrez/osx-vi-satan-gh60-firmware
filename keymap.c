#include "satan.h"
#include "mousekey.h"


// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define _BL 0
#define _AL 1
#define _ML 2

#define _______ KC_TRNS

enum function_id {
  SHIFT_ESC,
};

enum macro_id {
  NONE = 0,
  A_MUL,
  A_MUR,
  A_MDL,
  A_MDR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Alt |Gui |      Space            |Alt |Gui |FN  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_BL] = KEYMAP(
  F(0),    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, \
  KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         KC_RSFT, \
  KC_LCTL, KC_LALT,KC_LGUI,                KC_SPC,                                 KC_RGUI,KC_RALT, KC_RCTL,MO(_AL)),

/* Keymap _AL: Arrow Layer
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                       |    |    |    |     |
   * `-----------------------------------------------------------'
   */
[_AL] = KEYMAP(
  KC_GRV , _______, _______,       _______, KC_END,  _______, _______,       _______,  _______, _______, KC_HOME, _______, _______, KC_BSPC, \
  _______, _______, LALT(KC_RGHT), KC_END,  _______, _______, _______,       KC_PGUP,  KC_INS,  _______, KC_PAST, _______, _______, _______, \
  _______, _______, KC_HOME,       KC_PGDN, _______, _______, KC_LEFT,       KC_DOWN,  KC_UP,   KC_RGHT, _______, _______,          _______, \
  _______,          _______,       KC_DEL,  _______, KC_CAPS, LALT(KC_RGHT), _______,  _______, _______, _______, _______,          _______, \
  _______, _______, _______,                                  _______,                                   _______, _______, _______, _______),

  /* Keymap _ML: Media and Mouse Layer
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                       |    |    |    |     |
   * `-----------------------------------------------------------'
   */
[_ML] = KEYMAP(
  KC_GRV , KC_F14,  KC_F15,  _______, _______ , _______, _______, KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD, KC_VOLU, _______, \
  _______, _______, _______, _______, _______ , _______, _______, M(A_MUL), KC_MS_U,  M(A_MUR), _______,  _______, _______, _______, \
  _______, _______, _______, KC_BTN1, KC_BTN2 , _______, _______, KC_MS_L,  _______,  KC_MS_R,  _______,  _______,          _______, \
  _______,          _______, _______, _______ , _______, _______, _______,  M(A_MDL), KC_MS_D,  M(A_MDR), _______,          _______, \
  _______, _______, _______,                             KC_MPLY,                               _______,  _______, _______, _______),
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case 0:
      return MACRODOWN(TYPE(KC_RSFT), END);
      break;

    case A_MUL:
      if (record->event.pressed) {
        mousekey_on(KC_MS_UP);
        mousekey_on(KC_MS_LEFT);
      } else {
        mousekey_off(KC_MS_UP);
        mousekey_off(KC_MS_LEFT);
      }
      mousekey_send();
      break;

    case A_MUR:
      if (record->event.pressed) {
        mousekey_on(KC_MS_UP);
        mousekey_on(KC_MS_RIGHT);
      } else {
        mousekey_off(KC_MS_UP);
        mousekey_off(KC_MS_RIGHT);
      }
      mousekey_send();
      break;

    case A_MDL:
      if (record->event.pressed) {
        mousekey_on(KC_MS_DOWN);
        mousekey_on(KC_MS_LEFT);
      } else {
        mousekey_off(KC_MS_DOWN);
        mousekey_off(KC_MS_LEFT);
      }
      mousekey_send();
      break;

    case A_MDR:
      if (record->event.pressed) {
        mousekey_on(KC_MS_DOWN);
        mousekey_on(KC_MS_RIGHT);
      } else {
        mousekey_off(KC_MS_DOWN);
        mousekey_off(KC_MS_RIGHT);
      }
      mousekey_send();
      break;
  }
  return MACRO_NONE;
};
