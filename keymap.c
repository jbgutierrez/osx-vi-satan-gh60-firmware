#include "satan.h"
#include "mousekey.h"
#include "action_tapping.h"

#define _BA 0
#define _AR 1
#define _MO 2
#define _WN 3
#define _HW 4
#define _SY 5

#define _______ KC_TRNS

#define B_LGUI GUI_T(KC_PAST)

#define A_BSPC LALT(KC_BSPC)
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

#define LT_SPC LT(_AR, KC_SPC)
#define LT_TAB LT(_WN, KC_TAB)

#define T_CAPS CTL_T(KC_ESC)

enum key_id {
  NONE = 0,
  L_BSE,

  F_LSFT,
  F_RSFT,

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

  // Tap dancing definintions
  TD_GRV,
  TD_LBRC,
  TD_RBRC,
  TD_SLSH,
  TD_MISS,
};

uint16_t kf_timers[12];
uint16_t quot_timer = 0;
uint16_t scln_timer = 0;
bool spanish_detection = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap _BA: (Base Layer) Default Layer
 * ,-----------------------------------------------------------.
 * |   `| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
 * |-----------------------------------------------------------|
 * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
 * |-----------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
 * |-----------------------------------------------------------|
 * |    |Alt |Gui |      Space            |Alt |Lead|    |     |
 * `-----------------------------------------------------------'
 */
[_BA] = KEYMAP_ANSI(
  TD(TD_GRV)  , M(KF_1) , M(KF_2) , M(KF_3) , M(KF_4) , M(KF_5) , M(KF_6) , M(KF_7)  , M(KF_8) , M(KF_9) , M(KF_0)    , M(KF_MINS)  , M(KF_EQL)   , KC_BSLS     , \
  LT_TAB      , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U     , KC_I    , KC_O    , KC_P       , TD(TD_LBRC) , TD(TD_RBRC) , KC_BSPC     , \
  T_CAPS      , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J     , KC_K    , KC_L    , KC_SCLN    , KC_QUOT     , /*          , */KC_ENT    , \
  F(F_LSFT)   , /*      , */KC_Z  , KC_X    , KC_C    , KC_V    , KC_B    , KC_N     , KC_M    , KC_COMM , KC_DOT     , TD(TD_SLSH) , /*          , */F(F_RSFT) , \
  TD(TD_MISS) , KC_LALT , B_LGUI  , /*      ,         ,         ,         , */LT_SPC , /*      ,         , */ KC_RALT , KC_LEAD     , _______     , _______)    ,


/* Keymap _AR: Arrow Layer */
[_AR] = KEYMAP_ANSI(
  _______  , _______ , _______   , _______ , A_END   , _______ , _______ , _______   , _______ , _______ , A_START    , _______ , _______ , _______   , \
  _______  , _______ , A_WORD    , KC_END  , _______ , _______ , _______ , KC_PGUP   , KC_INS  , _______ , A_PASTE    , _______ , _______ , A_BSPC    , \
  F(L_BSE) , _______ , KC_HOME   , KC_PGDN , _______ , _______ , KC_LEFT , KC_DOWN   , KC_UP   , KC_RGHT , _______    , _______ , /*      , */_______ , \
  _______  , /*      , */_______ , KC_DEL  , _______ , _______ , A_BWORD , A_FNEXT   , _______ , _______ , _______    , A_FIND  , /*      , */KC_UP   , \
  _______  , _______ , _______   , /*      ,         ,         ,         , */_______ , /*      ,         , */ _______ , KC_LEFT , KC_DOWN , KC_RGHT)  ,

/* Keymap _MO: Media and Mouse Layer */
[_MO] = KEYMAP_ANSI(
  _______  , KC_F14  , KC_F15     , _______ , _______ , _______ , _______ , KC_MPRV   , KC_MPLY , KC_MNXT , KC_MUTE    , KC_VOLD , KC_VOLU , _______    , \
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , _______ , _______    , \
  F(L_BSE) , _______ , _______    , KC_BTN1 , KC_BTN2 , _______ , KC_MS_L , KC_MS_D   , KC_MS_U , KC_MS_R , _______    , _______ , /*      , */ _______ , \
  _______  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , /*      , */ _______ , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */KC_MPLY , /*      ,         , */ _______ , _______ , _______ , _______)   ,

/* Keymap _WN: Windows Layer */
[_WN] = KEYMAP_ANSI(
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______  , _______    , _______ , _______ , _______   , \
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , W_TOGGLE , W_PREV     , _______ , _______ , _______   , \
  F(L_BSE) , _______ , _______    , KC_F11  , W_MAX   , _______ , W_LEFT  , W_DOWN    , W_UP    , W_RGHT   , _______    , _______ , /*      , */_______ , \
  _______  , /*      , */ _______ , _______ , W_CENT  , _______ , _______ , W_NEXT    , _______ , _______  , _______    , _______ , /*      , */_______ , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,          , */ _______ , _______ , _______ , _______)  ,

