#!/bin/bash

# -------------------------------------------------------------------------
# Generates report of cppcheck result to specified directory
# -------------------------------------------------------------------------

PATH_TO_SOURCE="src"
INCLUDE_DIR="-I include -I test/unit"
OUTPUT_DIR=./test/cppcheck/html

HEADERS_TO_CHECK=" \
    include/Tools.hpp \
    include/GraphAlgorithms.hpp \
    include/MinimalSpanningTree.hpp \
    include/UnionFind.hpp \
    include/ShortPaths.hpp \
    include/Sort.hpp \
    include/Sort_Impl.hpp \
    include/BinarySearchTree.hpp \
    include/Edge.hpp \
    include/Graph.hpp \
    include/GraphDirectionPolicies.hpp \
    include/IndexedPQ.hpp \
    test/unit/CustomListeners.hpp \
    test/unit/TestGraph.hpp \
    test/unit/TestBinarySearchTree.hpp \
    test/unit/TestUnionFind.hpp \
    test/unit/TestSort.hpp \
    test/unit/UnitTests.hpp"

# cd to source directory
cd "$(dirname "$0")"
cd ../../

cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --xml-version=2 --force --library=windows,posix,gnu --include=$HEADERS_TO_CHECK $INCLUDE_DIR $PATH_TO_SOURCE  2> result.xml
cppcheck-htmlreport --source-encoding="iso8859-1" --title="algorithms" --source-dir=. --report-dir=$OUTPUT_DIR --file=result.xml
rm result.xml

