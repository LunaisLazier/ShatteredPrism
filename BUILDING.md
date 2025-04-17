## Building
To build the launcher yourself, follow the instructions on the Prism Launcher website, but clone this repo instead:

- [Windows](https://prismlauncher.org/wiki/development/build-instructions/windows/)
- [Linux](https://prismlauncher.org/wiki/development/build-instructions/linux/)
- [MacOS](https://prismlauncher.org/wiki/development/build-instructions/macos/)
- [OpenBSD](https://prismlauncher.org/wiki/development/build-instructions/openbsd/)
## Packaging
### If you are building a .deb :
Copy the prism makedeb repo but before running makedeb command you need to modify the MAKEPKG file.
This is modifed MAKEPKG for Shattered Prism : 
```
# Modified from the original prismlauncher MAKEPKG
# https://mpr.makedeb.org/packages/prismlauncher
# License: GPL-3.0
pkgname=shatteredprism
pkgver=1.7
pkgrel=1
pkgdesc='Minecraft launcher with ability to manage multiple instances.'
arch=('i386' 'amd64' 'arm64' 'armhf' 'riscv64')
url='https://github.com/LunaisLazier/ShatteredPrism'
license=('GPL-3')
depends=(
  'libqt6core5compat6'
  'libqt6core6'
  'libqt6network6'
  'libqt6networkauth6'
  'libqt6svg6'
  'libqt6widgets6'
  'libqt6xml6'
  'qt6-image-formats-plugins'
)
makedepends=(
  'cmake'
  'extra-cmake-modules'
  'g++'
  'gcc'
  'git'
  'libgl1-mesa-dev'
  'libqt6core5compat6-dev'
  'openjdk-17-jdk'
  'qt6-base-dev'
  'qt6-networkauth-dev'
  'qtchooser'
  'scdoc'
  'zlib1g-dev'
)
optdepends=(
  'flite: narrator support'
  'java-runtime=17: support for Minecraft versions >= 1.17 and <= 1.20.4'
  'java-runtime=21: support for Minecraft versions >= 1.20.5'
  'java-runtime=8: support for Minecraft versions <= 1.16'
  'x11-xserver-utils: xrandr is needed to support Minecraft versions <= 1.12'
  's!gamemode: support for GameMode'
  's!mangohud: HUD overlay for FPS and temperatures'
)
source=(
  "https://github.com/LunaisLazier/ShatteredPrism/releases/download/${pkgver}/ShatteredPrism-${pkgver}.tar.gz"
  'gcc-armv7-fix.patch'
  'copyright'
)
sha256sums=('SKIP'
            '42394447d4b52c9329ff45f3c700c0eb2090a5803c5de010587d64294c37420f'
            '55f14ca1c20ba05785b248b3454ce2671149112d6b7c1a4e4fd24f4dde8f4c71')
postinst=postinst.sh

# allow for ARM support
#TODO: makedeb's hard-coding for x86-64 has been fixed in a future makedeb version
#TODO: these 8 lines make this script match the behavior of future makedeb. When it releases, remove this
CARCH="$(dpkg --print-architecture)"
CHOST="$(uname -m)-pc-linux-gnu"
CFLAGS=${CFLAGS/-march=x86-64/}
CXXFLAGS=${CXXFLAGS/-march=x86-64/}
CFLAGS=${CFLAGS/-mtune=generic/}
CXXFLAGS=${CXXFLAGS/-mtune=generic/}
CFLAGS=${CFLAGS/-fcf-protection/}
CXXFLAGS=${CXXFLAGS/-fcf-protection/}

# if the user hasn't specified a tuning/architecture, specify our own minimal defaults to cover the earliest CPUs
if [[ ${CFLAGS} != *"-mtune"* && ${CFLAGS} != *"-march"* ]]; then
  case "${CARCH}" in
    amd64)
      CFLAGS+=" -march=x86-64 -fcf-protection"
      CXXFLAGS+=" -march=x86-64 -fcf-protection"
      ;;
    i386)
      CFLAGS+=" -march=i686"
      CXXFLAGS+=" -march=i686"
      ;;
    arm64)
      CFLAGS+=" -march=armv8-a"
      CXXFLAGS+=" -march=armv8-a"
      ;;
    armhf)
      CFLAGS+=" -march=armv7-a+fp"
      CXXFLAGS+=" -march=armv7-a+fp"
      ;;
    riscv64)
      CFLAGS+=" -march=rv64imafdc"
      CXXFLAGS+=" -march=rv64imafdc"
      ;;
  esac
fi

prepare() {
  # workaround https://gcc.gnu.org/bugzilla/show_bug.cgi?id=64860
  # more info: https://github.com/PrismLauncher/PrismLauncher/issues/128
  if [[ "$(uname -m)" = armv7* ]]; then
    echo "GCC / ARMv7 fix is needed for this architecture, applying gcc-armv7-fix.patch"
    patch --directory="PrismLauncher-${pkgver}" --forward --strip=1 --input="${srcdir}/gcc-armv7-fix.patch"
  else
    echo "GCC / ARMv7 fix is not needed for this architecture, skipping gcc-armv7-fix.patch"
  fi
}

build() {
  cd "${srcdir}/ShatteredPrism-${pkgver}"
  cmake -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="/usr" \
    -DLauncher_BUILD_PLATFORM="debian" \
    -DLauncher_APP_BINARY_NAME="${pkgname}" \
    -DLauncher_ENABLE_JAVA_DOWNLOADER=ON \
    -DENABLE_LTO=ON \
    -Bbuild -S.
  cmake --build build
}

check() {
  cd "${srcdir}/ShatteredPrism-${pkgver}/build"
  ctest . -E Task  # Skip unreliable Task test
}

package() {
  cd "${srcdir}/ShatteredPrism-${pkgver}/build"
  DESTDIR="${pkgdir}" cmake --install .
  mkdir -p "${pkgdir}/usr/share/doc/${pkgname}"
  cp -v "${srcdir}/copyright" "${pkgdir}/usr/share/doc/${pkgname}/copyright"
}

# vim: set sw=2 expandtab:
```
If check fails just run makedeb --no-check.

### If you are building rpm for fedora
No current instructions, modify the .spec file by yourself.
### If you are building rpm for opensuse
No current instructions modify the .spec file by yourself.
