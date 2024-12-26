#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <zx_colors.hpp>
#include <zx_graphics.hpp>

using namespace std;

int main() {
  vector<uint8_t> imageFile(32 * 24 * 8, 0);
  vector<uint8_t> attributeFile(32 * 24, INK_BLACK | PAPER_WHITE);

  zxspectrum::ByteSpan ifs(imageFile.data());
  zxspectrum::BitSpan bits(imageFile.data());

  for (int i = 0; i < 8; ++i) {
    ifs[16, 80 + i] = i;
    ifs[20 + i, 120] = i;
  }

  for (int i = 0; i < 100; ++i) {
    bits[i, i] = 1;
  }

  ofstream myfile;
  myfile.open("myimage.scr");

  // Write to file
  for (auto &byte : imageFile)
    myfile << byte;

  for (auto &byte : attributeFile)
    myfile << byte;

  myfile.close();
}
