#!/bin/sh
export LD_LIBRARY_PATH=:
export LD_PRELOAD=/home/user42/malloc/libft_malloc.so
$@
