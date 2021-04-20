licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])

cc_binary(
    name = "face_mesh_main",
    srcs = [
        "face_mesh_ar.cpp",
        "face_mesh_ar.h",
        "main.cpp",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_graph",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_core",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/graphs/face_mesh:desktop_live_calculators",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_binary(
    name = "facesMediapipe",
    srcs = [
        "CSAPI.cpp",
        "face_mesh_ar.cpp",
        "face_mesh_ar.h",
    ],
    linkshared = 1,
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_graph",
        "//mediapipe/framework/port:logging",
        "//mediapipe/framework/port:opencv_core",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/graphs/face_mesh:desktop_live_calculators",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)
