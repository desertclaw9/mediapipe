#include <opencv2/opencv.hpp>
#include <glog/logging.h>

#include "mediapipe/examples/desktop/face_mesh_ar/face_mesh_ar.h"

constexpr char kWindowName[] = "MediaPipe";

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  cv::Mat camera_frame_raw = cv::imread("/home/xharlord/workspaces/unity-ar-pcr/resources/Test/singleFace.jpg");

  cv::Mat camera_frame;
  cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
  std::vector<mediapipe::NormalizedLandmarkList> landMarks;
  absl::Status run_status = upm::RunMPPGraph(camera_frame, landMarks, true);

  cv::imshow(kWindowName, camera_frame);
  cv::waitKey(0);

  if (!run_status.ok()) {
    LOG(ERROR) << "Failed to run the graph: " << run_status.message();
    return EXIT_FAILURE;
  } else {
    LOG(INFO) << "Success!";
  }
  return EXIT_SUCCESS;
}