#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"
#include <glog/logging.h>

#include "mediapipe/examples/desktop/face_mesh_ar/face_mesh_ar.h"

extern "C" {

int face_mesh_mediapipe(const char *config_file,
                        unsigned char *data,
                        int width,
                        int height,
                        float faceLandmarks[],
                        bool showResults) {

  cv::Mat original_frame(cv::Size(width, height), CV_8UC4, data);
  cv::Mat color_frame;

  cv::cvtColor(original_frame, color_frame, cv::COLOR_RGBA2RGB);
  cv::flip(color_frame, color_frame, 0);

  std::vector<mediapipe::NormalizedLandmarkList> landMarks;
  upm::RunMPPGraph(std::string(config_file), color_frame, landMarks, showResults);

  if (landMarks.size() != 0) {

    LOG(INFO) << landMarks.at(0).landmark_size();
    LOG(INFO) << sizeof(faceLandmarks);
    int acc = 0;
    for (auto &landmark : landMarks) {
      for (int i = 0; i < landmark.landmark_size(); i++) {
        faceLandmarks[acc++] = landmark.landmark(i).x();
        faceLandmarks[acc++] = landmark.landmark(i).y();
      }
    }
  }

  cv::flip(color_frame, color_frame, 0);

  cvtColor(color_frame, original_frame, cv::COLOR_RGB2RGBA);
  return landMarks.size();
}
}