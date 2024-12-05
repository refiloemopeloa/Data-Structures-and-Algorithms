import numpy as np
import helper_functions as hf


def closest_pair(points_list):
    """
    This function finds the closest pair of points in the 2D array ``points_list`` and the distance between the two points using the brute force method.

    :param points_list: 2D array of points.
    :return: The distance between the two closest points, ``d`` and the two closest points, ``closest_pair``.
    """

    # Initialize the distance, ``d``, as the distance between the first two points
    d = hf.euclidean_distance(points_list[0], points_list[1])
    # Initialize the two closest points, ``closest_pair``, as the first two points.
    closest_pair = np.array([points_list[0]])
    closest_pair = np.append(closest_pair, [points_list[1]], axis=0)

    # Loop through the 2D array of points, ``points_list``
    for i in range(0, len(points_list)):
        # Compare the point at index ``i`` with the points at indices ``j``, where ``j`` is greater than ``i``
        # This is to avoid comparing a point with itself and comparing a point with a point that has already been compared.
        for j in range(i + 1, len(points_list)):
            # If the distance between the two points is less than the current distance, ``d``,
            # then update the distance, ``d``, and the two closest points, ``closest_pair``.
            if hf.euclidean_distance(points_list[i], points_list[j]) < d:
                d = hf.euclidean_distance(points_list[i], points_list[j])
                closest_pair = np.array([points_list[i]])
                closest_pair = np.append(closest_pair, [points_list[j]], axis=0)
    return d, closest_pair