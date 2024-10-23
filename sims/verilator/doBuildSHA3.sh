#!/bin/bash

# Set the environment variables and build the SHA3 binary
source ../../env.sh
cd ../../tests
./doBuildSHA3.sh
cd ../sims/verilator

# Display the menu and read user's choice
echo "eFPGA Simulation"
echo "================"
echo "at any time, press Ctrl+C to exit"
echo "Choose target type:"
echo "0. debug"
echo "1. release"
read -p "Target type [0-1]: " target

echo "Choose benchmark:"
echo "0. SHA3-512"
echo "1. SHA3-256"
read -p "Benchmark [0-1]: " benchmark

echo "Choose system bus width:"
echo "0. 64Bit"
echo "1. 32Bit"
read -p "Bus width [0-1]: " bus

echo "Choose throughput:"
echo "0. High"
echo "1. Low"
read -p "Throughput [0-1]: " throughput

# Execute the command based on the user's choice
case $target in
    0)
        echo "You chose debug"
        case $benchmark in
            0)
                echo "You chose SHA3-512"
                case $bus in
                    0)
                        echo "You chose 64Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-512High64Bit.riscv CONFIG=HazemConfig512High64Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-512Low64Bit.riscv CONFIG=HazemConfig512Low64Bit
                                ;;
                        esac
                        ;;
                    1)
                        echo "You chose 32Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-512High32Bit.riscv CONFIG=HazemConfig512High32Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-512Low32Bit.riscv CONFIG=HazemConfig512Low32Bit
                                ;;
                        esac
                        ;;
                esac
                ;;
            1)
                echo "You chose SHA3-256"
                case $bus in
                    0)
                        echo "You chose 64Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-256High64Bit.riscv CONFIG=HazemConfig256High64Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-256Low64Bit.riscv CONFIG=HazemConfig256Low64Bit
                                ;;
                        esac
                        ;;
                    1)
                        echo "You chose 32Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-256High32Bit.riscv CONFIG=HazemConfig256High32Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3-256Low32Bit.riscv CONFIG=HazemConfig256Low32Bit
                                ;;
                        esac
                        ;;
                esac
                ;;
        esac
        ;;
    1)
        echo "You chose release"
        case $benchmark in
            0)
                echo "You chose SHA3-512"
                case $bus in
                    0)
                        echo "You chose 64Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-512High64Bit.riscv CONFIG=HazemConfig512High64Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-512Low64Bit.riscv CONFIG=HazemConfig512Low64Bit
                                ;;
                        esac
                        ;;
                    1)
                        echo "You chose 32Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-512High32Bit.riscv CONFIG=HazemConfig512High32Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-512Low32Bit.riscv CONFIG=HazemConfig512Low32Bit
                                ;;
                        esac
                        ;;
                esac
                ;;
            1)
                echo "You chose SHA3-256"
                case $bus in
                    0)
                        echo "You chose 64Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-256High64Bit.riscv CONFIG=HazemConfig256High64Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-256Low64Bit.riscv CONFIG=HazemConfig256Low64Bit
                                ;;
                        esac
                        ;;
                    1)
                        echo "You chose 32Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-256High32Bit.riscv CONFIG=HazemConfig256High32Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3-256Low32Bit.riscv CONFIG=HazemConfig256Low32Bit
                                ;;
                        esac
                        ;;
                esac
                ;;
        esac
        ;;
esac