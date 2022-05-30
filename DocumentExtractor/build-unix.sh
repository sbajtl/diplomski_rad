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
mkdir lib-macos
mkdir lib-macos/opencv

git clone https://github.com/opencv/opencv.git
cd opencv || exit
git -C opencv checkout 4.5.2
git checkout $cvVersion

cd ..
 
# git clone https://github.com/opencv/opencv_contrib.git
# cd opencv_contrib
# git checkout $cvVersion
# cd ..

cd opencv || exit
mkdir build
cd build || exit

# add this if extra modules needed -D OPENCV_EXTRA_MODULES_PATH=path to opencv_contrib modules \
#      -D CMAKE_PREFIX_PATH="$PROJECT_PATH" \
#      -D CMAKE_MODULE_PATH="$PROJECT_PATH"/lib/cmake/opencv4 \
cmake -D CMAKE_INSTALL_PREFIX="$cwd"/lib-macos/opencv \
      -D CMAKE_BUILD_TYPE=Release \
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
      -D WITH_JPEG=ON \
      -D WITH_WEBP=ON \
      -D WITH_OPENEXR=OFF \
      -D WITH_OPENGL=OFF \
      -D WITH_OPENVX=OFF \
      -D WITH_OPENNI=OFF \
      -D WITH_OPENNI2=OFF \
      -D WITH_PNG=ON \
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
      -D BUILD_opencv_imgcodecs=ON \
      -D BUILD_opencv_highgui=ON \
      -D BUILD_opencv_apps=OFF \
      -D BUILD_opencv_calib3d=OFF \
      -D BUILD_opencv_dnn=OFF \
      -D BUILD_opencv_features2d=ON \
      -D BUILD_opencv_flann=ON \
      -D BUILD_opencv_gapi=OFF \
      -D BUILD_opencv_ml=ON \
      -D BUILD_opencv_photo=OFF \
      -D BUILD_opencv_shape=OFF \
      -D BUILD_opencv_videoio=ON \
      -D BUILD_opencv_videostab=OFF \
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
      -D WITH_PTHREADS_PF=OFF \
      -D CV_ENABLE_INTRINSICS=OFF \
      -D BUILD_WASM_INTRIN_TESTS=OFF ..
        
make
make install

#export OpenCV_DIR="$cwd"/lib/opencv/lib/cmake/opencv4/OpenCVConfig.cmake
[[ ":$PATH:" != *":$cwd/lib-macos/opencv/lib/cmake/opencv4/OpenCVConfig.cmake:"* ]] && PATH="$cwd/lib-macos/opencv/lib/cmake/opencv4/OpenCVConfig.cmake:${PATH}"
echo "$PATH"

cd "$cwd" || exit