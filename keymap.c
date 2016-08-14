#include "satan.h"
#include "mousekey.h"
#include "action_tapping.h"

#define _BL 0
#define _AL 1
#define _ML 2

#define _______ KC_TRNS
#define CK_PASTE LGUI(KC_V)
#define CK_COPY LGUI(KC_C)
#define CK_CUT LGUI(KC_X)
#define CK_UNDO LGUI(KC_Z)
#define CK_WORD LALT(KC_RGHT)
#define CK_BWORD LALT(KC_RGHT)

enum function_id {
  F_ESC = 0,
  F_BSE,
  F_SFT,
  F_ALT,
  F_CTRL,
  F_CYCL,
  F_HSFT,
};

enum macro_id {
  NONE = 0,

  // Diagonal mouse movement
  A_MUL,
  A_MUR,
  A_MDL,
  A_MDR,

  // Function / number keys
  KF_1, // 1, F1
  KF_2, // 2, F2
  KF_3, // ...
  KF_4,
  KF_5,
  KF_6,
  KF_7,
  KF_8,
  KF_9,
  KF_10,
  KF_11, // =, F11
};

enum enum_id {
  TD_SCLN = 0
};

uint16_t kf_timers[12];
uint16_t quote_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |Gui/Alt|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Alt |Gui |      Space            |Alt |Gui |Ctrl|Lead |
   * `-----------------------------------------------------------'
   */
[_BL] = KEYMAP(
  F(F_ESC),   KC_1,      KC_2,     KC_3,  KC_4,  KC_5,   KC_6,  KC_7,  KC_8,  KC_9,     KC_0,         KC_MINS,  KC_EQL,   KC_BSPC, \
  KC_TAB,     KC_Q,      KC_W,     KC_E,  KC_R,  KC_T,   KC_Y,  KC_U,  KC_I,  KC_O,     KC_P,         KC_LBRC,  KC_RBRC,  KC_BSLS, \
  F(F_CYCL),  KC_A,      KC_S,     KC_D,  KC_F,  KC_G,   KC_H,  KC_J,  KC_K,  KC_L,     TD(TD_SCLN),  KC_QUOT,            KC_ENT,  \
  F(F_SFT),              KC_Z,     KC_X,  KC_C,  KC_V,   KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,       KC_SLSH,            KC_RSFT, \
  F(F_CTRL),  F(F_ALT),  KC_LGUI,                KC_SPC,                                KC_RGUI,      KC_RALT,  KC_RCTL,  KC_LEAD),

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
  F(F_BSE), _______, _______, _______, KC_END,  _______,   _______,   _______,  _______, _______, KC_HOME , _______, _______, KC_BSPC, \
  _______ , _______, CK_WORD, KC_END,  _______, _______,   CK_COPY,   KC_PGUP,  KC_INS,  _______, CK_PASTE, _______, _______, _______, \
  _______ , _______, _______, KC_HOME, KC_PGDN, _______,   _______,   KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT,  _______,          _______, \
  _______ ,          CK_UNDO, KC_DEL,  CK_CUT , F(F_HSFT), CK_BWORD,  _______,  _______, _______, _______ , _______,          _______, \
  _______ , _______, _______,                              _______,                               _______ , _______, _______, _______),

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
  F(F_BSE), KC_F14,  KC_F15,  _______, _______ , _______, _______, KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD, KC_VOLU, _______, \
  _______ , _______, _______, _______, _______ , _______, _______, M(A_MUL), KC_MS_U,  M(A_MUR), _______,  _______, _______, _______, \
  _______ , _______, _______, KC_BTN1, KC_BTN2 , _______, _______, KC_MS_L,  _______,  KC_MS_R,  _______,  _______,          _______, \
  _______ ,          _______, _______, _______ , _______, _______, _______,  M(A_MDL), KC_MS_D,  M(A_MDR), _______,          _______, \
  _______ , _______, _______,                             KC_MPLY,                               _______,  _______, _______, _______),
};

const qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCLN]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, S(KC_SCLN))
};

const uint16_t PROGMEM fn_actions[] = {
  [F_ESC]  = ACTION_FUNCTION(F_ESC),
  [F_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS),
  [F_SFT]  = ACTION_MODS_ONESHOT(MOD_LSFT),
  [F_ALT]  = ACTION_MODS_ONESHOT(MOD_LALT),
  [F_CTRL] = ACTION_MODS_ONESHOT(MOD_LCTL),
  [F_CYCL] = ACTION_MODS_KEY(MOD_LALT, KC_TAB),
  [F_HSFT] = ACTION_FUNCTION(F_HSFT),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t f_esc_shift_mask;
  switch (id) {
    case F_ESC:
      f_esc_shift_mask = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
      if (record->event.pressed) {
        if (f_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (f_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      clear_oneshot_mods();
      break;
    case F_HSFT:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
          unregister_code(KC_LSFT);
        } else {
          register_code(KC_LSFT);
        }
      }
      break;
  }
}

const macro_t *ang_handle_kf(keyrecord_t *record, uint8_t id) {
  uint8_t code = id - KF_1;

  if (record->event.pressed) {
    kf_timers[code] = timer_read();
  } else {
    uint8_t kc;

    if (timer_elapsed(kf_timers[code]) > TAPPING_TERM) {
      // Long press
      kc = KC_F1 + code;
    } else {
      if (id == KF_11)
        kc = KC_EQL;
      else
        kc = KC_1 + code;
    }

    register_code(kc);
    unregister_code(kc);
  }
  return MACRO_NONE;
}

const macro_t *handle_diagonal_mouse(keyrecord_t *record, uint16_t vertical, uint16_t horizontal) {
  if (record->event.pressed) {
    mousekey_on(vertical);
    mousekey_on(horizontal);
  } else {
    mousekey_off(vertical);
    mousekey_off(horizontal);
  }
  mousekey_send();
  return MACRO_NONE;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case 0: return MACRODOWN(TYPE(KC_RSFT), END);

    case A_MUL: return handle_diagonal_mouse(record, KC_MS_UP,   KC_MS_LEFT);
    case A_MUR: return handle_diagonal_mouse(record, KC_MS_UP,   KC_MS_RIGHT);
    case A_MDL: return handle_diagonal_mouse(record, KC_MS_DOWN, KC_MS_LEFT);
    case A_MDR: return handle_diagonal_mouse(record, KC_MS_DOWN, KC_MS_RIGHT);

    case KF_1 ... KF_11: return ang_handle_kf(record, id);
  }
  return MACRO_NONE;
};

LEADER_EXTERNS();

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (quote_timer) {
      quote_timer = 0;
      switch (keycode) {
        case KC_A:
        case KC_E:
        case KC_I:
        case KC_O:
        case KC_U:
          register_code(KC_RALT);
          register_code(KC_E);
          unregister_code(KC_E);
          unregister_code(KC_RALT);
      }
    } else {
      if (keycode == KC_QUOT) {
        quote_timer = timer_read();
        return false;
      }
    }
  }

  return true;
}

void matrix_scan_user(void) {
  if (quote_timer && timer_elapsed(quote_timer) > TAPPING_TERM) {
    quote_timer = 0;
    register_code(KC_QUOT);
    unregister_code(KC_QUOT);
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    /* `c` activates cursor layer */
    SEQ_ONE_KEY(KC_C) {
      layer_on(_AL);
    }
    /* `d` shows desktop */
    SEQ_ONE_KEY(KC_D) {
      register_code(KC_F11);
      unregister_code(KC_F11);
    }
    /* `e` launches exposé and enters mouse layer */
    SEQ_ONE_KEY(KC_E) {
      register_code(KC_LCTL);
      register_code(KC_UP);
      unregister_code(KC_UP);
      unregister_code(KC_LCTL);
      layer_on(_ML);
    }
    /* `l` locks screen */
    SEQ_ONE_KEY(KC_L) {
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      register_code(KC_MEDIA_EJECT);
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
      unregister_code(KC_MEDIA_EJECT);
    }
    /* `m` activates mouse and media layer */
    SEQ_ONE_KEY(KC_M) {
      layer_on(_ML);
    }
    /* `p` types password */
    PASSWORD_SEQUENCE {
      SEND_STRING (PASSWORD);
    }
    /* `s` saves screenshot */
    SEQ_ONE_KEY(KC_S) {
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      register_code(KC_3);
      unregister_code(KC_LGUI);
      unregister_code(KC_LSFT);
      unregister_code(KC_3);
    }
    /* `ss` saves screenshot of selected area */
    SEQ_TWO_KEYS(KC_S, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      register_code(KC_4);
      unregister_code(KC_LGUI);
      unregister_code(KC_LSFT);
      unregister_code(KC_4);
    }
    /* `u` types username */
    SEQ_ONE_KEY (KC_U) {
      SEND_STRING (USERNAME);
    }
  }
}
