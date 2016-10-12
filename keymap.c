#ifdef SATAN_PCB
#include "satan.h"
#endif

#ifdef HASU_PCB
#include "quantum.h"
#define KEYMAP_HHKB(                                                           \
    K31, K30, K00, K10, K11, K20, K21, K40, K41, K60, K61, K70, K71, K50, K51, \
    K32, K01, K02, K13, K12, K23, K22, K42, K43, K62, K63, K73, K72, K52,      \
    K33, K04, K03, K14, K15, K24, K25, K45, K44, K65, K64, K74, K53,           \
    K34, K05, K06, K07, K16, K17, K26, K46, K66, K76, K75, K55, K54,           \
    XX1, K35, K36,           K37,                K57, K56, XX2, XX3            \
)                                                                              \
{                                                                              \
    { K00, K01, K02, K03, K04, K05, K06, K07   },                              \
    { K10, K11, K12, K13, K14, K15, K16, K17   },                              \
    { K20, K21, K22, K23, K24, K25, K26, KC_NO },                              \
    { K30, K31, K32, K33, K34, K35, K36, K37   },                              \
    { K40, K41, K42, K43, K44, K45, K46, KC_NO },                              \
    { K50, K51, K52, K53, K54, K55, K56, K57   },                              \
    { K60, K61, K62, K63, K64, K65, K66, KC_NO },                              \
    { K70, K71, K72, K73, K74, K75, K76, KC_NO }                               \
}
#endif

#include "mousekey.h"
#include "action_tapping.h"

#define _BA 0
#define _AR 1
#define _MO 2
#define _WN 3
#define _HW 4
#define _SY 5
#define HHKB 6

#define _______ KC_TRNS

#define A_BSPC LALT(KC_BSPC)
#define A_BWORD LALT(KC_LEFT)
#define A_FIND LGUI(KC_F)
#define A_FNEXT LGUI(KC_G)
#define A_WORD LALT(KC_RGHT)
#define A_END LGUI(KC_RGHT)
#define A_START LGUI(KC_LEFT)

#define W_CENT LGUI(LALT(KC_C))
#define W_DOWN LGUI(LALT(KC_DOWN))
#define W_LEFT LGUI(LALT(KC_LEFT))
#define W_MAX LGUI(LALT(KC_F))
#define W_RGHT LGUI(LALT(KC_RGHT))
#define W_TOGGLE LGUI(KC_TAB)
#define W_UP LGUI(LALT(KC_UP))
#define W_NEXT LCAG(KC_RGHT)
#define W_PREV LCAG(KC_LEFT)
#define W_EXPO LCTL(KC_UP)
#define W_WIND LCTL(KC_DOWN)
#define W_CALL LGUI(LALT(KC_W))

#define LT_SPC LT(_AR, KC_SPC)
#define LT_TAB LT(_WN, KC_TAB)
#define LT_CAPS LT(_SY, KC_CAPS)

#define T_CAPS CTL_T(KC_ESC)

enum key_id {
  NONE = 0,
  L_BSE,

  F_LSFT,
  F_RSFT,

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

  // Tap dancing definintions
  TD_ESC,
  TD_LGUI,
};

uint16_t kf_timers[12];
uint16_t quot_timer = 0;
uint16_t scln_timer = 0;
bool spanish_detection = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap _BA: (Base Layer) Default Layer
 * ,-----------------------------------------------------------.
 * |Esc!| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  `| \ |
 * |-----------------------------------------------------------|
 * |Tab! |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Back |
 * |-----------------------------------------------------------|
 * |Ctrl!  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
 * |-----------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
 * |-----------------------------------------------------------|
 * |Ctrl|Alt |Gui!|      Space            |Gui  |Alt|Ctrl|Fn0  |
 * `-----------------------------------------------------------'
 */
