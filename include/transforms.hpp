#ifndef _OCTOBER_TRANSFORMS_HPP_
#define _OCTOBER_TRANSFORMS_HPP_

#include "types.hpp"

namespace october {


std::shared_ptr<image_t> translated_image(std::shared_ptr<const image_t> img, const vec2f_t& offset);

std::shared_ptr<image_t> rotated_image(std::shared_ptr<const image_t> img, float theta, const vec2f_t& center);

affine2f_t origin_rotation(float rad);

affine2f_t center_rotation(std::shared_ptr<const image_t> img, float rad);

std::shared_ptr<image_t> affine_transformed_image(std::shared_ptr<const image_t> img, const affine2f_t& transform, float background);

void affine_transform_image(std::shared_ptr<image_t> img, const affine2f_t& transform, float background);

Eigen::Matrix3f image_transform(const bbox2f_t& bbox, uint32_t width, uint32_t height, uint32_t border = 0);

vec2f_t image_transform_1d(float min_value, float max_value, uint32_t height, uint32_t border = 0);

template <int D>
Eigen::Matrix<float, D+1, D+1> affine_image_transform(const Eigen::AlignedBox<float, D>& bbox, const Eigen::Matrix<int, D, 1>& img_size, int border = 0);

std::shared_ptr<image_t> to_log_polar(std::shared_ptr<const image_t> img, vec2f_t center, uint32_t width, uint32_t height);


#include "impl/transforms.hpp"


} // october

#endif /* _OCTOBER_TRANSFORMS_HPP_ */
