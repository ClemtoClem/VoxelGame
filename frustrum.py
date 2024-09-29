import numpy as np
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
import matplotlib.pyplot as plt

# setup --------------------------------------------------------------------------------

camera_position = [3, 0, 1]
camera_yaw = 20
camera_pitch = 30

field_of_view = 70
z_near_plane = 0.5
z_far_plane = 3
aspect_ratio = 16 / 9

# functions ----------------------------------------------------------------------------

def render_frustum(points, camera_pos, ax):
    line_indices = [
        [0, 1],
        [0, 2],
        [0, 4],
        [1, 3],
        [1, 5],
        [2, 3],
        [2, 6],
        [3, 7],
        [4, 5],
        [4, 6],
        [5, 7],
        [6, 7],
    ]
    for idx_pair in line_indices:
        line = np.transpose([points[idx_pair[0]], points[idx_pair[1]]])
        ax.plot(line[0], line[2], line[1], "r")
    ax.set_xlim([-5, 5])
    ax.set_ylim([-5, 5])
    ax.set_zlim([-5, 5])
    ax.set_xlabel("x")
    ax.set_ylabel("z")
    ax.set_zlabel("y")
    ax.plot([-5, 5], [0, 0], [0, 0], "k")
    ax.plot([0, 0], [-5, 5], [0, 0], "k")
    ax.plot([0, 0], [0, 0], [-5, 5], "k")
    if camera_pos is not None:
        ax.scatter(
            camera_pos[0], camera_pos[2], camera_pos[1], marker="o", color="g", s=30
        )

def get_perspective_mat(fov_deg, z_near, z_far, aspect_ratio):
    fov_rad = fov_deg * np.pi / 180
    f = 1 / np.tan(fov_rad / 2)

    return np.array(
        [
            [f / aspect_ratio, 0, 0, 0],
            [0, f, 0, 0],
            [
                0,
                0,
                (z_far + z_near) / (z_near - z_far),
                2 * z_far * z_near / (z_near - z_far),
            ],
            [0, 0, -1, 0],
        ]
    )

def get_rotation_mat_x(angle_rad):
    s = np.sin(angle_rad)
    c = np.cos(angle_rad)
    return np.array(
        [[1, 0, 0, 0], [0, c, -s, 0], [0, s, c, 0], [0, 0, 0, 1]], dtype=float
    )

def get_rotation_mat_y(angle_rad):
    s = np.sin(angle_rad)
    c = np.cos(angle_rad)
    return np.array(
        [[c, 0, s, 0], [0, 1, 0, 0], [-s, 0, c, 0], [0, 0, 0, 1]], dtype=float
    )

def get_translation_mat(position):
    return np.array(
        [
            [1, 0, 0, position[0]],
            [0, 1, 0, position[1]],
            [0, 0, 1, position[2]],
            [0, 0, 0, 1],
        ],
        dtype=float,
    )

def get_world_to_view_matrix(pitch_deg, yaw_deg, position):
    pitch_rad = np.pi / 180 * pitch_deg
    yaw_rad = np.pi / 180 * yaw_deg

    orientation_mat = np.matmul(
        get_rotation_mat_x(-pitch_rad), get_rotation_mat_y(-yaw_rad)
    )
    translation_mat = get_translation_mat(-1 * np.array(position, dtype=float))
    return np.matmul(orientation_mat, translation_mat)

# script -------------------------------------------------------------------------------

points_clip = np.array(
    [
        [-1, -1, -1, 1],
        [ 1, -1, -1, 1],
        [-1,  1, -1, 1],
        [ 1,  1, -1, 1],
        [-1, -1,  1, 1],
        [ 1, -1,  1, 1],
        [-1,  1,  1, 1],
        [ 1,  1,  1, 1],
    ],
    dtype=float,
)

M_wv = get_world_to_view_matrix(camera_pitch, camera_yaw, camera_position)
M_vc = get_perspective_mat(field_of_view, z_near_plane, z_far_plane, aspect_ratio)

M_vw = np.linalg.inv(M_wv)
M_cv = np.linalg.inv(M_vc)
# M_cw = np.matmul(M_vw, M_cv) # direct clip to world transformation

# alternative:
# M_wc = np.matmul(M_vc, M_wv)
# M_cw = np.linalg.inv(M_wc)

points_view = []
points_world = []
for i in range(8):
    points_view.append(np.matmul(M_cv, points_clip[i]))
    points_view[i] = points_view[i] / points_view[i][3]
    points_world.append(np.matmul(M_vw, points_view[i]))
    # alternative
    # points_world.append(np.matmul(M_cw, points_clip[i]))
    # points_world[i] = points_world[i] / points_world[i][3]

# plot everything ----------------------------------------------------------------------

fig = plt.figure()
ax_clip_space = fig.add_subplot(111, projection="3d")
render_frustum(points=points_clip, camera_pos=None, ax=ax_clip_space)
ax_clip_space.set_title("view frustum in clip space")

fig = plt.figure()
ax_view = fig.add_subplot(111, projection="3d")
render_frustum(points=points_view, camera_pos=[0, 0, 0], ax=ax_view)
ax_view.set_title("view frustum in view space")

fig = plt.figure()
ax_world = fig.add_subplot(111, projection="3d")
render_frustum(points=points_world, camera_pos=camera_position, ax=ax_world)
ax_world.set_title("view frustum in world space")

plt.show()
