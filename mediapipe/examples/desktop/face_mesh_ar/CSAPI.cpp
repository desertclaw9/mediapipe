#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"
#include "mediapipe/framework/formats/landmark.pb.h"


#include "mediapipe/examples/desktop/face_mesh_ar/face_mesh_ar.h"

extern "C" {

void face_mesh_mediapipe(unsigned char *data, int width, int height, bool showResults) {

  cv::Mat original_frame(cv::Size(width, height), CV_8UC4, data);
  cv::Mat color_frame;

  cv::cvtColor(original_frame, color_frame, cv::COLOR_RGBA2RGB);
  cv::flip(color_frame, color_frame, 0);

  std::vector<mediapipe::NormalizedLandmarkList> landMarks;
  upm::RunMPPGraph(color_frame, landMarks, showResults);

  cv::flip(color_frame, color_frame, 0);

  cvtColor(color_frame, original_frame, cv::COLOR_RGB2RGBA);
}
}