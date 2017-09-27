#!/bin/zsh

rpath=${PWD#$0:A:h:h/}

for f in "$@";{

ff=$(sed 's/[^A-Za-z0-9]/_/g' <<< _DCS_${rpath}/${1}_)
[ -e "$f" ] && echo "File $f exists!" || {
  echo Adding   $PWD/$f;
cat > $f <<EOF
#ifndef  $ff
#define  $ff 1
#include "$f"   //in c file


#endif
EOF

}
}
