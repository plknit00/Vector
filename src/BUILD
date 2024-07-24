cc_library(
    name = "vector",
    hdrs = ["vector.h"],
    deps = [
    ],
)

cc_library(
    name = "vector_test_fixture",
    hdrs = ["vector_test_fixture.h"],
    deps = [
        ":vector",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "vector_test",
    size = "small",
    srcs = ["vector_test.cc"],
    deps = [
        ":vector",
        ":vector_test_fixture",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
