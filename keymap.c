#include "satan.h"
#include "mousekey.h"
#include "action_tapping.h"

#define _BA 0
#define _AR 1
#define _MO 2
#define _TM 3
#define _WN 4
#define _HW 5

#define _______ KC_TRNS

#define B_LGUI GUI_T(KC_PAST)

#define A_BWORD LALT(KC_LEFT)
#define A_END LCTL(KC_E)
#define A_FIND LGUI(KC_F)
#define A_FNEXT LGUI(KC_G)
#define A_PASTE LGUI(KC_V)
#define A_START LCTL(KC_A)
#define A_WORD LALT(KC_RGHT)

#define W_CENT LGUI(LALT(KC_C))
#define W_DOWN LGUI(LALT(KC_DOWN))
#define W_LEFT LGUI(LALT(KC_LEFT))
#define W_MAX LGUI(LALT(KC_F))
#define W_RGHT LGUI(LALT(KC_RGHT))
#define W_TOGGLE LGUI(KC_TAB)
#define W_UP LGUI(LALT(KC_UP))
#define W_NEXT LCAG(KC_RGHT)
#define W_PREV LCAG(KC_LEFT)

#define LT_A LT(_AR, KC_A)
#define LT_SPC LT(_AR, KC_SPC)
#define LT_TAB LT(_WN, KC_TAB)
#define LT_GRV LT(_TM, KC_GRV)

enum key_id {
  NONE = 0,
  L_BSE,

  F_LSFT,
  F_RSFT,

  // Arrow
  C_VMOD,

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
  KF_0,
  KF_MINS,
  KF_EQL, // =, F12

  // TMUX
  T_LEFT,
  T_DOWN,
  T_UP,
  T_RGHT,
  T_NEW,
  T_REN,
  T_CHSE,
  T_RSZE,
  T_SPLT,
  T_RTE,
  T_LAY,
  T_COPY,
  T_NEXT,
  T_PREV,

  // Tap dancing definintions
  TD_SCLN,
  TD_LBRC,
  TD_RBRC,
  TD_GRV,
  TD_CAPS,
};

