import numpy as np
import matplotlib.pyplot as plt

def euclidean_distance(p1, p2):
    """
    This function calculates the Euclidean distance, ``d`` between two points, ``p1`` and ``p2``.

    :param p1: The first point.
    :param p2: The second point.
    :return: Euclidean distance between the two points.
    """
    # Get the difference between the x and y coordinates
    x = p1[0] - p2[0]
    y = p1[1] - p2[1]

    # Square the differences
    x_2 = x ** 2
    y_2 = y ** 2

    # Get the Euclidean distance
    d = np.sqrt(x_2 + y_2)
    return d

def plot_points(points, closest_pair=None, width=10, height=10):
    """
    This function plots the points in the given 2D array ``points``, as well as a line between the closest pair of points in the 2D array, ``closest_pair``.

    :param points: 2D array of points to plot.
    :param closest_pair: 2D array of the closest pair of points to draw a line between.
    :param width: Width of the plot.
    :param height: Height of the plot.
    :return: Displays the plot.
    """

    # Unpack the 2D array points into two 1D arrays, x_points and y_points
    x_points = points[:, 0]
    y_points = points[:, 1]

    # Set the plot size.
    plt.figure(figsize=(width, height))

    # Check if closest pair was passed.
    # If so, plot the points in the 2D array and plot the line between the closest pair.
    # Otherwise, just plot the points in the 2D array.
    if closest_pair is not None:
        plt.plot(closest_pair[:, 0], closest_pair[:, 1], color='r')

    # Plot the points in the 2D array as points shaped like circles.
    plt.plot(x_points, y_points, 'o')

    # Set the x and y axis labels.
    plt.xlabel('x-axis')
    plt.ylabel('y-axis')

    # Set the title of the plot.
    plt.title('Random points set')

    # Set the x and y axis ranges.
    plt.xticks(np.arange(min(x_points), max(x_points) + 1, 1.0))
    plt.yticks(np.arange(min(y_points), max(y_points) + 1, 1.0))

    # Set the grid lines.
    plt.grid()

    # Display the plot.
    plt.savefig('2333776_random-points.pdf', format='pdf', bbox_inches='tight')


def merge(left_start, left_end, right_start, right_end, points_list, mode):
    """
    This function merges the two sorted sublists into a single sorted list. the two sublists are defined by the indices ``left_start`` and ``left_end`` for the left sublist and ``right_start`` and ``right_end`` for the right sublist.

    :param left_start: The starting index of the left sublist.
    :param left_end: The ending index of the left sublist.
    :param right_start: The starting index of the right sublist.
    :param right_end: The ending index of the right sublist.
    :param points_list: The list of points to sort.
    :param mode: Sort by x or y.
    :return: Sorted list of points.
    """
    # Sort the points in the left sublist by x or y coordinate.
    if mode == 'x':
        column = 0
    elif mode == 'y':
        column = 1
    # Initialize a temporary list to store the sorted points.
    temp_list = np.empty((len(points_list), 2), dtype=int)

    # Initialize the indices for the left and right sublists.
    i = 0
    j = 0

    # Populate the temporary list with the points in the left sublist.
    for i in range(left_end, left_start - 1, -1):
        temp_list[i] = points_list[i]

    # Populate the temporary list with the points in the right sublist.
    for j in range(right_start, right_end + 1):
        temp_list[right_end + right_start - j] = points_list[j]

    # Set the indices for the left and right sublists.
    i = left_start
    j = right_end

    # Iterate through the temporary list and sort the points.
    for k in range(left_start, right_end + 1):
        # If the value at index ``i`` in the left sublist is less than the value at index ``j`` in the right sublist,
        # then set the value at index ``k`` in the temporary list to the value at index ``i`` in the left sublist.
        if temp_list[i][column] < temp_list[j][column]:
            points_list[k] = temp_list[i]
            i += 1
        # Otherwise, set the value at index ``k`` in the temporary list to the value at index ``j`` in the right sublist.
        else:
            points_list[k] = temp_list[j]
            j -= 1

    # Return the sorted list of points.
    return points_list

def merge_sort(left, right, points_list, mode):
    """
    This function sorts the points in the list ``points_list`` using the merge sort algorithm.

    :param left: The left index of the list.
    :param right: The right index of the list.
    :param points_list: The list of points to sort.
    :param mode: Sort by x or y.
    :return: Sorted list of points.
    """

    # If the left index is less than the right index, then sort the list.
    if right - left > 0:
        # Find the middle index of the list.
        mid = int(np.floor((left+right)/2))

        # Recursively sort the left and right sublists.
        points_list = merge_sort(left, mid, points_list, mode)
        points_list = merge_sort(mid+1, right, points_list, mode)

        # Merge the two sorted sublists.
        points_list = merge(left, mid, mid+1, right, points_list, mode)

        # Return the sorted list of points.
        return points_list

    # If the left index is equal to the right index, then return the list.
    return points_list

def write_tests_to_file(file_name, test_data):
    """
    This function writes the test data to a file. It writes the test data to a file in the format:

    ``input,time``

    where ``input`` is the input data size and ``time`` is the time it took to run the algorithm.
    :param file_name: The name of the file to write to.
    :param test_data: 2D array of test data.
    :return: File with test data.
    """
    with open(file_name, 'w') as file:
        file.write(f"input,time\n")

    with open(file_name, 'a') as file:
        for test_case in test_data:
            file.write(f"{test_case[0]},{test_case[1]}\n")