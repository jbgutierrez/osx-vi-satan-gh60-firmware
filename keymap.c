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
#define CK_PASTE LGUI(KC_V)
#define CK_COPY LGUI(KC_C)
#define CK_CUT LGUI(KC_X)
#define CK_UNDO LGUI(KC_Z)
#define CK_WORD LALT(KC_RGHT)
#define CK_BWORD LALT(KC_LEFT)

enum key_id {
  NONE = 0,
  L_BSE,

  F_LSFT,
  F_RSFT,

  // Arrow
  C_VBLQ,

  // Window
  W_CENT,
  W_DOWN,
  W_LEFT,
  W_MAX,
  W_RGHT,
  W_TOGGLE,
  W_UP,

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
   * |Esc    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Art |Gui |      Space            |Gui |Art |Ctrl|Lead |
   * `-----------------------------------------------------------'
   */
[_BA] = KEYMAP(
  KC_GRV          , KC_1          , KC_2    , KC_3  , KC_4 , KC_5          , KC_6 , KC_7     , KC_8 , KC_9    , KC_0        , KC_MINS , KC_EQL    , KC_BSPC     , \
  LT(_WN, KC_TAB) , KC_Q          , KC_W    , KC_E  , KC_R , LT(_TM, KC_T) , KC_Y , KC_U     , KC_I , KC_O    , KC_P        , KC_LBRC , KC_RBRC   , KC_BSLS     , \
  LT(_MO, KC_ESC) , LT(_AR, KC_A) , KC_S    , KC_D  , KC_F , KC_G          , KC_H , KC_J     , KC_K , KC_L    , TD(TD_SCLN) , KC_QUOT , /*        , */KC_ENT    , \
  F(F_LSFT)       , /*            , */KC_Z  , KC_X  , KC_C , KC_V          , KC_B , KC_N     , KC_M , KC_COMM , KC_DOT      , KC_SLSH , /*        , */F(F_RSFT) , \
  KC_LCTL         , KC_LALT       , KC_LGUI , /*    ,      ,               ,      , */KC_SPC , /*   ,         , */ KC_RGUI  , KC_RALT , KC_RCTL   , KC_LEAD)    ,

/* Keymap _AR: Arrow Layer */
[_AR] = KEYMAP(
  _______  , _______ , _______   , _______ , KC_END  , _______   , _______  , _______   , _______ , _______ , KC_HOME    , _______ , _______ , _______   , \
  _______  , _______ , CK_WORD   , KC_END  , _______ , _______   , CK_COPY  , KC_PGUP   , KC_INS  , _______ , CK_PASTE   , _______ , _______ , _______   , \
  F(L_BSE) , KC_HOME , _______   , KC_PGDN , _______ , _______   , KC_LEFT  , KC_DOWN   , KC_UP   , KC_RGHT , _______    , _______ , /*      , */_______ , \
  _______  , /*      , */CK_UNDO , KC_DEL  , CK_CUT  , F(C_VBLQ) , CK_BWORD , _______   , _______ , _______ , _______    , _______ , /*      , */_______ , \
  _______  , _______ , _______   , /*      ,         ,           ,          , */_______ , /*      ,         , */ _______ , _______ , _______ , _______)  ,

/* Keymap _MO: Media and Mouse Layer */
[_MO] = KEYMAP(
  _______  , KC_F14  , KC_F15     , _______ , _______ , _______ , _______ , KC_MPRV   , KC_MPLY , KC_MNXT , KC_MUTE    , KC_VOLD , KC_VOLU , _______    , \
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , _______ , _______    , \
  F(L_BSE) , _______ , _______    , KC_BTN1 , KC_BTN2 , _______ , KC_MS_L , KC_MS_U   , KC_MS_U , KC_MS_R , _______    , _______ , /*      , */ _______ , \
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
  _______ , _______ , _______    , _______ , _______   , _______ , _______   , _______     , _______  , _______     , _______    , _______ , _______ , _______   , \
  _______ , _______ , _______    , _______ , _______   , _______ , _______   , _______     , _______  , F(W_TOGGLE) , _______    , _______ , _______ , _______   , \
  F(L_BSE), _______ , _______    , KC_F11  , F(W_MAX)  , _______ , F(W_LEFT) , F(W_DOWN)   , F(W_UP)  , F(W_RGHT)   , _______    , _______ , /*      , */_______ , \
  _______ , /*      , */ _______ , _______ , F(W_CENT) , _______ , _______   , F(W_TOGGLE) , F(W_MAX) , _______     , _______    , _______ , /*      , */_______ , \
  _______ , _______ , _______    , /*      ,           ,         ,           , */_______   , /*       ,             , */ _______ , _______ , _______ , _______)  ,

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
  if (state->count > 2) {
    TAP_ONCE(KC_1);
    state->count = 0;
    return;
  }

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
}

const qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCLN] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_LBRC] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_RBRC] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_GRV]  = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
};

const uint16_t PROGMEM fn_actions[] = {
  [L_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS),

  [F_LSFT] = ACTION_MODS_ONESHOT(MOD_LSFT),
  [F_RSFT] = ACTION_MODS_ONESHOT(MOD_RSFT),
  [C_VBLQ] = ACTION_FUNCTION(C_VBLQ),

  // Window
  [W_CENT]   = ACTION_MODS_KEY(MOD_LGUI | MOD_LALT, KC_C),
  [W_DOWN]   = ACTION_MODS_KEY(MOD_LGUI | MOD_LALT, KC_DOWN),
  [W_LEFT]   = ACTION_MODS_KEY(MOD_LGUI | MOD_LALT, KC_LEFT),
  [W_MAX]    = ACTION_MODS_KEY(MOD_LGUI | MOD_LALT, KC_F),
  [W_RGHT]   = ACTION_MODS_KEY(MOD_LGUI | MOD_LALT, KC_RGHT),
  [W_TOGGLE] = ACTION_MODS_KEY(MOD_LGUI, KC_TAB),
  [W_UP]     = ACTION_MODS_KEY(MOD_LGUI | MOD_LALT, KC_UP),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case C_VBLQ:
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


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case 0: return MACRODOWN(TYPE(KC_RSFT), END);

    case KF_1 ... KF_11: return ang_handle_kf(record, id);

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