/* Keymap _SY: Symbols Layer
 * ,-----------------------------------------------------------.
 * |   ~| !|  @|  #|  $|  %|  ^|  &|  8|  (|  )|  _|  +|       |
 * |-----------------------------------------------------------|
 * |     |  ?|   |  =|   |   |  %|   |  _|  ||  +|  ]|   |     |
 * |-----------------------------------------------------------|
 * |       |  &|  $|  {|  (|   |  #|  )|  }|   |  :|  '|       |
 * |-----------------------------------------------------------|
 * |        |   |   |  ^|   |  \|  !|  -|  <|  >|  ?|          |
 * |-----------------------------------------------------------|
 * |    |    |    |                      *|     |    |    |    |
 * `-----------------------------------------------------------'
 */
[_SY] = KEYMAP_ANSI(
  KC_TILD  , KC_EXLM , KC_AT      , KC_HASH  , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR   , KC_ASTR , KC_LPRN , KC_RPRN    , KC_UNDS , KC_PLUS , KC_DEL    , \
  _______  , KC_QUES , _______    , KC_EQUAL , _______ , _______ , KC_PERC , KC_UNDS   , _______ , KC_PIPE , KC_PLUS    , KC_RBRC , _______ , _______   , \
  F(L_BSE) , KC_AMPR , KC_DLR     , KC_LCBR  , KC_LPRN , _______ , KC_HASH , KC_RPRN   , KC_RCBR , _______ , KC_COLN    , KC_DQUO , /*      , */_______ , \
  _______  , /*      , */ _______ , _______  , KC_CIRC , _______ , KC_BSLS , KC_EXLM   , KC_MINS , KC_LABK , KC_RABK    , KC_QUES , /*      , */_______ , \
  F(L_BSE) , _______ , _______    , /*       ,         ,         ,         , */KC_PAST , /*      ,         , */ _______ , _______ , _______ , _______)  ,

/* Keymap _HW: Hardware Layer */
[_HW] = KEYMAP_ANSI(
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , _______ , _______   , \
  _______  , _______ , _______    , _______ , RESET   , _______ , _______ , _______   , _______ , _______ , _______    , BL_DEC  , BL_INC  , BL_TOGG   , \
  F(L_BSE) , _______ , _______    , DEBUG   , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , /*      , */_______ , \
  _______  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______    , _______ , /*      , */_______ , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,         , */ _______ , _______ , _______ , _______)  ,
};

#define TAP_ONE(code) register_code(code); unregister_code(code)
#define TAP_TWO(code1, code2) register_code(code1); register_code(code2); unregister_code(code2); unregister_code(code1);
#define TAP_THREE(code1, code2, code3) register_code(code1); register_code(code2); register_code(code3); unregister_code(code3); unregister_code(code2); unregister_code(code1);

void shifted_tap_dance_fn(qk_tap_dance_state_t *state, void *user_data) {
  bool shifted = state->count == 2;
  uint8_t kc;
  switch(state->keycode) {
    case TD(TD_GRV)  : kc = KC_GRV; break;
    case TD(TD_LBRC) : kc = KC_LBRC; break;
    case TD(TD_RBRC) : kc = KC_RBRC; break;
    case TD(TD_SLSH) : kc = KC_SLSH; break;
    default: return;
  }

  if (shifted) {
    TAP_TWO(KC_RSFT, kc);
  } else {
    TAP_ONE(kc);
  }
};

void mission_control_tap_dance_fn(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
      TAP_TWO(KC_LCTL, KC_UP);
      break;
    case 2:
      TAP_TWO(KC_LCTL, KC_DOWN);
      break;
    default:
      TAP_ONE(KC_F11);
      return;
  }
};

extern qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GRV]  = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_LBRC] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_RBRC] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_SLSH] = ACTION_TAP_DANCE_FN(shifted_tap_dance_fn),
  [TD_MISS] = ACTION_TAP_DANCE_FN(mission_control_tap_dance_fn),
};

const uint16_t PROGMEM fn_actions[] = {
  [L_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS),

  [F_LSFT] = ACTION_MODS_ONESHOT(MOD_LSFT),
  [F_RSFT] = ACTION_MODS_ONESHOT(MOD_RSFT),
};

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

    TAP_ONE(kc);
  }
  return MACRO_NONE;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case 0: return MACRODOWN(TYPE(KC_RSFT), END);

    case KF_1 ... KF_EQL: return ang_handle_kf(record, id);
  }
  return MACRO_NONE;
};

