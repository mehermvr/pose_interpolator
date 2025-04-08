# SE(3) Pose Interpolation

A minimal Python package for SE(3) pose interpolation between 4x4 transformation matrices, implemented in C++ with pybind11 and Sophus.

## Installation

```bash
pip install "pose_interpolator @ git+https://github.com/mehermvr/pose_interpolator.git"
```


## Usage

You want

$$
T(t) = T_0 \exp(t \cdot \log(T_0^{-1} T_1))
$$

Where:
- $T_0$ = Start SE3 pose
- $T_1$ = End SE3 pose
- $t$ = Interpolation factor ∈ [0,1]
- $\exp$ = Group exponential 
- $\log$ = Group logarithm

```python
import numpy as np
from pose_interpolator import interpolate_se3d, InterpolateSE3d
# ...
interpolate_se3d(t, pose1, pose2)
# ...
interpolator = InterpolateSE3d(pose1, pose2)
pose_0_25 = interpolator.interpolate(0.25)
pose_0_75 = interpolator.interpolate(0.75)
# ...
```
