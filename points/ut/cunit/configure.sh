#!/usr/bin/env bash

cunit_cflags=`pkg-config --short-errors --cflags cunit`
cunit_ldflags=`pkg-config --short-errors --libs cunit`

cat > config.mk << EOF
CUNIT_CFLAGS = ${cunit_cflags}
CUNIT_LDFLAGS = ${cunit_ldflags}

EOF

