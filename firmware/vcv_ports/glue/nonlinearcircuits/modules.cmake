set(NONLINEARCIRCUITS_DIR ${CMAKE_CURRENT_LIST_DIR}/../../nonlinearcircuits)

set(nonlinearcircuitsModules
    4Seq
    8BitCipher
    BOOLs
    DivideConquer
    DivineCMOS
    DoubleNeuron
    GENiE
    LetsSplosh
    Neuron
    Numberwang
    Router
    Segue
    SlothApathy
    SlothInertia
    SlothTorpor
    SquidAxon
    Statues
    TripleSloth
)

include(${CMAKE_CURRENT_LIST_DIR}/../filter.cmake)
limit_modules_built("nonlinearcircuits" nonlinearcircuitsModules)

# cpp paths
list(TRANSFORM nonlinearcircuitsModules PREPEND ${NONLINEARCIRCUITS_DIR}/src/ OUTPUT_VARIABLE NONLINEARCIRCUITS_SOURCE_PATHS)
list(TRANSFORM NONLINEARCIRCUITS_SOURCE_PATHS APPEND .cpp)

# svg paths
list(TRANSFORM nonlinearcircuitsModules PREPEND ${NONLINEARCIRCUITS_DIR}/res/ OUTPUT_VARIABLE
                                                                              NONLINEARCIRCUITS_FACEPLATE_SVGS
)
list(TRANSFORM NONLINEARCIRCUITS_FACEPLATE_SVGS APPEND .svg)