#!/bin/sh
args="$@"
echo "OpenCV installation..."

#PROJECT_PATH=echo ${args[0]}

# Save current working directory
cwd=$(pwd)

cd "$cwd" || exit

#Specify OpenCV version
cvVersion="master"

# Clean build directories
rm -rf opencv/build
rm -rf opencv_contrib/build

# Create directory for installation
mkdir lib-emscripten
mkdir lib-emscripten/opencv

git clone https://github.com/opencv/opencv.git
cd opencv || exit
git -C opencv checkout 4.5.2
git checkout $cvVersion
cd ..

# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git
# Enter that directory
cd emsdk
# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull
# Download and install the latest SDK tools.
./emsdk install 2.0.25
# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate 2.0.25
# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
cd ..

 
# git clone https://github.com/opencv/opencv_contrib.git
# cd opencv_contrib
# git checkout $cvVersion
# cd ..

cd opencv || exit
mkdir build
cd build || exit

#emscriptenToolChainFile=""
emscriptenToolChainFile=../emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake

#case "$OSTYPE" in
#  linux*)   emscriptenToolChainFile=/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake ;;
#  darwin*)  emscriptenToolChainFile=/opt/homebrew/Cellar/emscripten/3.1.8/libexec/cmake/Modules/Platform/Emscripten.cmake ;;
#  msys*)    echo "windows" ;;
#  solaris*) echo "solaris" ;;
#  bsd*)     echo "bsd" ;;
#  *)        echo "unknown" ;;
#esac

# add this if extra modules needed -D OPENCV_EXTRA_MODULES_PATH=path to opencv_contrib modules \
#      -D CMAKE_PREFIX_PATH="$PROJECT_PATH" \
#      -D CMAKE_MODULE_PATH="$PROJECT_PATH"/lib/cmake/opencv4 \
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX="$cwd"/lib-emscripten/opencv \
      -D CMAKE_TOOLCHAIN_FILE="$emscriptenToolChainFile" \
      -D ENABLE_PIC=FALSE \
      -D CPU_BASELINE='' \
      -D CPU_DISPATCH='' \
      -D CV_TRACE=OFF \
      -D BUILD_SHARED_LIBS=OFF \
      -D BUILD_PROTOBUF=OFF \
      -D WITH_PROTOBUF=OFF \
      -D WITH_1394=OFF \
      -D WITH_ADE=OFF \
      -D WITH_VTK=OFF \
      -D WITH_EIGEN=OFF \
      -D WITH_FFMPEG=OFF \
      -D WITH_GSTREAMER=OFF \
      -D WITH_GTK=OFF \
      -D WITH_GTK_2_X=OFF \
      -D WITH_IPP=OFF \
      -D WITH_JASPER=OFF \
      -D WITH_JPEG=OFF \
      -D WITH_WEBP=OFF \
      -D WITH_OPENEXR=OFF \
      -D WITH_OPENGL=OFF \
      -D WITH_OPENVX=OFF \
      -D WITH_OPENNI=OFF \
      -D WITH_OPENNI2=OFF \
      -D WITH_PNG=OFF \
      -D WITH_TBB=OFF \
      -D WITH_TIFF=OFF \
      -D WITH_V4L=OFF \
      -D WITH_OPENCL=OFF \
      -D WITH_OPENCL_SVM=OFF \
      -D WITH_OPENCLAMDFFT=OFF \
      -D WITH_OPENCLAMDBLAS=OFF \
      -D WITH_GPHOTO2=OFF \
      -D WITH_LAPACK=OFF \
      -D WITH_ITT=OFF \
      -D WITH_QUIRC=OFF \
      -D BUILD_ZLIB=ON \
      -D BUILD_opencv_core=ON \
      -D BUILD_opencv_apps=OFF \
      -D BUILD_opencv_calib3d=OFF \
      -D BUILD_opencv_dnn=OFF \
      -D BUILD_opencv_features2d=ON \
      -D BUILD_opencv_flann=ON \
      -D BUILD_opencv_gapi=OFF \
      -D BUILD_opencv_ml=OFF \
      -D BUILD_opencv_photo=OFF \
      -D BUILD_opencv_imgcodecs=OFF \
      -D BUILD_opencv_shape=OFF \
      -D BUILD_opencv_videoio=OFF \
      -D BUILD_opencv_videostab=OFF \
      -D BUILD_opencv_highgui=OFF \
      -D BUILD_opencv_superres=OFF \
      -D BUILD_opencv_stitching=OFF \
      -D BUILD_opencv_java=OFF \
      -D BUILD_opencv_js=OFF \
      -D BUILD_opencv_python2=OFF \
      -D BUILD_opencv_python3=OFF \
      -D BUILD_EXAMPLES=OFF \
      -D BUILD_PACKAGE=OFF \
      -D BUILD_TESTS=OFF \
      -D BUILD_PERF_TESTS=OFF \
      -D BUILD_DOCS=OFF \
      -D WITH_PTHREADS_PF=ON \
      -D CV_ENABLE_INTRINSICS=ON \
      -D BUILD_WASM_INTRIN_TESTS=OFF \
      -D CMAKE_C_FLAGS="-s WASM=1 -s USE_PTHREADS=0    -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winconsistent-missing-override -Wno-delete-non-virtual-dtor -Wno-unnamed-type-template-args -Wno-comment -Wno-deprecated-enum-enum-conversion -Wno-deprecated-anon-enum-enum-conversion -fdiagnostics-show-option -pthread -Qunused-arguments -ffunction-sections -fdata-sections  -fvisibility=hidden -fvisibility-inlines-hidden -O3 -DNDEBUG  -DNDEBUG -msimd128" \
      -D CMAKE_CXX_FLAGS="-s WASM=1 -s USE_PTHREADS=0    -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winconsistent-missing-override -Wno-delete-non-virtual-dtor -Wno-unnamed-type-template-args -Wno-comment -Wno-deprecated-enum-enum-conversion -Wno-deprecated-anon-enum-enum-conversion -fdiagnostics-show-option -pthread -Qunused-arguments -ffunction-sections -fdata-sections  -fvisibility=hidden -fvisibility-inlines-hidden -O3 -DNDEBUG  -DNDEBUG -msimd128" ..
        
make
make install

#export OpenCV_DIR="$cwd"/lib/opencv/lib/cmake/opencv4/OpenCVConfig.cmake
[[ ":$PATH:" != *":$cwd/lib-emscripten/opencv/lib/cmake/opencv4/OpenCVConfig.cmake:"* ]] && PATH="$cwd/lib-emscripten/opencv/lib/cmake/opencv4/OpenCVConfig.cmake:${PATH}"
echo "$PATH"

cd "$cwd" || exit