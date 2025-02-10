#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/tath/Desktop/University/apal/hw1/b_tree_assn
  make -f /Users/tath/Desktop/University/apal/hw1/b_tree_assn/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/tath/Desktop/University/apal/hw1/b_tree_assn
  make -f /Users/tath/Desktop/University/apal/hw1/b_tree_assn/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/tath/Desktop/University/apal/hw1/b_tree_assn
  make -f /Users/tath/Desktop/University/apal/hw1/b_tree_assn/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/tath/Desktop/University/apal/hw1/b_tree_assn
  make -f /Users/tath/Desktop/University/apal/hw1/b_tree_assn/CMakeScripts/ReRunCMake.make
fi

