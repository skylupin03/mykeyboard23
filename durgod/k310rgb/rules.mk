# Default to K310 variant, since it will also work on a K320
# DEFAULT_FOLDER=0skyupin/durgod/k310rgb     -last

# MCU name (Actually F070, but close enough)
MCU = STM32F072
#MCU = STM32F401

# This file intentionally left blank
#BOARD = GENERIC_STM32_F072XB
BOARD = DURGOD_STM32_F070
#BOARD = BLACKPILL_STM32_F401
#BOAED = GENERIC_STM32_F401XC
#BOAED = ST_NUCLEO64_F401RE
#BOAED = TAUCHEF_STM32_F401		# 삭제해도 됨 기본클럭 및 PLL설정이 8M로 되어 있음

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options (change yes to no to disable)
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       	# Enable keyboard backlight functionality
#BACKLIGHT_DRIVER = pwm	     	# pwm, software, custom or no
LED_MATRIX_ENABLE = no				#
#LED_MATRIX_DRIVER = IS31FL3731		#
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow (WS2811, WS2812, WS2812B, WS2812C, SK6812, SK6812MINI, SK6805, APA102)
RGB_MATRIX_ENABLE = yes			#
RGB_MATRIX_DRIVER = WS2812		# IS31FL3731, 3733, 3737, WS2812등등 (WS2811, WS2812, WS2812B, WS2812C, SK6812, SK6812MINI, SK6805, APA102)
WS2812_DRIVER = spi				# bitbang, spi(circular buffer issue), pwm(too much access, Noise도 심한듯)

AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = yes

LAYOUTS = fullsize_ansi fullsize_iso

DYNAMIC_MACRO_ENABLE = yes
WPM_ENABLE = yes

TAP_DANCE_ENABLE = yes      # Tappa Dance

ENCODER_ENABLE = yes        # Enable Encoder
ENCODER_MAP_ENABLE = yes
#DIP_SWITCH_ENABLE = yes	# DIP Switch

# Use RAM (fake EEPROM, transient) instead of real EEPROM
##EEPROM_DRIVER = transient

OLED_ENABLE = yes			# +5568(0x15C0)byte
#OLED_DRIVER = SSD1306		# default값이라 필요없는듯

#간간히 OLED가 동작안하는 문제 해결?
#ISSI_ENABLE = yes			# If the I2C pullup resistors aren't install this must be disabled

#WATCHDOG_ENABLE = no		# Resets keyboard if matrix_scan isn't run every 250ms//

#AUTO_SHIFT_ENABLE = yes
#KEY_LOCK_ENABLE = yes
#CAPS_WORD_ENABLE = yes
#LEADER_ENABLE = yes

#JOYSTICK_ENABLE = yes		# #define HAL_USE_ADC TRUE(halconf.h) / STM32_ADC_USE_ADCx (mcuconf.h)
#JOYSTICK_DRIVER = digital
#JOYSTICK_DRIVER = analog
#SRC += analog.c

DEBUG_MATRIX_SCAN_RATE_ENABLE = no
DEBUG_EEPROM_OUTPUT_ENABLE = yes
WEAR_LEVELING_DEBUG_OUTPUT_ENABLE = yes
