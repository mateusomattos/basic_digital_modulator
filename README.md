# Digital Communications Simulator
This project implements a basic digital communications system simulator in C. It allows users to generate bit sequences, modulate these bits into IQ (In-phase and Quadrature) samples, simulate channel effects like free-space path loss and Additive White Gaussian Noise (AWGN), and visualize the resulting constellation diagram.

## Features
* Bit Generation: Creates random binary bit sequences for simulation purposes.
* Digital Modulation: Supports various modulation schemes (e.g., BPSK, QPSK, 16QAM).
* Channel Simulation:Free-Space Path Loss (FSPL): Attenuates the signal based on propagation distance and carrier frequency.
* Additive White Gaussian Noise (AWGN): Adds random noise to the signal based on the Eb/N0 ratio.
* Visualization: Generates constellation diagrams as PNG image files for visual analysis of the signal quality.
* Command-Line Configuration: All simulation parameters are configurable via command-line arguments.

## Prerequisites
To compile and run this project, you'll need:

* gcc
* make
* Gnuplot

## How to Compile
Navigate to the project's root directory and run the make command:
```
make
```
This will create the simulator executable in the bin/ directory.

## How to Run
The simulator is executed via the command line, with options to configure the simulation.

Basic Usage
```
./bin/simulator -b <number_of_bits> -m <modulation_type> -r <sample_rate> -f <carrier_frequency> [OPTIONS]
```

### Examples
1. Simulate with an input file, QPSK modulation, 100 kHz sample rate, 2.4 GHz carrier frequency, 15 dB Eb/N0, 20m channel distance:
```
./bin/simulator -b 1000 -m QPSK -r 100000 -f 2.4e9 --EbN0=15.0 -d 20
```
### Available Options
* `-m, --modulation <type>`: Modulation type (e.g., BPSK, QPSK, 16QAM).
* `-r, --sample-rate <rate>`: Sample rate in Hz. 
* `-f, --freq <frequency>`: Carrier frequency in Hz. 
* `-b, --bits <number>`: Number of bits to simulate.
* `-n, --EbN0 <SNR_dB> `: Adds AWGN.
* `-d, --channel-distance <m>`: Simulates channel loss based on distance in meters.
* `-s, --sdr`: Enables SDR (Software Defined Radio) transmit mode. (TODO)
* `-h, --help`: Displays the help message and exits.