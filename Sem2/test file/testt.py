from SALib.analyze import sobol
from SALib.sample import saltelli
import numpy as np

# Define the model problem with 14 parameters
problem = {
    'num_vars': 14,
    'names': [
        'Pipe Diameter', 'Brine inflow Flow', 'Pipe Length', 'Electricity price', 
        'Yearly operating', 'Membrane price', 'Life span', 'Draw concentration', 
        'Feed concentration', 'TFC membrane replacement', 'HFC plant elevation', 
        'Plant capacity', 'Turbine efficiency', 'TBSWDP elevation'
    ],
    'bounds': [
        [0.3, 1.0], [0.1, 0.5], [10, 100], [0.01, 0.2], 
        [0.01, 0.1], [0.001, 0.01], [0.001, 0.01], [0.0001, 0.002], 
        [0.00001, 0.0001], [1e-6, 1e-5], [1e-7, 1e-6], [1e-7, 1e-6], 
        [1e-8, 1e-7], [1e-8, 1e-7]
    ]
}

# Generate samples using Saltelli's sampling method
param_values = saltelli.sample(problem, 2394)

# Example model output (replace with real model results)
# Here we use a simple sum of inputs as a placeholder
Y = np.sum(param_values, axis=1)

# Perform Sobol sensitivity analysis
Si = sobol.analyze(problem, Y)

# Print the Sobol indices
print("First-order Sobol indices:")
print(Si['S1'])
print("Total-order Sobol indices:")
print(Si['ST'])