uint16_t kf_timers[12];
uint16_t quote_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BA: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |   ~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |EscCtrl|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Alt |Gui |      Space            |Lead |Gui |Alt |Ctrl|
   * `-----------------------------------------------------------'
   */
[_BA] = KEYMAP(
  TD(TD_GRV)  , M(KF_1) , M(KF_2) , M(KF_3) , M(KF_4) , M(KF_5) , M(KF_6) , M(KF_7)  , M(KF_8) , M(KF_9) , M(KF_0)     , M(KF_MINS)  , M(KF_EQL)   , KC_BSPC     , \
  LT_TAB      , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U     , KC_I    , KC_O    , KC_P        , TD(TD_LBRC) , TD(TD_RBRC) , KC_BSLS     , \
  TD(TD_CAPS) , LT_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J     , KC_K    , KC_L    , TD(TD_SCLN) , KC_QUOT     , /*          , */KC_ENT    , \
  F(F_LSFT)   , /*      , */KC_Z  , KC_X    , KC_C    , KC_V    , KC_B    , KC_N     , KC_M    , KC_COMM , KC_DOT      , KC_SLSH     , /*          , */F(F_RSFT) , \
  KC_LCTL     , KC_LALT , B_LGUI  , /*      ,         ,         ,         , */LT_SPC , /*      ,         , */ KC_LEAD  , KC_RGUI     , KC_RALT     , KC_RCTL)    ,

/* Keymap _AR: Arrow Layer */
[_AR] = KEYMAP(
  _______  , _______ , _______   , _______ , KC_END  , _______   , _______ , _______   , _______ , _______ , KC_HOME    , _______ , _______ , _______   , \
  _______  , _______ , A_WORD    , A_END   , _______ , _______   , _______ , KC_PGUP   , KC_INS  , _______ , A_PASTE    , _______ , _______ , _______   , \
  F(L_BSE) , _______ , A_START   , KC_PGDN , _______ , _______   , KC_LEFT , KC_DOWN   , KC_UP   , KC_RGHT , _______    , _______ , /*      , */_______ , \
  _______  , /*      , */_______ , KC_DEL  , _______ , F(C_VMOD) , A_BWORD , A_FNEXT   , _______ , _______ , _______    , A_FIND  , /*      , */_______ , \
  _______  , _______ , _______   , /*      ,         ,           ,         , */_______ , /*      ,         , */ _______ , _______ , _______ , _______)  ,

/* Keymap _MO: Media and Mouse Layer */
[_MO] = KEYMAP(
  _______  , KC_F14  , KC_F15     , _______ , _______ , _______ , _______ , KC_MPRV   , KC_MPLY , KC_MNXT , KC_MUTE    , KC_VOLD , KC_VOLU , _______    , \
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , _______ , _______    , \
  F(L_BSE) , _______ , _______    , KC_BTN1 , KC_BTN2 , _______ , KC_MS_L , KC_MS_D   , KC_MS_U , KC_MS_R , _______    , _______ , /*      , */ _______ , \
  _______  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , /*      , */ _______ , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */KC_MPLY , /*      ,         , */ _______ , _______ , _______ , _______)   ,

/* Keymap _TM: TMUX Layer */
[_TM] = KEYMAP(
  _______ , _______ , _______      , _______ , M(T_NEW) , _______ , _______   , _______    , _______ , _______   , _______    , M(T_SPLT) , _______ , _______     , \
  _______ , _______ , _______      , _______ , M(T_REN) , _______ , _______   , _______    , _______ , M(T_RTE)  , M(T_PREV)  , _______   , _______ , _______     , \
  F(L_BSE), _______ , M(T_CHSE)    , _______ , _______  , _______ , M(T_LEFT) , M(T_DOWN)  , M(T_UP) , M(T_RGHT) , _______    , _______   , /*      , */M(T_COPY) , \
  _______ , /*      , */ M(T_RSZE) , _______ , _______  , _______ , _______   , M(T_NEXT)  , _______ , _______   , _______    , _______   , /*      , */_______   , \
  _______ , _______ , _______      , /*      ,          ,         ,           , */M(T_LAY) , /*      ,           , */ _______ , _______   , _______ , _______)    ,

/* Keymap _WN: Windows Layer */
[_WN] = KEYMAP(
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______  , _______    , _______ , _______ , _______   , \
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , W_TOGGLE , W_PREV     , _______ , _______ , _______   , \
  F(L_BSE) , _______ , _______    , KC_F11  , W_MAX   , _______ , W_LEFT  , W_DOWN    , W_UP    , W_RGHT   , _______    , _______ , /*      , */_______ , \
  _______  , /*      , */ _______ , _______ , W_CENT  , _______ , _______ , W_NEXT    , _______ , _______  , _______    , _______ , /*      , */_______ , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,          , */ _______ , _______ , _______ , _______)  ,

/* Keymap _HW: Hardware Layer */
[_HW] = KEYMAP(
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , _______ , _______   , \
  _______  , _______ , _______    , _______ , RESET   , _______ , _______ , _______   , _______ , _______ , _______    , BL_DEC  , BL_INC  , BL_TOGG   , \
  F(L_BSE) , _______ , _______    , DEBUG   , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , /*      , */_______ , \
  _______  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , /*      , */_______ , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,         , */ _______ , _______ , _______ , _______)  ,
};

#define TAP_ONCE(code) register_code (code); unregister_code (code)

void shifted_tap_dance_fn(qk_tap_dance_state_t *state, void *user_data) {
  bool shifted = state->count == 2;
  uint8_t kc;
  switch(state->keycode) {
    case TD(TD_SCLN) : kc = KC_SCLN; break;
    case TD(TD_LBRC) : kc = KC_LBRC; break;
    case TD(TD_RBRC) : kc = KC_RBRC; break;
    case TD(TD_GRV)  : kc = KC_GRV; break;
    default: return;
  }

  if (shifted) {
    register_code (KC_RSFT);
    TAP_ONCE(kc);
    unregister_code (KC_RSFT);
  } else {
    TAP_ONCE(kc);
  }
};

typedef struct {
  bool locked;
} caps_state;

void on_caps_tap_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
  caps_state *caps = (caps_state *) user_data;

  if (caps->locked || (!state->pressed && state->count > 1)) {
    register_code(KC_CAPS);
  } else {
    if (state->pressed) {
      register_code(KC_RCTL);
    } else {
      register_code(KC_ESC);
    }
  }
}

void on_caps_tap_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
  caps_state *caps = (caps_state *) user_data;

  if (caps->locked || (!state->pressed && state->count > 1)) {
    unregister_code(KC_CAPS);
    caps->locked = !caps->locked;
  } else {
    if (state->pressed) {
      unregister_code(KC_RCTL);
    } else {
      unregister_code(KC_ESC);
      clear_keyboard();
    }
  }
}

const qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCLN] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_LBRC] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_RBRC] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_GRV]  = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_CAPS] = {
    .fn = { NULL, on_caps_tap_dance_finished_fn, on_caps_tap_dance_reset_fn },
    .user_data = (void *)&((caps_state) { false }),
  },
};

const uint16_t PROGMEM fn_actions[] = {
  [L_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS),

  [F_LSFT] = ACTION_MODS_ONESHOT(MOD_LSFT),
  [F_RSFT] = ACTION_MODS_ONESHOT(MOD_RSFT),
  [C_VMOD] = ACTION_FUNCTION(C_VMOD),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case C_VMOD:
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
      switch(id) {
        case KF_EQL: kc = KC_EQL; break;
        case KF_MINS: kc = KC_MINS; break;
        default: kc = KC_1 + code; break;
      }
    }

    register_code(kc);
    unregister_code(kc);
  }
  return MACRO_NONE;
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case 0: return MACRODOWN(TYPE(KC_RSFT), END);

    case KF_1 ... KF_EQL: return ang_handle_kf(record, id);

    case T_LEFT:  return MACRODOWN(D(RCTL), T(B), U(RCTL), T(H), END);
    case T_DOWN:  return MACRODOWN(D(RCTL), T(B), U(RCTL), T(J), END);
    case T_UP:    return MACRODOWN(D(RCTL), T(B), U(RCTL), T(K), END);
    case T_RGHT:  return MACRODOWN(D(RCTL), T(B), U(RCTL), T(L), END);
    case T_REN:   return MACRODOWN(D(RCTL), T(B), U(RCTL), D(LSFT), T(4), END);
    case T_NEW:   return MACRODOWN(D(RCTL), T(B), U(RCTL), D(LSFT), T(SCLN), U(LSFT), T(N), T(E), T(W), T(SPACE), T(MINS), T(S), T(SPACE), END);
    case T_CHSE:  return MACRODOWN(D(RCTL), T(B), U(RCTL), T(S), END);
    case T_PREV:  return MACRODOWN(D(RCTL), T(B), U(RCTL), D(LSFT), T(9), U(LSFT),  END);
    case T_NEXT:  return MACRODOWN(D(RCTL), T(B), U(RCTL), D(LSFT), T(0), U(LSFT),  END);
    case T_RSZE:  return MACRODOWN(D(RCTL), T(B), U(RCTL), T(Z), END);
    case T_SPLT:  return MACRODOWN(D(RCTL), T(B), U(RCTL), T(MINS), END);
    case T_RTE:   return MACRODOWN(D(RCTL), T(B), T(O), U(RCTL), END);
    case T_LAY:   return MACRODOWN(D(RCTL), T(B), U(RCTL), T(SPACE), END);
    case T_COPY:  return MACRODOWN(D(RCTL), T(B), U(RCTL), T(ENT), END);
  }
  return MACRO_NONE;
};

LEADER_EXTERNS();

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (quote_timer) {
      quote_timer = 0;
      switch (keycode) {
        case LT_A:
        case KC_E:
        case KC_I:
        case KC_O:
        case KC_U:
          register_code(KC_RALT);
          register_code(KC_E);
          unregister_code(KC_E);
          unregister_code(KC_RALT);
          break;
        case KC_QUOT:
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          break;
      }
    }
    uint8_t f_esc_shift_mask = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
    if (!f_esc_shift_mask && keycode == KC_QUOT) {
      quote_timer = timer_read();
      return false;
    }
  }

  return true;
}

uint8_t layer_was;
void matrix_scan_user(void) {
  if (quote_timer && timer_elapsed(quote_timer) > TAPPING_TERM) {
    quote_timer = 0;
    register_code(KC_QUOT);
    unregister_code(KC_QUOT);
  }

  uint8_t layer = biton32(layer_state);
  if (layer != layer_was) {
    clear_keyboard();
    layer_was = layer;
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    /* `c` activates cursor layer */
    SEQ_ONE_KEY(KC_C) {
      layer_on(_AR);
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
      layer_on(_MO);
    }
    /* `h` activates hardware layer */
    SEQ_ONE_KEY(KC_H) {
      layer_on(_HW);
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
      layer_on(_MO);
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
