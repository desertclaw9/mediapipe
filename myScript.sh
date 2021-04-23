git clone https://github.com/opencv/opencv_contrib.git -b 3.4.13 --depth 1
git clone https://github.com/opencv/opencv.git -b 3.4.13 --depth 1
mkdir opencv/build
cd opencv/build
cmake -DCMAKE_BUILD_TYPE=RELEASE \
-DBUILD_opencv_calib3d=ON \
-DBUILD_opencv_features2d=ON \
-DBUILD_opencv_highgui=ON \
-DBUILD_opencv_video=ON \
-DBUILD_opencv_videoio=ON \
-DBUILD_opencv_imgcodecs=ON \
-DBUILD_opencv_imgproc=ON \
-DBUILD_opencv_core=ON \
-DBUILD_opencv_aruco=OFF -DBUILD_opencv_bgsegm=OFF -DBUILD_opencv_bioinspired=OFF \
-DBUILD_opencv_ccalib=OFF -DBUILD_opencv_datasets=OFF -DBUILD_opencv_dnn=OFF \
-DBUILD_opencv_dnn_objdetect=OFF -DBUILD_opencv_dpm=OFF -DBUILD_opencv_face=OFF \
-DBUILD_opencv_fuzzy=OFF -DBUILD_opencv_hfs=OFF -DBUILD_opencv_img_hash=OFF \
-DBUILD_opencv_js=OFF -DBUILD_opencv_line_descriptor=OFF -DBUILD_opencv_phase_unwrapping=OFF \
-DBUILD_opencv_plot=OFF -DBUILD_opencv_quality=OFF -DBUILD_opencv_reg=OFF \
-DBUILD_opencv_rgbd=OFF -DBUILD_opencv_saliency=OFF -DBUILD_opencv_shape=OFF \
-DBUILD_opencv_structured_light=OFF -DBUILD_opencv_surface_matching=OFF \
-DBUILD_opencv_world=OFF -DBUILD_opencv_xobjdetect=OFF -DBUILD_opencv_xphoto=OFF \
-DBUILD_TESTS=OFF \
-DBUILD_PERF_TESTS=OFF \
-DBUILD_EXAMPLES=OFF \
-DBUILD_SHARED_LIBS=OFF \
-DWITH_ITT=OFF \
-DWITH_JASPER=OFF \
-DWITH_JPEG=ON \
-DWITH_PNG=ON \
-DWITH_TIFF=ON \
-DWITH_WEBP=OFF \
-DCV_ENABLE_INTRINSICS=ON \
-DWITH_EIGEN=ON \
-DWITH_PTHREADS=ON \
-DWITH_PTHREADS_PF=ON \
-DOPENCV_SKIP_VISIBILITY_HIDDE=ON \
-DOPENCV_SKIP_PYTHON_LOADER=ON \
-DBUILD_opencv_python=OFF \
-DENABLE_CCACHE=OFF \
-DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
-D WITH_TBB=ON -D INSTALL_C_EXAMPLES=OFF -D WITH_CUDA=OFF -D WITH_QT=OFF -D WITH_OPENCL=OFF -D BUILD_DOCS=OFF \
-DCMAKE_INSTALL_PREFIX=/home/xharlord/pruebaOPENV/static ..

make -j 16
make install