#!/usr/bin/env python

#
# Linker script for Ducky
#

(
  0x00000000,
  ( '.evt', [ r'\.evt' ]),

  0x00020000,
  ( '.text.boot', [ r'\.text\.boot'              ]),

  ( '.text',      [ r'\.text'                    ]),
  ( '.bootstack', [ r'\.bootstack'               ]),
  ( '.rodata',    [ r'\.rodata', r'\.rodata\..*', r'\.data\..*\.ro' ]),
  ( '.data',      [ r'\.data',   r'\.data\..*'   ]),
  ( '.bss',       [ r'\.bss'                     ]),

  0x00090000,  # Has to match settings from mpconfigport.h
  ( '.stack',     [ r'\.stack'                   ]),
  ( '.heap',      [ r'\.heap'                    ])
)
