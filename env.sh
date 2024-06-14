
# >>> build-setup-conda initialize >>>
# line auto-generated by ./build-setup.sh
if ! type conda >& /dev/null; then
    echo "::ERROR:: you must have conda in your environment first"
    return 1  # don't want to exit here because this file is sourced
fi

# if we're sourcing this in a sub process that has conda in the PATH but not as a function, init it again
conda activate --help >& /dev/null || source $(conda info --base)/etc/profile.d/conda.sh
conda activate /home/hazem/chipyard/.conda-env
source /home/hazem/chipyard/scripts/fix-open-files.sh
# <<< build-setup-conda initialize <<<


# >>> init-submodules initialize >>>
# line auto-generated by init-submodules-no-riscv-tools.sh
__DIR=/home/hazem/chipyard
PATH=$__DIR/software/firemarshal:$PATH
# <<< init-submodules initialize <<<

