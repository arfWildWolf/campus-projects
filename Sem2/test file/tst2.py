from SALib.analyze import sobol
from SALib.sample import sobol as sobol_sample  # Updated import for SALib 1.5.1+
import numpy as np

# Define the problem with 14 parameters
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

# Choose N as a power of 2 (e.g., 256 or 512) to avoid convergence issues
N = 256  

# Generate Sobol samples (Note: calc_second_order=True must match in analyze)
param_values = sobol_sample.sample(problem, N, calc_second_order=True)

# Simulate model output (Replace with real NPV computation)
Y = np.sum(param_values, axis=1)  # Placeholder function

# *Do NOT filter Y before analysis* - Sobol requires all samples
Si = sobol.analyze(problem, Y, calc_second_order=True)  # Must match sample()

# Print Sobol indices
print("First-order Sobol indices:")
print(Si['S1'])
print("Total-order Sobol indices:")
print(Si['ST'])

# Now, filter valid cases where net energy is positive *after* sensitivity analysis
valid_indices = np.where(Y > 0)[0]
param_values = param_values[valid_indices]
Y = Y[valid_indices]

# Ensure we only keep 2,394 cases
if len(Y) > 2394:
    param_values = param_values[:2394]
    Y = Y[:2394]

print(f"Total valid cases after filtering: {len(Y)}")