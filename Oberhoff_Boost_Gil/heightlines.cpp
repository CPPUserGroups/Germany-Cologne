#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/gil_all.hpp>
#include <boost/gil/pixel_iterator.hpp>
#include <boost/gil/extension/io/png_io.hpp>

#include <boost/mpl/vector.hpp>

#include <cstdint>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

struct height_t{};
typedef boost::mpl::vector1<height_t> srtm_t;
typedef boost::gil::layout<srtm_t> srtm_layout_t;
typedef boost::gil::pixel<boost::gil::bits16, srtm_layout_t> srtm_pixel_t;
typedef boost::gil::image<srtm_pixel_t, false> SrtmImage;

typedef boost::gil::layout<boost::gil::gray_t> gray_layout_t;
typedef boost::gil::pixel<boost::gil::bits8, gray_layout_t> gray_pixel_t;
typedef boost::gil::image<gray_pixel_t, false> GrayImage;

static const size_t srtm2_size = 1201;

// implements srtm pixel reading with endianness swapping
// todo: use boost::endian
template<typename istream_t> 
istream_t& operator >>(istream_t &is, srtm_pixel_t& pixel)
{
    is.read((char*)&pixel, sizeof(pixel));
    char* pixel_bytes = (char*)&pixel;
    std::swap(pixel_bytes[0], pixel_bytes[1]);
    return is;
} 

SrtmImage read_srtm3(const std::string& path)
{
    std::ifstream dataFile(path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    size_t length;
    if(!dataFile.std::ios::good())
    {
      throw std::runtime_error("requested srtm file '" + path + "' not readable, possibly does not exist");
    }
    length = dataFile.tellg();
    assert(length == srtm2_size * srtm2_size * sizeof(int16_t));

    dataFile.seekg(0, std::ios::beg);
    SrtmImage result(1201, 1201);
    std::copy(std::istream_iterator<srtm_pixel_t>(dataFile), std::istream_iterator<srtm_pixel_t>(),
              boost::gil::view(result).begin());
    return result;
}

int16_t next_height_line(int16_t value)
{
    const int16_t delta = 100;
    return ((value + delta - 1) / delta) * delta;
}

int16_t previous_height_line(int16_t value)
{
    const int16_t delta = 100;
    return (value / delta) * delta;
}

int main(int argc, const char** argv)
{
    SrtmImage srtm_image = read_srtm3(argv[1]);
    boost::gil::rgb8_image_t out_image(srtm_image.width(), srtm_image.height());

    auto srtm_view = boost::gil::const_view(srtm_image);
    auto out_view = boost::gil::view(out_image);

    for (size_t y = 1; y < srtm_image.height(); ++y)
    {
        auto srtm_iter = srtm_view.row_begin(y);
        auto srtm_iter_top = srtm_view.row_begin(y - 1);
        auto out_iter = out_view.row_begin(y);
        for (size_t x = 1; x < srtm_image.width() - 1; ++x)
        {
            int16_t left = next_height_line(boost::gil::get_color(srtm_iter[x - 1], height_t()));
            int16_t top = next_height_line(boost::gil::get_color(srtm_iter_top[x], height_t()));
            int16_t here = next_height_line(boost::gil::get_color(srtm_iter[x], height_t()));

            if (left > 0 && top > 0 && here > 0 &&  (left != here || top != here))
            {
                out_iter[x] = boost::gil::rgb8_pixel_t(0, 0, 0);
            }
            else if (here >= 0)
            {
                unsigned char white_part = std::min<int16_t>(255, std::pow(float(here), 0.4f) * 13);
                out_iter[x] = boost::gil::rgb8_pixel_t(white_part, 255, white_part);
            }
            else
            {
                out_iter[x] = boost::gil::rgb8_pixel_t(255, 255, 255);   
            }
        }
    }
    
    boost::gil::png_write_view(argv[1] + std::string(".png"), out_view);
    return 0;
}