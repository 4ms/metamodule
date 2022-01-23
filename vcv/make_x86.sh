# Builds x86 version from arm64 host
arch -x86_64 zsh -c "RACK_DIR=$HOME/4ms/vcv/Rack-x86 make -j10 $1"
