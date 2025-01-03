#include "sdf/plugins/camera_pinhole_radtan.h"

SDF::Bytes SDF::sensors::CameraPinholeRadTanProps::toBytes()
{
  Bytes bytes = Bytes();
  bytes.add_raw(notes.data(), notes.size());
  bytes.add(rate);
  bytes.add(width);
  bytes.add(height);
  bytes.add(fx);
  bytes.add(fy);
  bytes.add(cx);
  bytes.add(cy);
  bytes.add(k1);
  bytes.add(k2);
  bytes.add(p1);
  bytes.add(p2);
  bytes.add(k3);
  bytes.add(imageChannels);
  bytes.add(dataType);
  return bytes;
}

SDF::sensors::CameraPinholeRadTanProps SDF::sensors::CameraPinholeRadTanProps::fromBytes(SDF::Bytes bytes)
{
  bytes.resetPosition();
  CameraPinholeRadTanProps props = CameraPinholeRadTanProps();
  props.notes = std::string(static_cast<char *>(bytes.get_raw()));
  props.rate = bytes.get<float>();
  props.width = bytes.get<uint32_t>();
  props.height = bytes.get<uint32_t>();
  props.fx = bytes.get<float>();
  props.fy = bytes.get<float>();
  props.cx = bytes.get<float>();
  props.cy = bytes.get<float>();
  props.k1 = bytes.get<float>();
  props.k2 = bytes.get<float>();
  props.p1 = bytes.get<float>();
  props.p2 = bytes.get<float>();
  props.k3 = bytes.get<float>();
  props.imageChannels = bytes.get<uint32_t>();
  props.dataType = bytes.get<uint32_t>();

  return props;
}

SDF::Bytes SDF::sensors::CameraPinholeRadTanData::toBytes()
{
  Bytes bytes = Bytes();
  bytes.add(timestamp);
  bytes.add(image.cols);
  bytes.add(image.rows);
  bytes.add(image.channels());
  bytes.add_raw(image.data, image.total() * image.elemSize());
  return bytes;
}

SDF::sensors::CameraPinholeRadTanData SDF::sensors::CameraPinholeRadTanData::fromBytes(SDF::Bytes bytes)
{
  bytes.resetPosition();
  CameraPinholeRadTanData data = CameraPinholeRadTanData();
  data.timestamp = bytes.get<uint64_t>();
  int width = bytes.get<int>();
  int height = bytes.get<int>();
  int channels = bytes.get<int>();
  data.image = cv::Mat(height, width, CV_MAKETYPE(CV_8U, channels));
  std::memcpy(data.image.data, bytes.get_raw(), data.image.total() * data.image.elemSize());
  return data;
}