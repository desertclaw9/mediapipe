#include <opencv2/opencv.hpp>
#include <glog/logging.h>

#include "mediapipe/examples/desktop/face_mesh_ar/face_mesh_ar.h"

constexpr char kWindowName[] = "MediaPipe";

int main() {

  if (!std::getenv("MEDIAPIPE_RESOURCES")) {
    LOG(ERROR) << "Error. The environment variable \"MEDIAPIPE_RESOURCES\" is not defined. \n"
               << "Please do export MEDIAPIPE_RESOURCES=YOUR_MEDIAPIPE_REPOSITORY";
    return 0;
  }

  std::string config_file =
      std::string(std::getenv("MEDIAPIPE_RESOURCES"));

  cv::Mat
      camera_frame_raw = cv::imread(std::string(std::getenv("AR_PCR_RESOURCES")) + "/Test/singleFace.jpg");

  cv::Mat camera_frame;
  cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
  std::vector<mediapipe::NormalizedLandmarkList> landMarks;
  absl::Status run_status = upm::RunMPPGraph(config_file, camera_frame, landMarks, true);

  cv::cvtColor(camera_frame, camera_frame, cv::COLOR_RGB2BGR);
  cv::imshow(kWindowName, camera_frame);
  cv::waitKey(0);

  LOG(INFO) << landMarks.at(0).landmark().at(0).x();

  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
    return EXIT_FAILURE;
  } else {
    LOG(INFO) << "Success!";
  }
  return EXIT_SUCCESS;
}