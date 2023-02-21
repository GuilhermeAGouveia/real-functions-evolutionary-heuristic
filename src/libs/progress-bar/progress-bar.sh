#!/usr/bin/env bash

progress-bar() {
  local columns
  local space_available
  local space_reserved
  local space_initial
  space_reserved=6   # reserved width for the percentage value
  space_initial=6    # initial space before the progress bar
  percent=${1}      # current value (0-100)
  columns=$(tput cols)
  space_available=$(( columns-(space_reserved + space_initial) ))


  space_initial() { for (( space=0; space<space_initial ; space=space+1 )); do printf " "; done }
  already_done() { for ((done=0; done<((percent * space_available) / 100) ; done=done+1 )); do printf "▇"; done }
  remaining() { for (( remain=((percent * space_available) / 100) ; remain<(space_available) ; remain=remain+1 )); do printf "_"; done }
  percentage() { printf "| %s%%" $(( percent )); }
  clean_line() { printf "\r"; }

  space_initial; already_done; remaining; percentage
      #seep "$SLEEP_DURATION"
    
}
