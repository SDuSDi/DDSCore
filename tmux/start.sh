#! /bin/bash
set -e

touch ~/.tmux.conf
echo "set -g mouse" >> ~/.tmux.conf

tmuxinator start -p ./tmux/session.yml