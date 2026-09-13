#!/bin/bash

cat <<EOF | ./minishell ; echo "minishell exit code: $?"
echo does this work?
EOF
