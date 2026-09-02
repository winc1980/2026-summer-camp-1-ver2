FROM skylyrac/blocksds:slim-latest

# ---------------------------------------------------------------------------
# BlocksDS / Wonderful Toolchain のパッケージ (wf-pacman)
# 追加したいものはここに足す
#   例: blocksds-extra, blocksds-palib
# ---------------------------------------------------------------------------
RUN wf-pacman -Syu --noconfirm && \
    wf-pacman -S --noconfirm \
        blocksds-default \
    && \
    wf-config clean-caches --all

# ---------------------------------------------------------------------------
# Ubuntu 側のパッケージ (apt)
# 追加したいものはここに足す
#   例: python3, imagemagick, unzip
#
#   clangd     : エディタの補完・ジャンプ用
#   gcc        : examples/ の C 文法サンプルを動かす用（DS 用ではない。
#                DS のビルドには arm-none-eabi-gcc を使う）
#   libc6-dev  : gcc が使う標準ライブラリのヘッダ
# ---------------------------------------------------------------------------
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        clangd \
        gcc \
        libc6-dev \
    && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/*

# ---------------------------------------------------------------------------
# 非 root ユーザー
# ubuntu:24.04 は uid 1000 の "ubuntu" を同梱しているので、衝突を避けるため
# 一度消してから dev を作る
# ---------------------------------------------------------------------------
RUN (userdel -r ubuntu 2>/dev/null || true) && \
    useradd -m -u 1000 -s /bin/bash dev

USER dev