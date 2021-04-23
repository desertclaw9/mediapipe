#ifndef MEDIAPIPE_MEDIAPIPE_EXAMPLES_DESKTOP_FACE_MESH_AR_FACE_MESH_AR_H_
#define MEDIAPIPE_MEDIAPIPE_EXAMPLES_DESKTOP_FACE_MESH_AR_FACE_MESH_AR_H_

#include <opencv2/core.hpp>
#include "absl/status/status.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace upm {

absl::Status RunMPPGraph(std::string config_file,
                         cv::Mat &frame,
                         std::vector<mediapipe::NormalizedLandmarkList> &landMarks,
                         bool showResults = false);

}

#endif //MEDIAPIPE_MEDIAPIPE_EXAMPLES_DESKTOP_FACE_MESH_AR_FACE_MESH_AR_H_
