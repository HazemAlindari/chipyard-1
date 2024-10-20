#!/bin/bash

# Display the menu and read user's choice
echo "eFPGA Simulation"
echo "================"
echo "Choose target type:"
echo "0. debug"
echo "1. release"
echo "2. Exit"
read -p "Target type [0-2]: " target

if [ "$target" -eq 2 ]; then
    echo "Exiting..."
    exit 0
fi

echo "Choose benchmark:"
echo "0. SHA3-512"
echo "1. Exit"
read -p "Benchmark [0-1]: " benchmark

if [ "$benchmark" -eq 1 ]; then
    echo "Exiting..."
    exit 0
fi

echo "Choose system bus width:"
echo "0. 64Bit"
echo "1. 32Bit"
echo "2. Exit"
read -p "Bus width [0-2]: " bus

if [ "$bus" -eq 2 ]; then
    echo "Exiting..."
    exit 0
fi

echo "Choose throughput:"
echo "0. High"
echo "1. Low"
echo "2. Exit"
read -p "Throughput [0-2]: " throughput

if [ "$throughput" -eq 2 ]; then
    echo "Exiting..."
    exit 0
fi

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
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3High64Bit.riscv CONFIG=HazemConfigHigh64Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3Low64Bit.riscv CONFIG=HazemConfigLow64Bit
                                ;;
                        esac
                        ;;
                    1)
                        echo "You chose 32Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3High32Bit.riscv CONFIG=HazemConfigHigh32Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary-debug LOADMEM=1 BINARY=../../tests/testSHA3Low32Bit.riscv CONFIG=HazemConfigLow32Bit
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
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3High64Bit.riscv CONFIG=HazemConfigHigh64Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3Low64Bit.riscv CONFIG=HazemConfigLow64Bit
                                ;;
                        esac
                        ;;
                    1)
                        echo "You chose 32Bit"
                        case $throughput in
                            0)
                                echo "You chose High"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3High32Bit.riscv CONFIG=HazemConfigHigh32Bit
                                ;;
                            1)
                                echo "You chose Low"
                                make run-binary LOADMEM=1 BINARY=../../tests/testSHA3Low32Bit.riscv CONFIG=HazemConfigLow32Bit
                                ;;
                        esac
                        ;;
                esac
                ;;
        esac
        ;;
esac