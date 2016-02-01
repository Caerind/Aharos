#ifndef LP_COMPRESSION_HPP
#define LP_COMPRESSION_HPP

#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include <zlib.h>

#include "pugixml.hpp"

namespace lp
{

bool base64_encode(std::string& data);
bool base64_decode(std::string& data);
bool decompressString(std::string& data);
bool compressString(std::string& data);

bool compress(std::string& data);
bool decompress(std::string& data);

bool is_valid_base64(unsigned char c);

void loadCompressedXml(std::string const& filename, pugi::xml_document& doc);
void saveCompressedXml(std::string const& filename, pugi::xml_document const& doc);

} // namespace lp

#endif // LP_COMPRESSION_HPP
