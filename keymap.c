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

enum layers {
  _BA,
  _AR,
  _MO,
  _WN,
  _NU,
  _HW,
  HHKB,
};

#define _______ KC_TRNS

#define A_BSPC LALT(KC_BSPC)
#define A_BWORD LALT(KC_LEFT)
#define A_FIND LGUI(KC_F)
#define A_FNEXT LGUI(KC_G)
#define A_WORD LALT(KC_RGHT)
#define A_END LGUI(KC_RGHT)
#define A_START LGUI(KC_LEFT)

#define W_BLFT LSFT(LCTL(LGUI(KC_LEFT)))
#define W_BRGT LSFT(LCTL(LGUI(KC_RIGHT)))
#define W_CALL LGUI(LALT(KC_W))
#define W_CENT LGUI(LALT(KC_C))
#define W_DOWN LGUI(LALT(KC_DOWN))
#define W_EXPO LCTL(KC_UP)
#define W_LEFT LGUI(LALT(KC_LEFT))
#define W_MAX LGUI(LALT(KC_F))
#define W_NEXT LCAG(KC_RGHT)
#define W_PREV LCAG(KC_LEFT)
#define W_RGHT LGUI(LALT(KC_RGHT))
#define W_TLFT LGUI(LCTL(KC_LEFT))
#define W_TOGGLE LGUI(KC_TAB)
#define W_TRGT LGUI(LCTL(KC_RIGHT))
#define W_UP LGUI(LALT(KC_UP))
#define W_WIND LCTL(KC_DOWN)

#define LT_SPC LT(_AR, KC_SPC)
#define LT_ESC LT(_WN, KC_ESC)
#define LT_1 LT(_NU, KC_1)

enum key_id {
  NONE = 0,
  L_BSE,

  C_VMOD,

  // Tap dancing definintions
  TD_LGUI,
  TD_RGUI,
  TD_RALT,
  TD_CAPS,
};

uint16_t quot_timer = 0;
uint16_t scln_timer = 0;
bool spanish_detection = true;

