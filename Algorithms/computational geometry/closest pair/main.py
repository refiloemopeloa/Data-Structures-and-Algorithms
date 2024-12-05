import brute_force_closest_pair as bfcp
import divide_and_conquer_closest_pair as dccp
import points_generator as pg
import time
import numpy as np
import helper_functions as hf
import sys

from brute_force_closest_pair import closest_pair
from points_generator import write_points_to_file


def test_brute_force(points_list):
    """
    This function tests the brute force method. It returns the time taken to find the closest pair of points and the distance between the two points.
    :param points_list: 2D array of points.
    :return: Time taken to find the closest pair of points and the distance between the two points.
    """

    time_taken = 0
    # Start the timer
    time_taken -= time.time_ns()

    # Find the closest pair of points
    bfcp.closest_pair(points_list)

    # Stop the timer
    time_taken += time.time_ns()

    time_taken = round(time_taken/pow(10, 9),15)

    # Return the time taken to find the closest pair of points and the distance between the two points
    return time_taken

def test_divide_and_conquer(points_list):
    """
    This function tests the divide and conquer method. It returns the time taken to find the closest pair of points and the distance between the two points.

    :param points_list: 2D array of points.
    :return: Time taken to find the closest pair of points and the distance between the two points.
    """

    time_taken = 0
    # Start the timer
    time_taken -= time.time_ns()

    # Find the closest pair of points
    dccp.closest_pair(points_list)

    # Stop the timer
    time_taken += time.time_ns()

    time_taken = round(time_taken/pow(10, 9),15)

    # Return the time taken to find the closest pair of points and the distance between the two points
    return time_taken

def build_test_data(data_sizes, times):
    """
    This function builds the test data for an algorithm being tested. It takes in the data sizes and times and returns a 2D array of the data.
    :param data_sizes: 1D array of data sizes.
    :param times: 1D array of times taken.
    :return: 2D array of the data and times takes.
    """

    # Create a 2D array of the data and times taken
    test_data = np.append([data_sizes], [times], axis=0)

    # Transpose the 2D array
    test_data = np.transpose(test_data)

    # Return the 2D array of the data and times taken
    return test_data

def main():
    """
    This function is the main function. It tests the algorithms and saves the data to files.
    :return: Files containing the data and times taken.
    """

    # Store the file names
    file_brute_force = "tests/brute_force_closest_pair.csv"
    file_divide_and_conquer = "tests/divide_and_conquer_closest_pair.csv"

    # Set the number of times to run the algorithm
    power = int(sys.argv[1]) if len(sys.argv) == 2 else 5

    # Create empty arrays to store the times taken
    times_divide_and_conquer = np.empty([0,1],dtype=float)
    times_brute_force = np.empty([0,1],dtype=float)

    # Create an empty array to store the data sizes
    data_sizes = np.empty([0, 1], dtype=int)

    points_list = np.empty([0, 2], dtype=int)

    # Loop through the powers of 2
    for i in range(1, power + 1):
        # Set the data size
        data_size = pow(2, i)

        # Append the data size to the data sizes array
        data_sizes = np.append(data_sizes, data_size)

        # Generate random points
        points_list = pg.get_random_points(data_size)

        # Test the divide and conquer method for the current data size
        time_divide_and_conquer = test_divide_and_conquer(points_list)

        # Append the time taken to the times array
        times_divide_and_conquer = np.append(times_divide_and_conquer, time_divide_and_conquer)

        # Test the brute force method for the current data size
        time_brute_force = test_brute_force(points_list)

        # Append the time taken to the times array
        times_brute_force = np.append(times_brute_force, time_brute_force)

        if i == 4:
            hf.plot_points(points_list, None, 30, 20)
            pg.write_points_to_file(points_list, "2333776_input_data_example.csv")

    # Build the test data for the divide and conquer method
    test_data_divide_and_conquer = build_test_data(data_sizes, times_divide_and_conquer)

    # Write the test data to a file
    hf.write_tests_to_file(file_divide_and_conquer, test_data_divide_and_conquer)

    # Build the test data for the brute force method
    test_data_brute_force = build_test_data(data_sizes, times_brute_force)

    # Write the test data to a file
    hf.write_tests_to_file(file_brute_force, test_data_brute_force)

if __name__ == "__main__":
    main()







