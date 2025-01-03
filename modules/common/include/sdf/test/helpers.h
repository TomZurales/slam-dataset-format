#pragma once

float randomFloat(float min, float max)
{
  return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

std::string randomString(size_t length)
{
  auto randchar = []() -> char
  {
    const char charset[] = "0123456789"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[rand() % max_index];
  };
  std::string str(length, 0);
  std::generate_n(str.begin(), length, randchar);
  return str;
}

int randomInt(int min, int max)
{
  return rand() % (max - min + 1) + min;
}