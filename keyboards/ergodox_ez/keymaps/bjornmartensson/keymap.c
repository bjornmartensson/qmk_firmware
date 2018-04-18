#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

/* Custom keycodes */
enum {
  CT_LBP,
  CT_RBP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | Hyper|           | Meh  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |A/Win |S/Shft|D/Ctrl|F/Alt |   G  |------|           |------|   H  |J/Alt |K/Ctrl|L/Shft|   ;  |   '    |
 * |--------+------+------+------+------+------|  (   |           |   )  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |  [ { |           | } ]  |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |CapsL |   `  | App  | Esc  |  Tab |                                       | Space| Enter|   [  |   ]  |    \   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |A+S+Ta| A+Tab|       | PgUp |  Up  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Win  |C+S+Ta| C+Tab|       | Left | Down | Right|
 *                                 |------|------|------|       |------|------|------|            
 *                                 | Shift| Ctrl | Alt  |       | PgDn | Home | End  |
 *                                 `--------------------'       `----------------------'
 *   Design considerations:
 *   - Arrow key cluster with other movement keys: pgUp, PgDn, Home, End.
 *   - Dedicated key for  ALT+TAB, ALT+SHIFT+TAB, CTRL+TAB, CTRL+SHIFT+TAB for quick window / tab switching.
 *   - LShift / RShift on the outer sides could be remapped to something more useful.
 *   - Same for the [] on the right bottom.
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP_80(  // layer 0 : default
        // left hand
        KC_EQL , KC_1        , KC_2           , KC_3         , KC_4         , KC_5  , ALL_T(KC_NO)  , 
        KC_DELT, KC_Q        , KC_W           , KC_E         , KC_R         , KC_T  , TG(SYMB)      , 
        KC_BSPC, GUI_T(KC_A) , SFT_T(KC_S)    , CTL_T(KC_D)  , ALT_T(KC_F)  , KC_G  , 
        KC_LSFT, KC_Z        , KC_X           , KC_C         , KC_V         , KC_B  , TD(CT_LBP)    , 
        KC_CAPS, KC_GRV      , KC_APP         , KC_ESC       , KC_TAB       , 
                                                       LALT(S(KC_TAB)), LALT(KC_TAB),
                                              KC_LGUI, LCTL(S(KC_TAB)), LCTL(KC_TAB),
                                              KC_LSFT, KC_LCTL        , KC_LALT,
        // right hand
             MEH_T(KC_NO) , KC_6         , KC_7         , KC_8         , KC_9         , KC_0    , KC_MINS  , 
             TG(MDIA)     , KC_Y         , KC_U         , KC_I         , KC_O         , KC_P    , KC_SLSH  , 
                            KC_H         , ALGR_T(KC_J) , RCTL_T(KC_K) , RSFT_T(KC_L) , KC_SCLN , KC_QUOT  , 
             TD(CT_RBP)   , KC_N         , KC_M         , KC_COMM      , KC_DOT       , KC_SLSH , KC_RSFT  , 
                                           KC_SPC       , KC_ENT       , KC_LBRC      , KC_RBRC , KC_BSLASH, 
             KC_PGUP, KC_UP,
             KC_LEFT,KC_DOWN, KC_RIGHT,
             KC_PGDN,KC_HOME, KC_END
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |------|------|------|       |------|------|------|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP_80(
       // left hand
       M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+----------.
 *                                 |      |      |      |       |      |      |          |
 *                                 |------|------|------|       |------|------|----------|
 *                                 |      |      |      |       |      |      |BrwserBack|
 *                                 `--------------------'       `------------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP_80(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
								  KC_TRNS, KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

// TODO Can this be removed?
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

// TODO Remove this.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

static void
_td_brackets_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->keycode == TD(CT_LBP))
      register_code16 (S(KC_9));
    else
      register_code16 (S(KC_0));
  } else if (state->count == 2) {
    if (state->keycode == TD(CT_LBP))
      register_code16 (KC_MINUS);
    else
      register_code16 (KC_EQUAL);
  } else if (state->count == 3) {
    if (state->keycode == TD(CT_LBP))
      register_code16 (S(KC_MINUS));
    else
      register_code16 (S(KC_EQUAL));
  }
}

static void
_td_brackets_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->keycode == TD(CT_LBP))
      unregister_code16 (S(KC_9));
    else
      unregister_code16 (S(KC_0));
  } else if (state->count == 2) {
    if (state->keycode == TD(CT_LBP))
      unregister_code16 (KC_MINUS);
    else
      unregister_code16 (KC_EQUAL);
  } else if (state->count == 3) {
    if (state->keycode == TD(CT_LBP))
      unregister_code16 (S(KC_MINUS));
    else
      unregister_code16 (S(KC_EQUAL));
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_LBP] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, _td_brackets_finished, _td_brackets_reset)
  ,[CT_RBP] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, _td_brackets_finished, _td_brackets_reset)
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
