#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "sdf/sdf/sdf.h"
#include "sdf/plugins/sensors/cameras/pinhole_radtan_camera.h"

int main(int argc, char **argv)
{
  // SDF::SDF sdf = SDF::SDF();

  // SDF::sensors::PinholeRadTanCamera::Properties properties;
  // properties.name = "cam0";
  // properties.width = 752;
  // properties.height = 480;
  // properties.channels = 1;
  // properties.fps = 20.0;
  // properties.fx = 458.654;
  // properties.fy = 457.296;
  // properties.cx = 367.215;
  // properties.cy = 248.375;
  // properties.k1 = -0.28340811;
  // properties.k2 = 0.07395907;
  // properties.p1 = 0.00019359;
  // properties.p2 = 1.76187114e-05;

  // std::shared_ptr<SDF::sensors::PinholeRadTanCamera::Data> data(new SDF::sensors::PinholeRadTanCamera::Data);
  // data->timestamp = 0;
  // data->image = cv::imread("test.png");
  // auto sensor = sdf.addSensor<SDF::sensors::PinholeRadTanCamera>(properties);
  // sensor->addData(data);

  // sdf.write("test.sdf");

  // std::ifstream file("test.sdf", std::ios::binary);
  // if (file.is_open())
  // {
  //   auto newHeader = SDF::Header::fromStream(file);
  //   std::cout << newHeader.to_string() << std::endl;
  // }
  return 0;
}