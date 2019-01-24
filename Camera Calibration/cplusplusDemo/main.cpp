#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

int main() {
  using namespace cv;

  std::string inputFilename{"../images/cam1-img/cam1-%8d.jpg"};

  //  CALIB_CB_FAST_CHECK
  int chessBoardFlags = CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK;

  Size boardSize{8, 6};
  Size imageSize{640, 480};
  float squareSize = 30.f; // mm
  float grid_width = squareSize * (boardSize.width - 1);

  std::vector<std::string> imageList;
  std::vector<std::vector<Point2f>> imagePoints;
  std::vector<Mat> imageViews;

  VideoCapture capture(inputFilename);

  while (capture.isOpened()) {
    Mat view;
    capture >> view;

    if (!view.empty()) {
      std::vector<Point2f> pointBuf;

      bool found = findChessboardCorners(view, boardSize, pointBuf, chessBoardFlags);

      if (found) {
        Mat viewGray;
        cvtColor(view, viewGray, COLOR_BGR2GRAY);

        cornerSubPix(viewGray, pointBuf, Size(3, 3), Size(-1, -1),
                     TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.0001));

        drawChessboardCorners(view, boardSize, Mat(pointBuf), found);

        imageViews.push_back(view);
        imagePoints.emplace_back(std::move(pointBuf));
      }

    } else {
      break;
    }
  }

  /*
  namedWindow("Image Sequence: Detected Corners");

  for (auto &img: imageViews) {
    imshow("Image Sequence: Detected Corners", img);
    waitKey(-1);  // indefinitely waits for any key
  }
  */

  // calibration
  Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
  Mat distCoeffs = Mat::zeros(8, 1, CV_64F);
  std::vector<Mat> rvecs, tvecs;
  std::vector<float> reprojErrs;

  std::vector<Point3f> newObjPoints;
  double totalAvgErr = 0;

  // run calibration
  std::vector<std::vector<Point3f>> objectPoints(1);

  for (int i = 0; i < boardSize.height; ++i) {
    for (int j = 0; j < boardSize.width; ++j) {
      objectPoints[0].emplace_back(j * squareSize, i * squareSize, 0);
    }
  }

  objectPoints[0][boardSize.width - 1].x = objectPoints[0][0].x + grid_width;
  newObjPoints = objectPoints[0];
  objectPoints.resize(imagePoints.size(), objectPoints[0]);

  //Find intrinsic and extrinsic camera parameters
  double rms;

  rms = calibrateCameraRO(objectPoints, imagePoints, imageSize, -1, cameraMatrix, distCoeffs, rvecs, tvecs,
                          newObjPoints, CALIB_USE_LU);

  std::cout << "Re-projection error: " << rms << '\n';

  objectPoints.clear();
  objectPoints.resize(imagePoints.size(), newObjPoints);

  // re-projection errors
  std::vector<Point2f> imagePoints2;
  std::vector<float> perViewErrors;
  size_t totalPoints = 0;
  double totalErr = 0;
  double err;

  perViewErrors.resize(objectPoints.size());

  for (size_t i = 0; i < objectPoints.size(); ++i) {

    projectPoints(objectPoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);
    err = norm(imagePoints[i], imagePoints2, NORM_L2);

    size_t n = objectPoints[i].size();
    perViewErrors[i] = (float) std::sqrt(err * err / n);
    totalErr += err * err;
    totalPoints += n;
  }

  totalAvgErr = std::sqrt(totalErr / totalPoints);

  std::cout << "total avg err: " << totalAvgErr << '\n';

  // camera matrix, dist coeffs, reproj error, pixel error scatter plot


  // undistort
  Mat view, rview, map1, map2;

  initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
                          getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, nullptr),
                          imageSize, CV_16SC2, map1, map2);

  for (auto &img : imageViews) {
    remap(img, rview, map1, map2, INTER_LINEAR);
    imshow("Image View", rview);
    waitKey(-1);
  }

  return 0;
}