// This file is part of the DerpVision Project.
// Licensing information can be found in the LICENSE file.
// (C) 2015 Group 13. All rights reserved.

#pragma once

#include <cmath>
#include <iostream>

#include <opencv2/opencv.hpp>


namespace dv {

/**
 * All connections to procams are identified by ID equal to the ID of the
 * associated ProCam.
 */
using ConnectionID = uint64_t;

/**
 * Camera matrix & distorion.
 */
struct CameraModel {
  cv::Mat calib;
  cv::Mat dist;
};

/**
 * Camera pose.
 */
struct CameraPose {
  cv::Mat rvec;
  cv::Mat tvec;
};

/**
 * Structure representing the equation of a plane.
 */
struct Plane {
  float nx, ny, nz;
  float d;
};

/**
 * Structure representing a vertex (position + color + viewId).
 */
struct Vertex {
  Vertex(
      const cv::Point3f &position,
      const cv::Point3f &color,
      ConnectionID viewId)
    : position(position)
    , color(color)
    , viewId(viewId)
  {
  }

  cv::Point3f position;
  cv::Point3f color;
  ConnectionID viewId;
};

/**
 * Structure representing a size.
 */
struct Size {
  unsigned width;
  unsigned height;
};


static inline bool equals(float x, float y) {
  const float epsilon = 0.000001f;
  return std::abs(x - y) <= epsilon * std::abs(x);
}

// To and from string conversion for the resolution type.
std::ostream& operator << (std::ostream& os, const Size&);
std::istream& operator >> (std::istream& is, Size&);


/**
 * Generic OpenCV type generator.
 */
template<typename T, size_t D> struct CVType { };
template<> struct CVType<float, 1>  { static const int type = CV_32FC1; };
template<> struct CVType<double, 1>  { static const int type = CV_64FC1; };
template<> struct CVType<uint8_t, 4> { static const int type = CV_8UC4; };

}

