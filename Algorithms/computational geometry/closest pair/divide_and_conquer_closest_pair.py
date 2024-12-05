import numpy as np
import helper_functions as hf
import brute_force_closest_pair as bfcp

def create_strip(points_list, d, mid_point):
    """
    This function creates a strip of points that are within a distance ``d`` to the left and right of the middle point, ``mid_point``.
    :param points_list: 2D array of points.
    :param d: Distance between the closest pair of points found from the recursive calls.
    :param mid_point: Point in the middle of the 2D array of points sorted by x-coordinate.
    :return: 2D array of points within a distance ``d`` to the left and right of the middle point, ``mid_point``.
    """
    # Create an empty 2D array to store the strip of points.
    strip = np.empty((0, 2), dtype=int)

    # Loop through the 2D array of points, ``points_list``
    for point in points_list:
        # Check if the point is within a distance ``d`` to the left and right of the middle point, ``mid_point``.
        if abs(point[0] - mid_point[0]) < d:
            # If so, append the point to the strip.
            strip = np.append(strip, [point], axis=0)

    # Return the strip of points.
    return strip


def closest_pair_divide_and_conquer(d, points_list):
    """
    This function finds the closest pair of points in the 2D array ``points_list`` and the distance between the two points using the divide and conquer method. It also returns the sorted 2D array of points by y-coordinate.

    :param d: Distance between the closest pair of points found from the recursive calls.
    :param points_list: 2D array of points.
    :return: Distance between the two closest points, ``d``, the two closest points, ``closest_pair``, and the sorted 2D array of points by y-coordinate, ``points_list``.
    """

    # Base case: If the 2D array of points has less than 3 points, use the brute force method.
    if len(points_list) <= 3:
        # Brute force method
        d, closest_pair = bfcp.closest_pair(points_list)

        # Sort the 2D array of points by y-coordinate.
        points_list = hf.merge_sort(0, len(points_list) - 1, points_list, 'y')

        # Return the distance between the two closest points, ``d``, the two closest points, ``closest_pair``, and the sorted 2D array of points by y-coordinate, ``points_list``.
        return d, points_list, closest_pair

    # Find the index of middle point of the 2D array of points.
    mid = int(np.floor(len(points_list) / 2))

    # Find the middle point of the 2D array of points.
    mid_point = points_list[mid]

    # Recursively find the closest pair of points in the left and right halves of the 2D array of points.
    d1, points_list1, closest_pair1 = closest_pair_divide_and_conquer(d, points_list[0:mid])
    d2, points_list2, closest_pair2 = closest_pair_divide_and_conquer(d, points_list[mid:len(points_list)])

    # Merge the two 2D arrays of points.
    points_list = np.concatenate((points_list1, points_list2), axis=0)
    points_list = hf.merge_sort(0, len(points_list) - 1, points_list, 'y')

    # Find the smallest distance between the two closest pairs of points from the recursive calls.
    d = min(d1, d2)

    # Set the closest pair of points to the closest pair of points from the recursive calls.
    closest_pair = closest_pair1 if d == d1 else closest_pair2

    # Create a strip of points that are within a distance ``d`` to the left and right of the middle point, ``mid_point``.
    strip = create_strip(points_list, d, mid_point)

    # Loop through the strip of points.
    for i in range(len(strip)):
        # Initialize the index of the point in the strip that is being compared to the other points in the strip.
        j = 1

        # Loop through the strip of points.
        # Stop the loop if the sum of the indexes of the points being compared is greater than pr equal the length of the strip or
        # if the index of the point being compared is greater than 7.
        while (i + j) < len(strip) and j <= 7:

            # If the distance between the two points is less than the current distance, ``d``,
            # then update the distance, ``d``, and the two closest points, ``closest_pair``.
            if hf.euclidean_distance(strip[i], strip[i + j]) < d:
                d = hf.euclidean_distance(strip[i], strip[i + j])
                closest_pair = np.array([strip[i]])
                closest_pair = np.append(closest_pair, [strip[i + j]], axis=0)

            # Increment the index of the point in the strip that is being compared to the other points in the strip.
            j += 1

    # Return the distance between the two closest points, ``d``, the two closest points, ``closest_pair``, and the sorted 2D array of points by y-coordinate, ``points_list``.
    return d, points_list, closest_pair

def closest_pair(points_list):
    """
    This function finds the closest pair of points in the 2D array ``points_list`` and the distance between the two points using the divide and conquer method, as well assorts the 2D array of points by y-coordinate. The function includes preprocessing to sort the 2D array of points by x-coordinate.

    :param points_list: 2D array of points.
    :return: Distance between the two closest points, ``d``, the two closest points, ``closest_pair``, and the sorted 2D array of points by y-coordinate, ``points_list``.
    """

    # Preprocessing: Sort the 2D array of points by x-coordinate.
    points_list = hf.merge_sort(0, len(points_list) - 1, points_list, 'x')

    # Initialize the distance between the two closest points, ``d``, to the distance between the first two points in the 2D array of points.
    d = hf.euclidean_distance(points_list[0], points_list[1])

    # Run the divide and conquer algorithm to find the closest pair of points in the 2D array of points.
    distance, points_list, closest_pair = closest_pair_divide_and_conquer(d, points_list)

    # Return the distance between the two closest points, ``d``, the two closest points, ``closest_pair``, and the sorted 2D array of points by y-coordinate, ``points_list``.
    return distance, points_list, closest_pair
