#include <representation.hpp>

namespace october {


representation::ptr_t
representation::from_files(const std::vector<fs::path>& file_paths, float area_threshold, float angle_threshold, const std::vector<adapter::ptr_t>& adapters) {
    std::vector<std::string> paths(file_paths.size());
    std::vector<std::string> unique_extensions(file_paths.size());
    std::transform(file_paths.begin(), file_paths.end(), paths.begin(), [&] (const fs::path& p) { return p.string(); });
    std::transform(file_paths.begin(), file_paths.end(), unique_extensions.begin(), [&] (const fs::path& p) { return p.extension().string(); });
    std::sort(unique_extensions.begin(), unique_extensions.end());
    auto new_end = std::unique(unique_extensions.begin(), unique_extensions.end());
    unique_extensions.resize(std::distance(unique_extensions.begin(), new_end));
    for (auto adapter : adapters) {
        if (!adapter->supports_extension(unique_extensions)) continue;
        std::string guid;
        auto planes = adapter->extract_planes(paths, area_threshold, angle_threshold, guid);
        return ptr_t(new representation(planes, guid));
    }
    throw std::runtime_error("representation::from_file(const fs::path&): No suitable adapter found.");
}

representation::~representation() {
}

representation::representation(const std::vector<bounded_plane::ptr_t>& planes, const std::string& guid) : planes_(planes), guid_(guid) {
}

const std::vector<bounded_plane::ptr_t>&
representation::planes() const {
    return planes_;
}

void
representation::transform(const mat4f_t& transformation) {
    for (auto p : planes_) {
        p->transform(transformation);
    }
}

void
representation::center(mat4f_t* center_transformation) {
    vec3f_t center = vec3f_t::Zero();
    for (const auto& p : planes_) {
        center += p->origin();
    }
    center /= planes_.size();
    
    mat4f_t trafo = mat4f_t::Identity();
    
    trafo.block<3, 1>(0, 3) = -center;
    
    transform(trafo);
    
    if (center_transformation) {
        *center_transformation = trafo;
    }
}

const std::string&
representation::guid() const {
    return guid_;
};


} // october