LEADER_EXTERNS();

bool send_alt(uint16_t keycode) {
  bool caps_lock = host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK);
  uint8_t shiftmask = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
  del_mods(shiftmask);
  if (caps_lock) TAP_ONE(KC_CAPS);
  TAP_TWO(KC_RALT, keycode);
  if (caps_lock) TAP_ONE(KC_CAPS);
  set_mods(shiftmask);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!spanish_detection) { return true; }

  if (record->event.pressed) {
    uint8_t shiftmask = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
    if (quot_timer) {
      quot_timer = 0;
      switch (keycode) {
        case KC_A:
        case KC_E:
        case KC_I:
        case KC_O:
        case KC_U:
          send_alt(KC_E);
          break;
        case KC_QUOT:
          TAP_TWO(KC_RSFT, KC_QUOT);
          return false;
        default:
          TAP_ONE(KC_QUOT);
          break;
      }
    }
    if (!shiftmask && keycode == KC_QUOT) {
      quot_timer = timer_read();
      return false;
    }

    if (scln_timer) {
      scln_timer = 0;
      switch (keycode) {
        case KC_A:
        case KC_E:
        case KC_I:
        case KC_O:
        case KC_U:
          send_alt(KC_N);
          TAP_ONE(KC_N);
          break;
        case KC_SCLN:
          TAP_TWO(KC_RSFT, KC_SCLN);
          return false;
        default:
          TAP_ONE(KC_SCLN);
          break;
      }
    }
    if (!shiftmask && keycode == KC_SCLN) {
      scln_timer = timer_read();
      return false;
    }
  }

  return true;
}

uint8_t layer_was;
void matrix_scan_user(void) {
  if (spanish_detection) {
    if (quot_timer && timer_elapsed(quot_timer) > TAPPING_TERM) {
      quot_timer = 0;
      TAP_ONE(KC_QUOT);
    }

    if (scln_timer && timer_elapsed(scln_timer) > TAPPING_TERM) {
      scln_timer = 0;
      TAP_ONE(KC_SCLN);
    }
  }

  uint8_t layer = biton32(layer_state);
  if (layer != layer_was) {
    clear_keyboard();
    layer_was = layer;
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    /* `tab` toggles Caps Lock */
    SEQ_ONE_KEY(T_CAPS) {
      TAP_ONE(KC_CAPS);
    }
    /* `d` open debug panel */
    SEQ_ONE_KEY(KC_D) {
      TAP_THREE(KC_LGUI, KC_LALT, KC_I);
    }
    /* `c` activates arrow layer */
    SEQ_ONE_KEY(KC_A) {
      layer_on(_AR);
    }
    /* `h` activates hardware layer */
    SEQ_ONE_KEY(KC_H) {
      layer_on(_HW);
    }
    /* `k,space,space` toggles spanish detection mode */
    SEQ_THREE_KEYS (KC_K, KC_SPC, KC_SPC) {
     spanish_detection = !spanish_detection;
    }
    /* `l` locks screen */
    SEQ_ONE_KEY(KC_L) {
      TAP_THREE(KC_LGUI, KC_LALT, KC_MEDIA_EJECT);
    }
    /* `m` activates mouse and media layer */
    SEQ_ONE_KEY(KC_M) {
      layer_on(_MO);
    }
    /* `p` types password */
    PASSWORD_SEQUENCE {
      SEND_STRING (PASSWORD);
    }
    /* `q` close all windows of current application */
    SEQ_ONE_KEY(KC_Q) {
      TAP_THREE(KC_LGUI, KC_LALT, KC_W);
    }
    /* `s` saves screenshot */
    SEQ_ONE_KEY(KC_S) {
      TAP_THREE(KC_LGUI, KC_LSFT, KC_3);
    }
    /* `ss` saves screenshot of selected area */
    SEQ_TWO_KEYS(KC_S, KC_S) {
      TAP_THREE(KC_LGUI, KC_LSFT, KC_4);
    }
    /* `t` taps on current mouse position */
    SEQ_ONE_KEY(KC_T) {
      mousekey_on(KC_BTN1);
      mousekey_send();
      mousekey_off(KC_BTN1);
      mousekey_send();
    }
    /* `tn` creates new tmux session */
    SEQ_TWO_KEYS(KC_T,KC_N) {
      TAP_TWO(KC_RCTL, KC_B);
      SEND_STRING(":new -s ");
    }
    /* `u` types username */
    SEQ_ONE_KEY (KC_U) {
      SEND_STRING (USERNAME);
    }
    /* `w` activates window layer */
    SEQ_ONE_KEY(KC_W) {
      layer_on(_WN);
    }
  }
}
