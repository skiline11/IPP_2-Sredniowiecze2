#!/bin/bash

read line

echo "END_TURN"

read line

sleep 1.5

echo "Crashing AI..." >&2
kill -9 $$