#define TAP_ONE(code) register_code(code); unregister_code(code)
#define TAP_TWO(code1, code2) register_code(code1); register_code(code2); unregister_code(code2); unregister_code(code1);
#define TAP_THREE(code1, code2, code3) register_code(code1); register_code(code2); register_code(code3); unregister_code(code3); unregister_code(code2); unregister_code(code1);
#define TAP_HYPR(code) register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_LSFT); register_code(KC_LGUI); register_code(code); unregister_code(code); unregister_code(KC_LGUI); unregister_code(KC_LSFT); unregister_code(KC_LALT); unregister_code(KC_LCTL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BA: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc!| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  `| \ |
   * |-----------------------------------------------------------|
   * |Tab! |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Back |
   * |-----------------------------------------------------------|
   * |Ctrl!  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Shift|Fn0|
   * |-----------------------------------------------------------|
   * |Ctrl|Alt |Gui!|      Space            |Gui  |Alt|Ctrl|Fn0  |
   * `-----------------------------------------------------------'
   */
  [_BA] = KEYMAP_HHKB(
      LT_ESC      , LT_1    , KC_2        , KC_3 , KC_4 , KC_5 , KC_6 , KC_7     , KC_8 , KC_9    , KC_0    , KC_MINS        , KC_EQL      , KC_BSLS    , KC_GRV     , \
      KC_TAB      , KC_Q    , KC_W        , KC_E , KC_R , KC_T , KC_Y , KC_U     , KC_I , KC_O    , KC_P    , KC_LBRC        , KC_RBRC     , /*         , */ KC_BSPC , \
      TD(TD_CAPS) , KC_A    , KC_S        , KC_D , KC_F , KC_G , KC_H , KC_J     , KC_K , KC_L    , KC_SCLN , KC_QUOT        , /*          ,            , */ KC_ENT  , \
      KC_LSFT     , /*      , */KC_Z      , KC_X , KC_C , KC_V , KC_B , KC_N     , KC_M , KC_COMM , KC_DOT  , KC_SLSH        , /*          , */ KC_RSFT , MO(HHKB)   , \
      KC_LCTL     , KC_LALT , TD(TD_LGUI) , /*   ,      ,      ,      , */LT_SPC , /*   ,         ,         , */ TD(TD_RGUI) , TD(TD_RALT) , KC_RCTL    , KC_RCTL)  ,


  /* Keymap _AR: Arrow Layer */
  [_AR] = KEYMAP_HHKB(
      F(L_BSE) , _______ , _______   , _______ , KC_END  , _______   , KC_HOME , _______   , _______ , _______ , KC_HOME , _______    , _______ , _______  , _______    , \
      _______  , _______ , A_WORD    , A_END   , _______ , _______   , _______ , KC_PGUP   , KC_INS  , _______ , _______ , _______    , _______ , /*       , */ A_BSPC  , \
      _______  , A_START , _______   , KC_PGDN , _______ , _______   , KC_LEFT , KC_DOWN   , KC_UP   , KC_RGHT , _______ , _______    , /*      ,          , */ _______ , \
      _______  , /*      , */_______ , KC_DEL  , _______ , F(C_VMOD) , A_BWORD , A_FNEXT   , _______ , _______ , _______ , A_FIND     , /*      , */ KC_UP , _______    , \
      _______ , _______  , _______   , /*      ,         ,           ,         , */_______ , /*      ,         ,         , */ _______ , KC_LEFT , KC_DOWN  , KC_RGHT)   ,

  /* Keymap _MO: Media and Mouse Layer */
  [_MO] = KEYMAP_HHKB(
      F(L_BSE) , KC_F14  , KC_F15     , _______ , _______ , _______ , _______ , KC_MPRV   , KC_MPLY , KC_MNXT , KC_MUTE , KC_VOLD    , KC_VOLU , _______    , _______    , \
      _______  , _______ , _______    , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______ , _______    , _______ , /*         , */ _______ , \
      _______  , _______ , _______    , KC_BTN1 , KC_BTN2 , _______ , KC_MS_L , KC_MS_D   , KC_MS_U , KC_MS_R , _______ , _______    , /*      ,            , */ _______ , \
      KC_MS_U  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______ , _______    , /*      , */ KC_MS_U , _______    , \
      KC_MS_L , KC_MS_D  , KC_MS_R    , /*      ,         ,         ,         , */KC_MPLY , /*      ,         ,         , */ _______ , KC_MS_L , KC_MS_D    , KC_MS_R)   ,

  /* Keymap _WN: Windows Layer */
  [_WN] = KEYMAP_HHKB(
      _______  , W_PREV  , W_NEXT     , _______ , _______ , _______ , _______ , _______   , _______ , _______  , _______ , _______    , _______ , _______   , _______    , \
      _______  , W_CALL  , W_WIND     , W_EXPO  , _______ , W_TOGGLE, _______ , W_TLFT    , _______ , W_TRGT   , _______ , _______    , _______ , /*        , */ _______ , \
      _______  , _______ , _______    , KC_F11  , W_MAX   , _______ , W_LEFT  , W_DOWN    , W_UP    , W_RGHT   , _______ , _______    , /*      ,           , */ _______ , \
      _______  , /*      , */ _______ , _______ , W_CENT  , _______ , _______ , _______   , W_BLFT  , _______  , W_BRGT  , _______    , /*      , */_______ , _______    , \
      _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*      ,          ,         , */ _______ , _______ , _______   , _______)   ,

  /* Keymap _NU: Numpad Layer */
  [_NU] = KEYMAP_HHKB(
      F(L_BSE) , _______ , _______    , _______ , _______ , _______ , _______ , KC_7      , KC_8 , KC_9    , KC_0  , _______    , _______ , _______ , _______    , \
      _______  , _______ , _______    , _______ , _______ , _______ , _______ , KC_4      , KC_5 , KC_6    , _______ , _______    , _______ , /*      , */ _______ , \
      _______  , _______ , _______    , _______ , _______ , _______ , _______ , KC_1      , KC_2 , KC_3    , _______ , _______    , /*      ,         , */ _______ , \
      _______  , /*      , */ _______ , _______ , _______ , _______ , _______ , _______   , KC_0 , _______ , _______ , _______    , _______ , /*      , */ _______ , \
      _______  , _______ , _______    , /*      ,         ,         ,         , */_______ , /*   ,         ,         , */ _______ , _______ , _______ , _______)   ,

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

void on_lgui_tap_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) { register_code(KC_LGUI); }
}

void on_lgui_tap_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
  uint8_t mask = get_mods() & (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI));
  if (mask) {
    unregister_code(KC_LGUI);
  } else {
    keyevent_t event = { pressed: true };
    keyrecord_t record = { event: event };
    process_leader(KC_LEAD, &record);
  }
};

void on_rgui_tap_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) {
    register_code(KC_RGUI);
  } else {
    TAP_TWO(KC_LCTL, KC_B);
    TAP_ONE(state->count > 1 ? KC_Z : KC_S);
  }
}

void on_rgui_tap_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_RGUI);
}

void on_ralt_tap_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) {
    unregister_code(KC_RALT);
  } else {
    TAP_TWO(KC_LCTL, KC_B);
    SEND_STRING(":new -s ");
  }
}

void on_ralt_tap_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) { register_code(KC_RALT); }
}

void on_caps_tap_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
  register_code(state->pressed   ? KC_LCTL :
      state->count > 1 ? KC_CAPS : KC_ESC);
}

void on_caps_tap_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_LCTL);
  unregister_code(KC_CAPS);
  unregister_code(KC_ESC);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_lgui_tap_dance_finished_fn, on_lgui_tap_dance_reset_fn),
  [TD_RGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_rgui_tap_dance_finished_fn, on_rgui_tap_dance_reset_fn),
  [TD_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_ralt_tap_dance_finished_fn, on_ralt_tap_dance_reset_fn),
  [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_caps_tap_dance_finished_fn, on_caps_tap_dance_reset_fn),
};

const uint16_t PROGMEM fn_actions[] = {
  [L_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS),
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

LEADER_EXTERNS();

void send_alt(uint16_t keycode) {
  bool caps_lock = host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK);
  uint8_t shiftmask = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
  del_mods(shiftmask);
  if (caps_lock) TAP_ONE(KC_CAPS);
  TAP_TWO(KC_RALT, keycode);
  if (caps_lock) TAP_ONE(KC_CAPS);
  set_mods(shiftmask);
}

bool process_spanish_chording(uint16_t keycode, keyrecord_t *record) {
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

bool sticky_leading = false;
uint16_t pending_sticky = 0;
bool process_sticky(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    bool sticky_pressed = keycode == KC_LSFT || keycode == KC_RSFT;
    if (!sticky_leading && sticky_pressed) {
      sticky_leading = true;
      pending_sticky = timer_read();
      return true;
    }
    if (sticky_leading) {
      sticky_leading = false;
      uint16_t sticky = timer_elapsed(pending_sticky) < 3 * LEADER_TIMEOUT;
      uint8_t shiftmask = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
      if (!shiftmask && sticky) {
        TAP_HYPR(keycode);
        return false;
      }
    }
  }
  return true;
}

void process_spanish_chording_pending(void) {
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
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool pending =
    process_spanish_chording(keycode, record) &&
    process_sticky(keycode, record);
  return pending;
}

uint8_t layer_was;
void matrix_scan_user(void) {
  process_spanish_chording_pending();

  uint8_t layer = biton32(layer_state);
  if (layer != layer_was) {
    clear_keyboard();
    layer_was = layer;
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    /* `d` open debug panel */
    SEQ_ONE_KEY(KC_D) {
      TAP_THREE(KC_LGUI, KC_LALT, KC_I);
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
    /* `n` activates numpad layer */
    SEQ_ONE_KEY(KC_N) {
      layer_on(_NU);
    }
#ifdef PASSWORD
    PASSWORD_SEQUENCE { SEND_STRING (PASSWORD); }
#endif
#ifdef PASSWORD2
    PASSWORD2_SEQUENCE { SEND_STRING (PASSWORD2); }
#endif
#ifdef PASSWORD3
    PASSWORD3_SEQUENCE { SEND_STRING (PASSWORD3); }
#endif
    /* `q` close all windows of current application */
    SEQ_ONE_KEY(KC_Q) {
      TAP_THREE(KC_LGUI, KC_LALT, KC_W);
    }
    /* `esc` moves focus to the menu bar */
    SEQ_ONE_KEY(LT_ESC) {
      TAP_TWO(KC_LCTL, KC_F2);
    }
    /* `t` taps on current mouse position */
    SEQ_ONE_KEY(KC_T) {
      mousekey_on(KC_BTN1);
      mousekey_send();
      mousekey_off(KC_BTN1);
      mousekey_send();
    }
    /* `u` types username */
    SEQ_ONE_KEY (KC_U) {
      SEND_STRING (USERNAME);
    }
    SEQ_ONE_KEY(TD_RALT) {
      spanish_detection = !spanish_detection;
    }
  }
}
