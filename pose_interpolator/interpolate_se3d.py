import numpy as np

from .pose_interpolator_pybind import _interpolate_se3d, _InterpolateSE3d


def interpolate_se3d(t: float, pose1: np.ndarray, pose2: np.ndarray) -> np.ndarray:
    """
    Interpolate between two SE(3) poses.
    Args:
        t: Interpolation factor in [0, 1] where 0=pose1, 1=pose2
        pose1: Start pose as 4x4 numpy array
        pose2: End pose as 4x4 numpy array
    Returns:
        Interpolated 4x4 transformation matrix
    """
    return _interpolate_se3d(t, pose1, pose2)


class InterpolateSE3d:
    """
    Class-based SE(3) pose interpolator for repeated interpolation between
    fixed start and end poses.

    Example:
    >>> interpolator = InterpolateSE3d(pose_start, pose_end)
    >>> pose_0_5 = interpolator.interpolate(0.5)
    """

    def __init__(self, pose1: np.ndarray, pose2: np.ndarray):
        """
        Initialize interpolator with start and end poses.
        Args:
            pose1: Start pose as 4x4 numpy array
            pose2: End pose as 4x4 numpy array
        """
        self._impl = _InterpolateSE3d(pose1, pose2)

    def interpolate(self, t: float) -> np.ndarray:
        """
        Perform interpolation at factor t.
        Args:
            t: Interpolation factor in [0, 1]
        Returns:
            Interpolated 4x4 transformation matrix
        """
        return self._impl.interpolate(t)
