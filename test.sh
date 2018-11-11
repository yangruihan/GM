#!/usr/bin/env bash

bash build_release.sh $* \
&& ./bin/Test/GM_test
