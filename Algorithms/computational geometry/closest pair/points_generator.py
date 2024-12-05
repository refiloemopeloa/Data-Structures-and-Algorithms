import numpy as np
import helper_functions as hf

def get_random_points(length):
    """
    This function generates random real-valued points in a 2D space.

    It makes use of the ``numpy.random.uniform``, which generates random numbers over a uniform distribution.

    The numbers are generated in a range of [``-length``, ``length``), with ``length`` rows and two columns.

    Returns a 2D array of random points.

    :param length: Number of rows in the 2D array.
    :return: 2D array of random points.
    """
    random_points = np.random.uniform(low=-length, high=length, size=(length, 2))

    return random_points

def write_points_to_file(points, filename):
    """
    This function writes the points in the 2D array ``points`` to a file ``filename``.
    :param points: 2D array of points to write to the file.
    :param filename: File to write the points to.
    :return: File with the points written to it.
    """
    # Creates the file if it doesn't exist, or overwrites the file if it does.
    with open(filename, 'w') as file:
        file.write(f"x,y\n")
    # Appends the points to the file.
    with open(filename, 'a') as file:
        for point in points:
            file.write(f"{point[0]},{point[1]}\n")

