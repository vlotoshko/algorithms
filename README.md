## Implementations of the variety algorithms and data structures.
###### Algorithms and their unit tests.
Application outputs result of unit tests.

###### Build
Build project with the key `COMPILE_WITH_CPPUNIT` to enable unit tests.
The documentation will be generated for `Release` version if `Doxygen` package is installed.

###### Usage
Usage: `algorithm`.
Possible output:
```
---  All Tests  ------------------------------------------------------------------
---  TestIsSorted  ---------------------------------------------------------------
| isSorted_ShouldFail_WhenGivenUnSortedContainer ........................ [ OK ] |
| isSorted_ShouldReturnTrue_WhenGivenSortedContainer .................... [ OK ] |
| isSorted_ShouldReturnTrue_WhenGivenContainerHasEqualElements .......... [ OK ] |
| isSorted_ShouldReturnTrue_WhenGivenContainerHasSameElement ............ [ OK ] |
| isSorted_ShouldReturnTrue_WhenGivenContainerIsEmpty ................... [ OK ] |
----------------------------------------------------------------------------------

---  Dummy sort  -----------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Buble sort  -----------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Comb sort  ------------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Shake sort  -----------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Quick sort  -----------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Quick sort median  ----------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Quick3 sort  ----------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Gnome sort  -----------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Selection sort  -------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Heap sort  ------------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Insertion sort  -------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  Merge sort  -----------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  MergeUp sort  ---------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  QuickIns sort  --------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  MergeIns sort  --------------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  InsertionBinary sort  -------------------------------------------------------
| sort_ShouldReturnSorted_WhenGivenSortedContainer ...................... [ OK ] |
| sort_ShouldReturnSorted_WhenGivenUnsortedContainer .................... [ OK ] |
----------------------------------------------------------------------------------

---  UnionFind/QiuckFind  --------------------------------------------------------
| find_ShouldReturnClusterId_WhenGivenComponent ......................... [ OK ] |
| unionComponents_ShouldConnectComponentsIntoOneCluster ................. [ OK ] |
----------------------------------------------------------------------------------

---  UnionFind/QiuckUnion  -------------------------------------------------------
| find_ShouldReturnClusterId_WhenGivenComponent ......................... [ OK ] |
| unionComponents_ShouldConnectComponentsIntoOneCluster ................. [ OK ] |
----------------------------------------------------------------------------------

---  UnionFind/QiuckUnion balanced  ----------------------------------------------
| find_ShouldReturnClusterId_WhenGivenComponent ......................... [ OK ] |
| unionComponents_ShouldConnectComponentsIntoOneCluster ................. [ OK ] |
----------------------------------------------------------------------------------

---  TestBST  --------------------------------------------------------------------
| get_ShouldReturnValue_WhenGivenKey .................................... [ OK ] |
| deleteNode_ShouldDeleteNode_WhenGivenKey .............................. [ OK ] |
| min_ShouldReturnKeyWithMinimalValue ................................... [ OK ] |
| max_ShouldReturnKeyWithMaximalValue ................................... [ OK ] |
| size_ShouldReturnCountOfNodes ......................................... [ OK ] |
| valueSum_ShouldReturnSumOfAllvalues ................................... [ OK ] |
| floor_ShouldReturnFloor_WhengivenKey .................................. [ OK ] |
| ceiling_ShouldReturnCeiling_WhengivenKey .............................. [ OK ] |
| select_ShouldReturnKey_WhenGivenRank .................................. [ OK ] |
| rank_ShouldReturnRank_WhenGivenKey .................................... [ OK ] |
----------------------------------------------------------------------------------

---  TestGraph  ------------------------------------------------------------------
| avgDegree_ShouldReturnAverageDegree_WhenGivenGraph .................... [ OK ] |
| maxDegree_ShouldReturnMaxDegree_WhenGivenGraph ........................ [ OK ] |
| selfLoops_ShouldReturnCountOfSelfLoops_WhenGivenGraph ................. [ OK ] |
| reverse_ShouldReturnReversedGraph_WhenGivenGraph ...................... [ OK ] |
| isCyclic_ShouldReturnTrue_WhenGivenGraphIsCyclic ...................... [ OK ] |
| isDirectedCyclic_ShouldReturnTrue_WhenGivenDirectedGraphIsCyclic ...... [ OK ] |
| depthFirstSearh_ShouldReturnCountOfSteps_WhenGivenGraph ............... [ OK ] |
| depthFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex ............. [ OK ] |
| depthFirstOrder_ShouldReturnOrderedGraphs_WhenGivenGraph .............. [ OK ] |
| topological_ShouldReturnTopologialOrder_WhenGivenGraph ................ [ OK ] |
| kosarajuSCC_ShouldReturnSCC_WhenGivenGraph ............................ [ OK ] |
| coupledComponents_ShouldReturnCC_WhenGivenGraph ....................... [ OK ] |
| transitiveClosure_ShouldReturnReachable_WhenGivenGraph ................ [ OK ] |
| twoColored_ShouldReturnTrue_WhenGivenGraphIsBipartite ................. [ OK ] |
| breadthFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex ........... [ OK ] |
----------------------------------------------------------------------------------

---  TestIsSorted  ---------------------------------------------------------------
| addEdge_ShouldAddEdge_WhenGivenTwoKeys ................................ [ OK ] |
| addEdge_ShouldReturnFalse_WhenAddedOverflowEdge ....................... [ OK ] |
| contains_ShouldReturnTrue_WhenGivenExistingsKey ....................... [ OK ] |
| index_ShouldReturnIndex_WhenGivenKey .................................. [ OK ] |
| name_ShouldReturnName_WhenGivenIndex .................................. [ OK ] |
| lexical_ShouldReturnEdgesAsString_WhenGivenIndex ...................... [ OK ] |
----------------------------------------------------------------------------------

---  PrimMST_Lazy  ---------------------------------------------------------------
| edges_ShouldReturnEdgesOfMST_WhenGivenGraph ........................... [ OK ] |
----------------------------------------------------------------------------------

---  PrimMST_Energy  -------------------------------------------------------------
| edges_ShouldReturnEdgesOfMST_WhenGivenGraph ........................... [ OK ] |
----------------------------------------------------------------------------------

---  KruskalMST  -----------------------------------------------------------------
| edges_ShouldReturnEdgesOfMST_WhenGivenGraph ........................... [ OK ] |
----------------------------------------------------------------------------------

---  DijkstraSP  -----------------------------------------------------------------
| distTo_ShouldReturnDistToVertex_WhenGivenVertex ....................... [ OK ] |
| hasPathTo_ShouldReturnTrue_WhenGivenVertex ............................ [ OK ] |
| pathTo_ShouldReturnEdgesToVertex_WhenGivenvVertex ..................... [ OK ] |
----------------------------------------------------------------------------------

---  AcyclicShortPaths  ----------------------------------------------------------
| distTo_ShouldReturnDistToVertex_WhenGivenVertex ....................... [ OK ] |
| hasPathTo_ShouldReturnTrue_WhenGivenVertex ............................ [ OK ] |
| pathTo_ShouldReturnEdgesToVertex_WhenGivenvVertex ..................... [ OK ] |
----------------------------------------------------------------------------------

---  AcyclicLongPaths  -----------------------------------------------------------
| distTo_ShouldReturnDistToVertex_WhenGivenVertex ....................... [ OK ] |
| hasPathTo_ShouldReturnTrue_WhenGivenVertex ............................ [ OK ] |
| pathTo_ShouldReturnEdgesToVertex_WhenGivenvVertex ..................... [ OK ] |
----------------------------------------------------------------------------------

---  CriticalPathMethod  ---------------------------------------------------------
| criticalPathMethod_ShouldReturnAcyclicLongPaths_DependentJobs ......... [ OK ] |
----------------------------------------------------------------------------------

----------------------------------------------------------------------------------
```