#!/bin/bash

# Compile all individual function codes using Catch2 defined main for unit testing
echo "Compiling unit testing executables(this may take some time!)..."
make tests

# Execute all tests for unit testing, add your executable down here to add to the unit testing script...
echo "Begin all unit tests..."
./tests

echo "Cleaning..."
make clean_tests