[_BA] = KEYMAP_HHKB(
  TD(TD_ESC) , M(KF_1) , M(KF_2)     , M(KF_3) , M(KF_4) , M(KF_5) , M(KF_6) , M(KF_7)  , M(KF_8) , M(KF_9) , M(KF_0) , M(KF_MINS) , M(KF_EQL) , KC_BSLS      , KC_GRV     , \
  LT_TAB     , KC_Q    , KC_W        , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U     , KC_I    , KC_O    , KC_P    , KC_LBRC    , KC_RBRC   , /*           , */ KC_BSPC , \
  T_CAPS     , KC_A    , KC_S        , KC_D    , KC_F    , KC_G    , KC_H    , KC_J     , KC_K    , KC_L    , KC_SCLN , KC_QUOT    , /*        ,              , */ KC_ENT  , \
  F(F_LSFT)  , /*      , */KC_Z      , KC_X    , KC_C    , KC_V    , KC_B    , KC_N     , KC_M    , KC_COMM , KC_DOT  , KC_SLSH    , /*        , */ F(F_RSFT) , MO(HHKB)   , \
  KC_LCTL    , KC_LALT , TD(TD_LGUI) , /*      ,         ,         ,         , */LT_SPC , /*      ,         ,         , */ KC_RALT , KC_RGUI   , KC_RCTL      , MO(HHKB))  ,


/* Keymap _AR: Arrow Layer */
[_AR] = KEYMAP_HHKB(
  F(L_BSE) , _______ , _______   , _______ , KC_END  , _______   , KC_HOME , _______   , _______ , _______ , KC_HOME , _______    , _______ , _______  , _______    , \
  _______  , _______ , A_WORD    , A_END   , _______ , _______   , _______ , KC_PGUP   , KC_INS  , _______ , _______ , _______    , _______ , /*       , */ A_BSPC  , \
  _______  , A_START , _______   , KC_PGDN , _______ , _______   , KC_LEFT , KC_DOWN   , KC_UP   , KC_RGHT , _______ , _______    , /*      ,          , */ _______ , \
  _______  , /*      , */_______ , KC_DEL  , _______ , F(C_VMOD) , A_BWORD , A_FNEXT   , _______ , _______ , _______ , A_FIND     , /*      , */ KC_UP , _______    , \
  _______  , _______ , _______   , /*      ,         ,           ,         , */_______ , /*      ,         ,         , */ _______ , KC_LEFT , KC_DOWN  , KC_RGHT)   ,

/* Keymap _MO: Media and Mouse Layer */
[_MO] = KEYMAP_HHKB(
  F(L_BSE) , KC_F14  , KC_F15     , _______ , _______ , _______ , _______ , KC_MPRV   , KC_MPLY , KC_MNXT , KC_MUTE , KC_VOLD    , KC_VOLU , _______    , _______    , \
  _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______ , _______    , _______ , /*         , */ _______ , \
  _______  , _______ , _______    , KC_BTN1 , KC_BTN2 , _______ , KC_MS_L , KC_MS_D   , KC_MS_U , KC_MS_R , _______ , _______    , /*      ,            , */ _______ , \
  _______  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______ , _______    , /*      , */ KC_MS_U , _______    , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */KC_MPLY , /*      ,         ,         , */ _______ , KC_MS_L , KC_MS_D    , KC_MS_R)   ,

/* Keymap _WN: Windows Layer */
[_WN] = KEYMAP_HHKB(
  F(L_BSE) , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______  , _______ , _______    , _______ , _______   , _______    , \
  _______  , W_CALL  , W_WIND     , W_EXPO  , _______ , _______ , _______ , _______   , _______ , W_TOGGLE , W_PREV  , _______    , _______ , /*        , */ _______ , \
  _______  , _______ , _______    , KC_F11  , W_MAX   , _______ , W_LEFT  , W_DOWN    , W_UP    , W_RGHT   , _______ , _______    , /*      ,           , */ _______ , \
  _______  , /*      , */ _______ , _______ , W_CENT  , _______ , _______ , W_NEXT    , _______ , _______  , _______ , _______    , /*      , */_______ , _______    , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,          ,         , */ _______ , _______ , _______   , _______)   ,

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
[_SY] = KEYMAP_HHKB(
  F(L_BSE) , KC_EXLM , KC_AT      , KC_HASH  , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR   , KC_ASTR , KC_LPRN , KC_RPRN , KC_UNDS    , KC_PLUS , KC_PIPE    , KC_TILD    , \
  _______  , KC_QUES , _______    , KC_EQUAL , _______ , _______ , KC_PERC , KC_UNDS   , _______ , KC_PIPE , KC_PLUS , KC_LBRC    , KC_RBRC , /*         , */ KC_DEL , \
  _______  , KC_AMPR , KC_DLR     , KC_LCBR  , KC_LPRN , _______ , KC_HASH , KC_RPRN   , KC_RCBR , _______ , KC_COLN , KC_DQUO    , /*      ,            , */ _______ , \
  _______  , /*      , */ _______ , _______  , KC_CIRC , _______ , KC_BSLS , KC_EXLM   , KC_MINS , KC_LABK , KC_RABK , KC_QUES    , /*      , */ _______ , _______    , \
  _______  , _______ , _______    , /*       ,         ,         ,         , */KC_PAST , /*      ,         ,         , */ _______ , _______ , _______    , _______)   ,

