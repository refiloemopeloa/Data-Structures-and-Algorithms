import matplotlib.pyplot as plt
import numpy as np

# Data from the table
input_sizes = [2, 3, 4, 5, 8, 9, 16, 25, 27, 32, 64, 81, 125, 128, 243, 256, 512, 625, 729, 1024]
recursive_times = [2.55667e-07, 1.11367e-06, 1.00367e-06, 8.55567e-06, 7.10367e-06, 5.8538e-05, 5.77917e-05, 
                  0.000501413, 0.000493333, 0.000494776, 0.00394825, 0.032492, 0.0305851, 0.0298259, 
                  0.243983, 0.249034, 1.97856, 15.9643, 16.0092, 15.9565]
strassen_times = [3.52667e-07, 2.43633e-06, 2.369e-06, 1.79227e-05, 1.7478e-05, 0.000127731, 0.000124577, 
                 0.000889892, 0.000893455, 0.000925646, 0.00640195, 0.0441623, 0.0447836, 0.0441484, 
                 0.31831, 0.32025, 2.31955, 17.7837, 17.6625, 17.9433]
iterative_times = [9.43333e-08, 3.02667e-07, 2.62667e-07, 2.104e-06, 1.84833e-06, 1.4448e-05, 1.43843e-05, 
                  0.000112636, 0.000111901, 0.000112672, 0.000850411, 0.00681176, 0.00683504, 0.00663569, 
                  0.0548831, 0.0548318, 0.508981, 4.53272, 4.46113, 4.35723]

# Create the plot
plt.figure(figsize=(12, 8))

# Plot each algorithm with different colors and markers
plt.plot(input_sizes, recursive_times, 'b-o', label='Recursive', linewidth=2, markersize=6)
plt.plot(input_sizes, strassen_times, 'r-s', label='Strassen', linewidth=2, markersize=6)
plt.plot(input_sizes, iterative_times, 'g-^', label='Iterative', linewidth=2, markersize=6)

# Set log scale for both axes to better visualize the wide range of values
plt.xscale('log')
plt.yscale('log')

# Set labels and title
plt.xlabel('Input Size', fontsize=14)
plt.ylabel('Run Time (seconds)', fontsize=14)
plt.title('Complexity of different matrix multiplication algorithms', fontsize=16, fontweight='bold')

# Add grid for better readability
plt.grid(True, which='both', linestyle='--', alpha=0.7)

# Add legend
plt.legend(fontsize=12)

# Customize tick parameters
plt.tick_params(axis='both', which='major', labelsize=12)

# Add some padding for better visualization
plt.tight_layout()

# Show the plot
plt.show()

# Optional: Save the plot as an image file
# plt.savefig('matrix_multiplication_complexity.png', dpi=300, bbox_inches='tight')