#!/usr/bin/env bash

GREEN="\033[1;32m"
RED="\033[1;31m"
ILC="\033[3m"
ORG="\033[1;33m"
RST="\033[0m"

PROGRAM_NAME="yutsuos"
UNIT_TESTS_NAME="unit_tests"

function _error()
{
    echo -e "${RED}${BOLD}[❌] ERROR:\n${RST}\t$1\n\t${ILC}\"$2\"${RST}"
    exit 84
}

function _success()
{
    echo -e "${GREEN}[✅] SUCCESS:\t${RST} ${ILC}$1${RST}"
}

function _info()
{
    echo -e "${ORG}[🚧] RUNNING:\t${RST} ${ILC}$1${RST}"
}

function _base_run()
{
    local cmake_args="$1"
    local build_type="$2"

    git submodule update --init --recursive
    mkdir -p build
    cd build || _error "mkdir failed"

    cmake .. -G Ninja $cmake_args
    if ! ninja $build_type; then
        _error "compilation error" "failed to compile $build_type"
    fi
    _success "compiled $build_type"
}

function _all()
{
    _base_run "-DCMAKE_BUILD_TYPE=Release -DENABLE_DEBUG=OFF" "$PROGRAM_NAME"
    exit 0
}

function _debug()
{
    _base_run "-DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG=ON" "$PROGRAM_NAME"
    exit 0
}

function _tests_run()
{
    _base_run "-DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG=ON -DENABLE_TESTS=ON" "$UNIT_TESTS_NAME"
    if ! ./$UNIT_TESTS_NAME; then 
        _error "unit tests error" "unit tests failed!"
    fi
    _success "unit tests succeed!"
    exit 0
}

function _clean()
{
    rm -rf build
}

function _fclean()
{
    _clean
    rm -rf $PROGRAM_NAME $UNIT_TESTS_NAME plugins code_coverage.txt $UNIT_TESTS_NAME-*.profraw $UNIT_TESTS_NAME.profdata vgcore* cmake-build-debug *.a libr*
}

function _run()
{
    cd build || _error "cd failed"
    ninja run
    exit 0
}

for args in "$@"
do
    case $args in
        -h|--help)
            cat << EOF
USAGE:
      $0    builds $PROGRAM_NAME project

ARGUMENTS:
      $0 [-h|--help]    displays this message
      $0 [-d|--debug]   debug flags compilation
      $0 [-r|--re]      rebuild the project
      $0 [-c|--clean]   clean the project
      $0 [-f|--fclean]  fclean the project
      $0 [-t|--tests]   run unit tests
      $0 [-run|--run]   run the program (after building it)
EOF
        exit 0
        ;;
    -c|--clean)
        _clean
        exit 0
        ;;
    -f|--fclean)
        _fclean
        exit 0
        ;;
    -d|--debug)
        _debug
        ;;
    -t|--tests)
        _tests_run
        ;;
    -r|--re)
        _fclean
        _all
        ;;
    -run|--run)
        _run
        ;;
    *)
        _error "Invalid arguments: " "$args"
    esac
done

_all
