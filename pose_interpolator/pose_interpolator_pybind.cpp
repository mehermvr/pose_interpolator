#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <sophus/se3.hpp>

namespace py = pybind11;
using namespace py::literals;

namespace Eigen {
using Matrix4d = Matrix<double, 4, 4>;
using Vector6d = Matrix<double, 6, 1>;

} // namespace Eigen

namespace {
Eigen::Matrix4d interpolate_se3d(const double t, const Eigen::Matrix4d &mat1,
                                 const Eigen::Matrix4d &mat2) {
  const Sophus::SE3d pose1(mat1);
  const Sophus::SE3d pose2(mat2);
  return (pose1 * Sophus::SE3d::exp(t * (pose1.inverse() * pose2).log()))
      .matrix();
}

class InterpolateSE3d {
public:
  InterpolateSE3d(const Eigen::Matrix4d &mat1, const Eigen::Matrix4d &mat2)
      : _pose1(mat1), _pose2(mat2) {
    _log = (_pose1.inverse() * _pose2).log();
  }

  Eigen::Matrix4d interpolate(const double t) const {
    return (_pose1 * Sophus::SE3d::exp(t * _log)).matrix();
  }

private:
  Sophus::SE3d _pose1;
  Sophus::SE3d _pose2;
  Eigen::Vector6d _log;
};
} // namespace

PYBIND11_MODULE(pose_interpolator_pybind, m) {
  m.def("_interpolate_se3d", &interpolate_se3d, "t"_a, "mat1"_a, "mat2"_a,
        "Interpolate between two SE(3) poses");

  py::class_<InterpolateSE3d>(m, "_InterpolateSE3d")
      .def(py::init<const Eigen::Matrix4d &, const Eigen::Matrix4d &>())
      .def("interpolate", &InterpolateSE3d::interpolate, "t"_a);
}
