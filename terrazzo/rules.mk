# MCU name
MCU = STM32F411

# This file intentionally left blank
#BOARD = GENERIC_STM32_F072XB
BOARD = BLACKPILL_STM32_F401

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
LED_MATRIX_ENABLE = yes
LED_MATRIX_DRIVER = IS31FL3731
#ENCODER_ENABLE = yes
WPM_ENABLE = yes