/* Keymap _HW: Hardware Layer */
[_HW] = KEYMAP_HHKB(
  F(L_BSE) , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , BL_TOGG , BL_INC     , BL_INC  , _______    , _______    , \
  _______  , _______ , _______    , _______ , RESET   , _______ , _______ , _______   , _______ , _______ , _______ , _______    , _______ , /*         , */ _______ , \
  _______  , _______ , _______    , DEBUG   , _______ , _______ , _______ , _______   , _______ , _______ , _______ , _______    , /*      ,            , */ _______ , \
  _______  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______ , _______    , /*      , */ _______ , _______    , \
  _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,         ,         , */ _______ , _______ , _______    , _______)   ,

/* Keymap HHKB: HHKB mode (HHKB Fn) */
[HHKB] = KEYMAP_HHKB(
  KC_PWR  , KC_F1   , KC_F2      , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7     , KC_F8   , KC_F9   , KC_F10  , KC_F11     , KC_F12  , KC_INS     , KC_DEL     , \
  KC_CAPS , _______ , _______    , _______ , _______ , _______ , _______ , _______   , KC_PSCR , KC_SLCK , KC_PAUS , KC_UP      , _______ , /*         , */ KC_BSPC , \
  _______ , KC_VOLD , KC_VOLU    , KC_MUTE , _______ , _______ , KC_PAST , KC_PSLS   , KC_HOME , KC_PGUP , KC_LEFT , KC_RGHT    , /*      ,            , */ KC_PENT , \
  _______ , /*      , */ _______ , _______ , _______ , _______ , _______ , KC_PPLS   , KC_PMNS , KC_END  , KC_PGDN , KC_DOWN    , /*      , */ _______ , _______    , \
  _______ , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,         ,         , */ _______ , _______ , _______    , _______)   ,
};

#define TAP_ONE(code) register_code(code); unregister_code(code)
#define TAP_TWO(code1, code2) register_code(code1); register_code(code2); unregister_code(code2); unregister_code(code1);
#define TAP_THREE(code1, code2, code3) register_code(code1); register_code(code2); register_code(code3); unregister_code(code3); unregister_code(code2); unregister_code(code1);

void esc_tap_dance_fn(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 2:
      TAP_TWO(KC_RSFT, KC_GRV);
      break;
    case 3:
      TAP_ONE(KC_GRV);
      break;
    default:
      TAP_ONE(KC_ESC);
      return;
  }
};

void on_lgui_tap_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) { register_code(KC_LGUI); }
}

void on_lgui_tap_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
  uint8_t guimask = get_mods() & (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI));
  if (guimask) {
    unregister_code(KC_LGUI);
  } else {
    keyevent_t event = { pressed: true };
    keyrecord_t record = { event: event };
    process_leader(KC_LEAD, &record);
  }
};

extern qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC]  = ACTION_TAP_DANCE_FN(esc_tap_dance_fn),
  [TD_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_lgui_tap_dance_finished_fn, on_lgui_tap_dance_reset_fn),
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
        uint8_t shiftmask = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
        if (shiftmask) {
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
    /* `tab` one shot modifier for tab */
    SEQ_ONE_KEY(LT_TAB) {
      TAP_TWO(KC_LGUI, KC_TAB);
    }
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
    /* `esc` moves focus to the menu bar */
    SEQ_ONE_KEY(TD(TD_ESC)) {
      TAP_TWO(KC_LCTL, KC_F2);
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
