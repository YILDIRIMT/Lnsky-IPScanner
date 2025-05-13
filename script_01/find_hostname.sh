#!/bin/bash
timeout 0.1 fping -c1 "$1" 2>/dev/null | awk '{print $6}'
