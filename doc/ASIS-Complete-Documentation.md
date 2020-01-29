# ASIS Complete Documentation
**WIP**

## Constants

#### ASIS Constants (see asis.h)

#### Configuration Constants (see script_config.h)

## ASIS Instructions

## ASIS Packet

## ASIS System Functions

## ASIS User Functions

## LED indication
 - 2 rapid blinks followed by 1 second off = buffer overflow when building the script
 - 2 rapid blinks followed by 1 second on then 1 second off = buffer overflow when running the script (stack or memory)
 - regular blinks, frequency equals wait frequency = waiting
 - blink once followed by 3 second off = script finished successfully with an exit instruction