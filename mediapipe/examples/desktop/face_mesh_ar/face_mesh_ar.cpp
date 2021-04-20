#include <opencv2/imgproc.hpp>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/formats/landmark.pb.h"

#include "face_mesh_ar.h"

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "output_video";

constexpr char kOutputStreamLM[] = "multi_face_landmarks";

ABSL_FLAG(std::string,
    calculator_graph_config_file,
    "mediapipe/graphs/face_mesh/face_mesh_desktop_live.pbtxt",
    "Name of file containing text format CalculatorGraphConfig proto.");

namespace upm {

absl::Status RunMPPGraph(cv::Mat &camera_frame,
                         std::vector<mediapipe::NormalizedLandmarkList> &landMarks,
                         bool showResults) {
  std::string calculator_graph_config_contents;
  MP_RETURN_IF_ERROR(mediapipe::file::GetContents(
      absl::GetFlag(FLAGS_calculator_graph_config_file),
      &calculator_graph_config_contents));

  mediapipe::CalculatorGraphConfig config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
      calculator_graph_config_contents);

  LOG(INFO) << "Initialize the calculator graph.";
  mediapipe::CalculatorGraph graph;
  MP_RETURN_IF_ERROR(graph.Initialize(config));

  LOG(INFO) << "Start running the calculator graph.";
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller pollerFrame,
                   graph.AddOutputStreamPoller(kOutputStream));
  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller pollerLM,
                   graph.AddOutputStreamPoller(kOutputStreamLM));
  MP_RETURN_IF_ERROR(graph.StartRun({}));

  LOG(INFO) << "Start grabbing and processing frame";

  // Wrap Mat into an ImageFrame.
  auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
      mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
      mediapipe::ImageFrame::kDefaultAlignmentBoundary);
  cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
  camera_frame.copyTo(input_frame_mat);

  // Send image packet into the graph.
  size_t frame_timestamp_us =
      (double) cv::getTickCount() / (double) cv::getTickFrequency() * 1e6;
  MP_RETURN_IF_ERROR(graph.AddPacketToInputStream(
      kInputStream, mediapipe::Adopt(input_frame.release())
          .At(mediapipe::Timestamp(frame_timestamp_us))));

  // Get the graph result packet, or stop if that fails.
  mediapipe::Packet packetFrame;
  if (!pollerFrame.Next(&packetFrame)) {
    MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
    return graph.WaitUntilDone();
  }

  mediapipe::Packet packetLM;
  if (!pollerLM.Next(&packetLM)) {
    MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
    return graph.WaitUntilDone();
  }

  auto &output_frame = packetFrame.Get<mediapipe::ImageFrame>();
  landMarks = packetLM.Get<std::vector<mediapipe::NormalizedLandmarkList>>();

  // Convert back to opencv for display or saving.
  if (showResults) {
    cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
    cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);
    camera_frame = output_frame_mat.clone();
  }

  LOG(INFO) << "Shutting down.";
  MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
  return graph.WaitUntilDone();
}
}